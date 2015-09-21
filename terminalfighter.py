import sys

import pygame

from universe import Universe
from gamemaster import GameMaster

pygame.init()
pygame.font.init()
pygame.key.set_repeat(100, 25)

DRAWING_SCALE = 1
if len(sys.argv) >= 2:
    try:
        DRAWING_SCALE = int(sys.argv[1])
    except ValueError:
        print("Scale argument must be int")
        sys.exit()


GAME_WIDTH = 1000
GAME_HEIGHT = 700
WHITE = 0, 0, 0

screen = pygame.display.set_mode((int(GAME_WIDTH*DRAWING_SCALE), int(GAME_HEIGHT*DRAWING_SCALE)))

universe = Universe((GAME_WIDTH, GAME_HEIGHT))
gamemaster = GameMaster(universe, DRAWING_SCALE)

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
    gamemaster.update(events)
    # print("update time : " + str(pygame.time.get_ticks() - update_start_time))

    draw_start_time = pygame.time.get_ticks() 
    gamemaster.draw(screen)
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