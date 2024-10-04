import pygame
import sys
import random

# Initialize Pygame
pygame.init()

# Set screen dimensions
screen_width = 1000
screen_height = 1000
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
ball_dy = 4  # Vertical speed
ball_color = random.choice([RED, BLUE])

# Paddle properties
paddle_width = 100
paddle_height = 10
paddle_x = (screen_width - paddle_width) // 2
paddle_y = screen_height - paddle_height - 10
paddle_speed = 6
paddle_color = RED  # Initially red

# Game variables
gravity_on = False
game_paused = False
hit_counter = 0
score = 0
game_won = False  # Track if the game is won

# Bricks properties
brick_rows = 4
brick_cols = 7
brick_padding = 5
brick_width = (screen_width - brick_padding*brick_cols) // brick_cols
brick_height = 20
bricks = []

# Fonts for displaying text
font = pygame.font.Font(None, 36)

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

# Function to display the hit counter and score
def draw_stats():
    text = font.render(f"Hits: {hit_counter}  Score: {score}", True, WHITE)
    screen.blit(text, (10, 10))

# Function to display the pause menu
def display_pause_menu():
    screen.fill(BLACK)
    text = font.render("PAUSED", True, WHITE)
    screen.blit(text, (screen_width // 2 - 50, screen_height // 2 - 50))
    text = font.render("Press J to Continue", True, WHITE)
    screen.blit(text, (screen_width // 2 - 120, screen_height // 2))

# Function to display the win screen
def display_win_message():
    screen.fill(BLACK)
    text = font.render("YOU WIN!", True, WHITE)
    screen.blit(text, (screen_width // 2 - 70, screen_height // 2 - 50))
    text = font.render("Press R to Restart", True, WHITE)
    screen.blit(text, (screen_width // 2 - 120, screen_height // 2))

# Function to reset the game
def reset_game():
    pygame.time.wait(1000)  # Wait for 1 second before resetting
    global ball_x, ball_y, ball_dx, ball_dy, hit_counter, score, gravity_on, paddle_color, game_won
    create_bricks()
    ball_x = screen_width // 2
    ball_y = screen_height // 2
    ball_dx = random.choice([-4, -3, -2, 2, 3, 4])
    ball_dy = 4
    hit_counter = 0
    score = 0
    gravity_on = False
    paddle_color = RED
    game_won = False  # Reset the win condition

# Main game loop
def main():
    global game_paused, paddle_x, paddle_color, gravity_on, ball_x, ball_y, ball_dx, ball_dy, hit_counter, score, game_won  # Declare necessary globals
    create_bricks()  # Initialize bricks

    while True:
        # Handle events
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()

        # Check for key presses
        keys = pygame.key.get_pressed()

        if game_won:
            if keys[pygame.K_r]:
                reset_game()  # Restart the game when 'R' is pressed

        else:
            # Paddle movement
            if keys[pygame.K_LEFT]:
                paddle_x -= paddle_speed
            if keys[pygame.K_RIGHT]:
                paddle_x += paddle_speed

            # Change paddle color with 'B' key
            if keys[pygame.K_b]:
                paddle_color = BLUE if paddle_color == RED else RED

            # Toggle gravity with 'S' key
            if keys[pygame.K_s]:
                gravity_on = not gravity_on

            # Pause the game with 'J' key
            if keys[pygame.K_j]:
                game_paused = not game_paused

            # Game logic
            if not game_paused:
                # Update ball position
                ball_x += ball_dx
                ball_y += ball_dy

                # Apply gravity if toggled
                if gravity_on:
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
                        if brick.collidepoint(ball_x, ball_y):
                            ball_dy = -ball_dy
                            row.remove((brick, color))
                            score += 10  # Increase score for each brick hit
                            change_ball_color()

                # Ball out of bounds (reset if it falls below the screen)
                if ball_y > screen_height:
                    reset_game()

                # Check if all bricks are destroyed (win condition)
                if all(len(row) == 0 for row in bricks):
                    game_won = True

        # Draw everything
        screen.fill(BLACK)
        if game_won:
            display_win_message()  # Display win message if the game is won
        elif game_paused:
            display_pause_menu()
        else:
            draw_ball()
            draw_paddle()
            draw_bricks()
            draw_stats()

        pygame.display.flip()
        pygame.time.delay(30)  # Control the frame rate

main()
