import sys

import pygame

pygame.init()
screen = pygame.display.set_mode((1000, 1000))

WHITE = 0, 0, 0

while 1:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            sys.exit()
    
    background = pygame.Surface(screen.get_size())
    background = background.convert()
    background.fill((255, 255, 255))
    screen.blit(background, (0, 0))

    pygame.display.flip()