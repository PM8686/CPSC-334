import pygame
import math

# Initialize pygame
pygame.init()

# Screen dimensions for fullscreen mode
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

# Function to draw a circle as the heart beat, with radius based on screen size
def draw_heart(scale):
    radius = int(0.1 * min(screen_width, screen_height) * scale)  # Radius is 10% of the smaller screen dimension
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

# Function to render text on the screen
def render_text(text, position):
    text_surface = font.render(text, True, WHITE)
    text_rect = text_surface.get_rect(center=position)
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
            # Adjust BPM with arrow keys
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_UP and bpm < 180:  # Increase BPM with UP arrow
                    bpm += 1
                if event.key == pygame.K_DOWN and bpm > 60:  # Decrease BPM with DOWN arrow
                    bpm -= 1

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
        render_text(f"BPM: {bpm}", (screen_width // 2, 50))

        # Update the display
        pygame.display.flip()

        # Cap the frame rate
        clock.tick(60)

# Example of running the heart beat with adjustable BPM
run_heart_beat(70)  # Start with an initial BPM of 70

# Quit pygame
pygame.quit()
