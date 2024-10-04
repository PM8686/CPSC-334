import pygame
import sys
import random
import serial  # Import pySerial to read inputs from ESP32

# Initialize Pygame
pygame.init()

# Set screen dimensions
screen_width = 690
screen_height = 540
screen = pygame.display.set_mode((screen_width, screen_height))
pygame.display.set_caption("Bounce the Ball")

# Define colors
WHITE = (255, 255, 255)
RED = (255, 0, 0)
BLUE = (0, 0, 255)
GREEN = (0, 255, 0)
YELLOW = (255, 255, 0)
PURPLE = (128, 0, 128)
BLACK = (0, 0, 0)

brick_colors = [RED, BLUE, GREEN, YELLOW, PURPLE]

# Ball properties
ball_radius = 10
ball_x = screen_width // 2
ball_y = screen_height // 2
ball_dx = random.choice([-4, -3, -2, 2, 3, 4])  # Random horizontal speed
ball_dy = 8  # Vertical speed
ball_color = random.choice([RED, BLUE])

# Paddle properties
paddle_width = 100
paddle_height = 10
paddle_x = (screen_width - paddle_width) // 2
paddle_y = screen_height - paddle_height - 10
paddle_speed = 8
paddle_color = RED  # Initially red

# Game variables
gravity = False
game_paused = True
hit_counter = 0
score = 0
game_won = False  # Track if the game is won
game_lost = False
lives = 3  # Player starts with 3 lives

# Bricks properties
brick_rows = 1
brick_cols = 7
brick_padding = 5
brick_width = (screen_width - brick_padding * brick_cols) // brick_cols
brick_height = 20
bricks = []

# Fonts for displaying text
font = pygame.font.Font(None, 36)

# Last button states for detecting press events
last_button_state = 1
last_joy_sw_state = 1

# Function to create bricks with random colors
def create_bricks():
    global bricks
    bricks = []
    for row in range(brick_rows):
        brick_row = []
        for col in range(brick_cols):
            brick_x = col * (brick_width + brick_padding)
            brick_y = row * (brick_height + brick_padding) + 50
            color = random.choice(brick_colors)  # Random color for each brick
            brick_rect = pygame.Rect(brick_x, brick_y, brick_width, brick_height)
            brick_row.append((brick_rect, color))
        bricks.append(brick_row)

# Function to draw the ball
def draw_ball():
    pygame.draw.circle(screen, ball_color, (ball_x, ball_y), ball_radius)

def change_ball_color():
    global ball_color
    ball_color = random.choice([RED, BLUE])

# Function to draw the paddle
def draw_paddle():
    pygame.draw.rect(screen, paddle_color, (paddle_x, paddle_y, paddle_width, paddle_height))

# Function to draw the bricks
def draw_bricks():
    for row in bricks:
        for brick, color in row:
            pygame.draw.rect(screen, color, brick)

# Function to display the hit counter, score, and lives
def draw_stats():
    text = font.render(f"Hits: {hit_counter}  Score: {score}  Lives: {lives}", True, WHITE)
    screen.blit(text, (10, 10))

# Function to display the pause menu
def display_pause_menu():
    screen.fill(BLACK)
    text = font.render("Push the Joystick to Continue", True, WHITE)
    screen.blit(text, (screen_width // 2 - 180, screen_height // 2))

# Function to display the win screen
def display_win_message():
    screen.fill(BLACK)
    text = font.render("YOU WIN!", True, WHITE)
    screen.blit(text, (screen_width // 2 - 70, screen_height // 2 - 50))
    text = font.render(f"Final Score: {score}   Hits: {hit_counter}", True, WHITE)
    screen.blit(text, (screen_width // 2 - 160, screen_height // 2))
    text = font.render("Press the joystick to restart", True, WHITE)
    screen.blit(text, (screen_width // 2 - 160, screen_height // 2 + 50))

# Function to display the win screen
def display_lose_message():
    screen.fill(BLACK)
    text = font.render("YOU LOST :(", True, WHITE)
    screen.blit(text, (screen_width // 2 - 80, screen_height // 2 - 50))
    text = font.render(f"Final Score: {score}   Hits: {hit_counter}", True, WHITE)
    screen.blit(text, (screen_width // 2 - 160, screen_height // 2))
    text = font.render("Press the joystick to restart", True, WHITE)
    screen.blit(text, (screen_width // 2 - 160, screen_height // 2 + 50))

# Function to reset the game
def reset_game():
    pygame.time.wait(1000)  # Wait for 1 second before resetting
    global ball_x, ball_y, ball_dx, ball_dy, hit_counter, score, gravity, paddle_color, game_won, game_lost, lives
    create_bricks()
    ball_x = screen_width // 2
    ball_y = screen_height // 2
    ball_dx = random.choice([-4, -3, -2, 2, 3, 4])
    ball_dy = 4
    hit_counter = 0
    score = 0
    gravity = False
    paddle_color = RED
    game_won = False  # Reset the win condition
    game_lost = False
    lives = 3  # Reset lives to 3

# Function to read joystick and button inputs from ESP32
def read_ESP(ser):
    line = ser.readline().decode('utf-8').strip()  # Read a line from the serial port
    data = line.split(' ')
    
    # Expecting 5 values: joy_x, joy_y, joy_sw, button, switch
    if len(data) == 5:
        joy_x = int(data[0])
        joy_sw = int(data[2])
        button_state = int(data[3])
        switch_state = int(data[4])
        return joy_x, joy_sw, button_state, switch_state
    else:
        return None  # Return None if data is not as expected

# Main game loop
def main():
    global game_paused, paddle_x, paddle_color, gravity, ball_x, ball_y, ball_dx, ball_dy, hit_counter, score, game_won, game_lost, lives, last_button_state, last_joy_sw_state   # Declare necessary globals
    create_bricks()  # Initialize bricks

    # Initialize pySerial to read inputs from the ESP32
    ser = serial.Serial('COM3', 115200)  # Replace 'COM3' with ESP32's port

    while True:
        # Handle events
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()

        # Read joystick and button inputs from ESP32
        inputs = read_ESP(ser)
        if inputs is not None:
            joy_x, joy_sw, button_state, switch_state = inputs
        else:
            continue  # Skip this loop iteration if data is not as expected

        # Detect button press (transition from 1 to 0)
        if last_joy_sw_state == 1 and joy_sw == 0:
            game_paused = not game_paused  # Toggle pause on button press

            if game_won or game_lost:  # restart the game if necessary
                reset_game()

        last_joy_sw_state = joy_sw  # Update the last button state

        # Detect switch press (transition from 1 to 0 for toggling gravity)
        if switch_state == 0:
            gravity = True 
        else:
            gravity = False

        # Paddle movement logic based on joystick input
        if joy_x < 1500:
            paddle_x -= paddle_speed
        elif joy_x > 2200:
            paddle_x += paddle_speed
        
        # Ensure paddle stays within bounds
        paddle_x = max(0, min(paddle_x, screen_width - paddle_width))

        # Change paddle color if button is pressed (button state is 0 when pressed)
        if button_state == 0 and last_button_state == 1:
            paddle_color = BLUE if paddle_color == RED else RED
        last_button_state = button_state

        # Game logic
        if not game_paused:
            # Update ball position
            ball_x += ball_dx
            ball_y += ball_dy

            # Apply gravity if true
            if gravity:
                ball_dy += 0.2

            # Ball collision with walls
            if ball_x - ball_radius <= 0 or ball_x + ball_radius >= screen_width:
                ball_dx = -ball_dx
                change_ball_color()
            if ball_y - ball_radius <= 0:
                ball_dy = -ball_dy
                change_ball_color()

            # Ball collision with paddle
            if (paddle_y <= ball_y + ball_radius <= paddle_y + paddle_height and
                    paddle_x <= ball_x <= paddle_x + paddle_width):
                if paddle_color == ball_color:
                    ball_dy = -ball_dy
                    hit_counter += 1

            # Ball collision with bricks
            for row in bricks:
                for brick, color in row:
                    # Check if the ball is within the brick's horizontal range and close to its vertical edges (top or bottom)
                    if (brick.left <= ball_x <= brick.right and
                            brick.top - ball_radius <= ball_y <= brick.bottom + ball_radius):
                        ball_dy = -ball_dy
                        row.remove((brick, color))
                        score += 10  # Increase score for each brick hit
                        change_ball_color()

                    # Check if the ball is within the brick's vertical range and close to its horizontal edges (left or right)
                    elif (brick.top <= ball_y <= brick.bottom and
                        brick.left - ball_radius <= ball_x <= brick.right + ball_radius):
                        ball_dx = -ball_dx
                        row.remove((brick, color))
                        score += 10  # Increase score for each brick hit
                        change_ball_color()

            # Ball out of bounds (below the screen)
            if ball_y + ball_radius >= screen_height:
                lives -= 1  # Subtract a life
                if lives > 0:
                    # Reset ball position if there are lives left
                    ball_x = screen_width // 2
                    ball_y = screen_height // 2
                    ball_dx = random.choice([-4, -3, -2, 2, 3, 4])
                    ball_dy = 4
                else:
                    # lose game if lives = 0
                    game_lost = True

            # Check if all bricks are destroyed (winning condition)
            if all(len(row) == 0 for row in bricks):
                game_won = True  # Mark the game as won

        # Drawing
        screen.fill(BLACK)  # Clear the screen
        
        if game_won:
            display_win_message()  # Show win message if game won
        
        elif game_lost: 
            display_lose_message() # Show lose message if lost

        elif game_paused:
            display_pause_menu()  # Show pause menu
        else:
            draw_ball()
            draw_paddle()
            draw_bricks()
            draw_stats()  # Show hit counter, score, and lives

        # Update the display
        pygame.display.flip()

        # Set frame rate
        pygame.time.Clock().tick(60)

# Run the main loop
main()
