import random

import pygame

from basic_grunt import BasicGrunt
from maincharacter import MainCharacter


class GameMaster():

    def __init__(self, universe, DRAWING_SCALE):
        self.universe_ = universe
        self.DRAWING_SCALE_ = DRAWING_SCALE

        self.basic_grunt_spawn_delay_ = 200
        self.basic_grunt_spawn_timer_ = 199
        self.basic_grunt_x_spawn_locations = [x/100 for x in range(20, 80)] 
        self.main_character_spawn_height_ = self.universe_.height_*0.9
        self.spawn_main_character()

        self.spawn_difficulty_ = 0.1
        self.minimum_spawn_delay_ = 19 

    def draw(self, screen):
        self.universe_.main_character_.draw_view(screen)
        self.universe_.main_character_.draw_ui(screen)

    def spawn_main_character(self):
        starting_position = [
            self.universe_.width_/2, self.main_character_spawn_height_]
        the_main_character = MainCharacter(
            starting_position, self.universe_, self.DRAWING_SCALE_)
        self.universe_.create_main_character(the_main_character)

    def spawn_basic_grunt(self):
        starting_position = [self.universe_.width_*random.choice(self.basic_grunt_x_spawn_locations), 0]
        the_basic_grunt = BasicGrunt(starting_position, self.universe_)
        self.universe_.create_enemy(the_basic_grunt)

    def update(self, events):
        self.basic_grunt_spawn_timer_ += 1
        if self.basic_grunt_spawn_delay_ > self.minimum_spawn_delay_: 
            self.basic_grunt_spawn_delay_ -= self.spawn_difficulty_ 
            if self.basic_grunt_spawn_delay_ < self.minimum_spawn_delay_:
                self.basic_grunt_spawn_delay_ = self.minimum_spawn_delay_
        if self.basic_grunt_spawn_timer_ > self.basic_grunt_spawn_delay_:
            self.spawn_basic_grunt()
            self.basic_grunt_spawn_timer_ = 0
             
        self.universe_.update(events)
