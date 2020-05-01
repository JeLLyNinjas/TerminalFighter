import random

import pygame

from basic_grunt import BasicGrunt
from score_counter import ScoreCounter
from maincharacter import MainCharacter
from not_so_basic_grunt import NotSoBasicGrunt

class GameMaster():

    def __init__(self, universe, spawn_controller, score_counter):
        self.universe_ = universe
        self.spawn_controller = spawn_controller
        self.score_counter_ = score_counter
        self.main_character_spawn_height_ = self.universe_.height_*0.9
        self.spawn_main_character()

    def draw(self, screen):
        self.universe_.main_character_.draw_view(screen)
        self.universe_.main_character_.draw_ui(screen)
        self.score_counter_.draw(screen)

    def spawn_main_character(self):
        starting_position = [
            self.universe_.width_/2, self.main_character_spawn_height_]
        the_main_character = MainCharacter(
            starting_position, self.universe_)
        self.universe_.create_main_character(the_main_character)

    def update(self, events):
        self.spawn_controller.update()
        self.score_counter_.update()
        self.universe_.update(events)
