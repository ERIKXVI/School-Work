import pygame

# Initialize Pygame
pygame.init()

# Set window dimensions
screen_width = 600
screen_height = 400
screen = pygame.display.set_mode((screen_width, screen_height))

# Title
pygame.display.set_caption("My Pygame Game")

# Colors (Example)
black = (0, 0, 0)
white = (255, 255, 255)

# Game Loop 
running = True
while running:
    # Event Handling
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    # Game Logic (Update things here)


    # Drawing
    screen.fill(white)  # Fill background with white

    # Update the display
    pygame.display.flip()

# Quit Pygame
pygame.quit()
