import sys

import pygame

from maincharacter import MainCharacter
from universe import Universe

pygame.init()

GAME_WIDTH = 1000
GAME_HEIGHT = 700
BLACK = 0, 0, 0

def main_menu(screen, DRAWING_SCALE):
    
    universe = Universe((GAME_WIDTH, GAME_HEIGHT))
    the_main_character = MainCharacter([universe.width_/2, universe.height_*0.9], universe, DRAWING_SCALE)
    the_main_character.weapons_ = the_main_character.weapons_[:1] 
    universe.create_main_character(the_main_character)

    # pygame ticks, one tick is 1/1000 second
    # 15 pygame ticks per update is approximately 30 updates per second
    FRAME_LENGTH_TICKS = 33
    
    prev_frame_start_time = 0
    
    while 1:
        frame_start_time = pygame.time.get_ticks()
        # print("Elapsed time since last update : " + str(frame_start_time - prev_frame_start_time))
        prev_frame_start_time = frame_start_time
    
        update_start_time = pygame.time.get_ticks()
        events = pygame.event.get()
        for event in events:
            if event.type == pygame.QUIT:
                sys.exit()
        universe.update(events)
        # print("update time : " + str(pygame.time.get_ticks() - update_start_time))
    
        draw_start_time = pygame.time.get_ticks()
        universe.main_character_.current_weapon_.draw(screen)
        # universe.main_character_.draw_ui(screen)
        # print("draw time : " + str(pygame.time.get_ticks() - draw_start_time))
    
        flip_start_time = pygame.time.get_ticks()
        pygame.display.flip()
        # print("flip time : " + str(pygame.time.get_ticks() - flip_start_time))
    
        frame_end_time = pygame.time.get_ticks()
        frame_time_elapsed = frame_end_time - frame_start_time
        if frame_time_elapsed < FRAME_LENGTH_TICKS:
            pygame.time.wait(FRAME_LENGTH_TICKS - frame_time_elapsed)
        else:
            print("WARNING: Cannot keep up with 30FPS update time!")
