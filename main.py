import cProfile
import sys
import time

import pygame

from main_menu import main_menu
from terminalfighter import terminalfighter

GAME_WIDTH = 1000
GAME_HEIGHT = 700

PROFILE_FILE_NAME = "terminalfighter"


def exit_game(screen):
    sys.exit()


run_game_state = {
    "MENU": main_menu,
    "PLAY": terminalfighter,
    "QUIT": exit_game
}

if __name__ == '__main__':
    # Start profiling
    pr = cProfile.Profile()
    pr.enable()
    try:
        pygame.init()
        screen = pygame.display.set_mode((int(GAME_WIDTH), int(GAME_HEIGHT)))
        gamestate = "MENU"
        while True:
            gamestate = run_game_state.get(gamestate, exit_game)(screen)
    finally:
        pr.disable()
        pr.dump_stats("%s_%d.prof" % (PROFILE_FILE_NAME, int(time.time())))
