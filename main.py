import cProfile
import sys
import time
import argparse
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
    parser = argparse.ArgumentParser()
    parser.add_argument("-p", "--profile", action='store_true',
                        help="Enabling profiling. Profiling output is dumped into terminalfighter_<timestamp>")
    args = parser.parse_args()
    pr = cProfile.Profile()
    if args.profile:
        # Start profiling
        print("Starting with profiling enabled")
        pr.enable()
    try:
        pygame.init()
        screen = pygame.display.set_mode((int(GAME_WIDTH), int(GAME_HEIGHT)))
        gamestate = "MENU"
        while True:
            gamestate = run_game_state.get(gamestate, exit_game)(screen)
    finally:
        if args.profile:
            pr.disable()
            prof_file = "%s_%d.prof" % (PROFILE_FILE_NAME, int(time.time()))
            print("Dumping profiling results to %s" % prof_file)
            pr.dump_stats(prof_file)
