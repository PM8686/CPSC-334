import pygame
import math
import socket

# Replace with the ESP32 IP address
esp32_ip = "10.67.70.186"  
port = 80

# Initialize pygame
pygame.init()

# Set up fullscreen display
screen = pygame.display.set_mode((0, 0), pygame.FULLSCREEN)
screen_width, screen_height = screen.get_size()

# Colors
BLACK = (0, 0, 0)
RED = (255, 0, 0)
WHITE = (255, 255, 255)

# Set the title of the window
pygame.display.set_caption("Heart Beat Lub-Dub")

# Clock to control the frame rate
clock = pygame.time.Clock()

# Set font for displaying BPM
font = pygame.font.SysFont(None, 36)

def receive_data():
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect((esp32_ip, port))
        data = s.recv(1024)  # Receive data from ESP32
        return data.decode()
    
# Function to draw a circle as the heart beat, scaling based on screen size
def draw_heart(scale):
    radius = int(0.1 * min(screen_width, screen_height) * scale)  # 10% of smaller dimension
    center_x, center_y = screen_width // 2, screen_height // 2
    pygame.draw.circle(screen, RED, (center_x, center_y), radius)

# Function to convert BPM to lull time in milliseconds (the time between lub-dub sequences)
def bpm_to_lull_time(bpm):
    total_interval = 60000 / bpm  # Total time between heart beats
    lub_dub_duration = 500  # Total time for lub-dub (fixed)
    return total_interval - lub_dub_duration  # Lull is the remaining time

# Smooth transition between values using linear interpolation (lerp)
def lerp(start, end, t):
    return start + t * (end - start)

# Function to render centered text on the screen
def render_text(text):
    text_surface = font.render(text, True, WHITE)
    text_rect = text_surface.get_rect(center=(screen_width // 2, 50))
    screen.blit(text_surface, text_rect)

# Main loop
def run_heart_beat(initial_bpm):
    bpm = initial_bpm  # Initialize bpm
    scale = 1.0  # Initial scale for heart size
    lub_increase_duration = 100  # "Lub" increase time (100 ms)
    lub_decrease_duration = 100  # "Lub" decrease time (100 ms)
    dub_increase_duration = 100  # "Dub" increase time (100 ms)
    dub_decrease_duration = 100  # "Dub" decrease time (100 ms)
    
    lull_time = bpm_to_lull_time(bpm)  # Calculate lull time based on BPM
    total_cycle_time = (lub_increase_duration + lub_decrease_duration +
                        dub_increase_duration + dub_decrease_duration + lull_time)  # Full heartbeat cycle time

    running = True
    while running:
        # Handle events
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
            elif event.type == pygame.KEYDOWN:
                if event.key == pygame.K_ESCAPE:  # Press ESC to quit
                    running = False
        # Fetch new BPM data every second
        current_time = time.time()
        if current_time - last_data_fetch_time >= 1:  # Check if 1 second has passed
            try:
                bpm = int(receive_data())  # Ensure bpm is an integer
                print(bpm)
            except Exception as e:
                print("Failed to receive data:", e)
            last_data_fetch_time = current_time  # Reset last fetch time

        # Update lull time based on the current bpm
        lull_time = bpm_to_lull_time(bpm)
        total_cycle_time = (lub_increase_duration + lub_decrease_duration +
                            dub_increase_duration + dub_decrease_duration + lull_time)

        # Get the current time
        current_time = pygame.time.get_ticks()
        elapsed_time = current_time % total_cycle_time

        # Smooth transitions for the four-phase lub-dub process
        if elapsed_time <= lub_increase_duration:  # Lub increase phase
            t = elapsed_time / lub_increase_duration
            scale = lerp(1.0, 1.3, t)  # Scale from 1.0 to 1.3
        elif elapsed_time <= lub_increase_duration + lub_decrease_duration:  # Lub decrease phase
            t = (elapsed_time - lub_increase_duration) / lub_decrease_duration
            scale = lerp(1.3, 1.1, t)  # Scale from 1.3 to 1.1
        elif elapsed_time <= lub_increase_duration + lub_decrease_duration + dub_increase_duration:  # Dub increase phase
            t = (elapsed_time - lub_increase_duration - lub_decrease_duration) / dub_increase_duration
            scale = lerp(1.1, 1.4, t)  # Scale from 1.1 to 1.4
        elif elapsed_time <= lub_increase_duration + lub_decrease_duration + dub_increase_duration + dub_decrease_duration:  # Dub decrease phase
            t = (elapsed_time - lub_increase_duration - lub_decrease_duration - dub_increase_duration) / dub_decrease_duration
            scale = lerp(1.4, 1.0, t)  # Scale from 1.4 to 1.0
        else:  # Lull phase
            t = (elapsed_time - lub_increase_duration - lub_decrease_duration - dub_increase_duration - dub_decrease_duration) / lull_time
            scale = 1.0  # During the lull, keep scale at resting size

        # Clear the screen
        screen.fill(BLACK)

        # Draw the circle based on the current scale
        draw_heart(scale)

        # Display the current BPM on the screen, centered at the top
        render_text(f"BPM: {bpm}")

        # Update the display
        pygame.display.flip()

        # Cap the frame rate
        clock.tick(60)

# Example of running the heart beat with adjustable BPM
run_heart_beat(70)  # Start with an initial BPM of 70

# Quit pygame
pygame.quit()
