import sys

import pygame

import main_menu
import terminal_fighter

pygame.init()

DRAWING_SCALE = 1
if len(sys.argv) >= 2:
    try:
        DRAWING_SCALE = int(sys.argv[1])
    except ValueError:
        print("Scale argument must be int")
        sys.exit()

GAME_WIDTH = 1000
GAME_HEIGHT = 700

screen = pygame.display.set_mode(
    (int(GAME_WIDTH*DRAWING_SCALE), int(GAME_HEIGHT*DRAWING_SCALE)))

run_game_state = {
    "MENU": main_menu,
    "GAME": terminal_fighter
    "QUIT": sys.exit
}

gamestate_handler = GameStateHandler()

gamestate = "MENU"

while True:
    gamestate = run_game_state.get(
        gamestate, sys.exit())(screen, DRAWING_SCALE)
