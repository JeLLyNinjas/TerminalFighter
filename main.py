import sys

import pygame

from main_menu import main_menu
from terminalfighter import terminalfighter

pygame.init()

def exit_game(screen):
    sys.exit()

GAME_WIDTH = 1000
GAME_HEIGHT = 700

# pygame ticks, one tick is 1/1000 second
# 16 pygame ticks per update is approximately 62.5 updates per second
FRAME_LENGTH_TICKS = 16

screen = pygame.display.set_mode(
    (int(GAME_WIDTH), int(GAME_HEIGHT)))

run_game_state = {
    "MENU" : main_menu,
    "PLAY" : terminalfighter,
    "QUIT" : exit_game
}

gamestate = "MENU"


while True:
    gamestate = run_game_state.get(gamestate, exit_game)(screen, FRAME_LENGTH_TICKS)

