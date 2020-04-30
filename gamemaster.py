import random

import pygame

from basic_grunt import BasicGrunt
from score_counter import ScoreCounter
from maincharacter import MainCharacter
from not_so_basic_grunt import NotSoBasicGrunt

class GameMaster():

    def __init__(self, universe):
        self.universe_ = universe
        self.score_counter_ = ScoreCounter()

        self.basic_grunt_spawn_delay_ = 300
        self.basic_grunt_spawn_timer_ = self.basic_grunt_spawn_delay_
        self.enemy_x_spawn_locations = [x/100 for x in range(20, 80)]
        self.main_character_spawn_height_ = self.universe_.height_*0.9
        self.spawn_main_character()

        self.spawn_difficulty_ = 0.9995
        self.minimum_spawn_delay_ = 40

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

    def spawn_basic_grunt(self):
        starting_position = [self.universe_.width_*random.choice(self.enemy_x_spawn_locations), 0]
        the_basic_grunt = BasicGrunt(starting_position, self.universe_)
        self.universe_.create_enemy(the_basic_grunt)
        the_basic_grunt.register(self.score_counter_)

    def spawn_not_so_basic_grunt(self):
        starting_position = [self.universe_.width_*random.choice(self.enemy_x_spawn_locations), 0]
        not_so_basic_grunt = NotSoBasicGrunt(starting_position, self.universe_)
        self.universe_.create_enemy(not_so_basic_grunt)
        not_so_basic_grunt.register(self.score_counter_)

    def update(self, events):
        # print('self.basic_grunt_spawn_delay_:' + str(self.basic_grunt_spawn_delay_))
        self.basic_grunt_spawn_timer_ += 1

        if self.basic_grunt_spawn_delay_ > self.minimum_spawn_delay_:
            self.basic_grunt_spawn_delay_ *= self.spawn_difficulty_
        else:
            self.basic_grunt_spawn_delay_ = self.minimum_spawn_delay_
            # print("maximum difficulty reached")

        if self.basic_grunt_spawn_timer_ > self.basic_grunt_spawn_delay_:
            self.spawn_basic_grunt()
            self.spawn_not_so_basic_grunt()
            self.basic_grunt_spawn_timer_ = 0

        self.score_counter_.update()
        self.universe_.update(events)
