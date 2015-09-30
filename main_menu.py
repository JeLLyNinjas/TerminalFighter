import sys

import pygame

pygame.init()

BLACK = 0, 0, 0

def main_menu(screen, DRAWING_SCALE):
    
    while True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                sys.exit()
            elif event.type == pygame.KEYDOWN:
                return "GAME"

        pygame.draw.rect(screen, BLACK, pygame.Rect((0,0), screen.get_size()))




