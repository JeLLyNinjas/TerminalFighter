import sys

import pygame

from main_menu import main_menu
from terminalfighter import terminalfighter

pygame.init()

def exit_game(screen):
    sys.exit()

GAME_WIDTH = 1000
GAME_HEIGHT = 700

screen = pygame.display.set_mode(
    (int(GAME_WIDTH), int(GAME_HEIGHT)))

run_game_state = {
    "MENU" : main_menu,
    "PLAY" : terminalfighter,
    "QUIT" : exit_game
}

gamestate = "MENU"

while True:
    gamestate = run_game_state.get(gamestate, exit_game)(screen)
