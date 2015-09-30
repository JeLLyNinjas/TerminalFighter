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

        # Enter the spawn rate (grunts / second) at a specific time t
        # Enter time t
        # acceleration = ((spawn rate)*(delay)*(update time)/(1000)-1)*(15)/t
        # spawn rate (acceleration, time in seconds)  = (1000*(acceleration*1/15time + 1)) / (delay * updatetime in ms) (units: grunts / sec)
        # velocity = acceleration*1/15*time + 1
        # note 1/15 = 450 * update time 
        # note assumes 30 frames per second (update time = 0.33)
        self.spawn_acceleration_ = 1 
        self.spawn_velocity_ = 1
        self.update_counter_ = 0

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
        #/// TEST FOR LINEAR
        #/// int grunt_count, update_count 
        #/// update_count += 1
        # For every update increase update counter by 1 
        self.update_counter_ += 1
        # If update counter reaches max, at vel=33, spawn rate = 5 grunts/sec
        if self.update_counter_ > 450 and self.spawn_velocity_ < 33:
            # Increase spawn velocity by spawn acceleration
            self.spawn_velocity_ += self.spawn_acceleration_
            # Reset update counter to 0
            self.update_counter_ = 0
        # Grunts now spawn at: spawn rate (acceleration, time in seconds)  = (1000*(acceleration*1/15time + 1)) / (delay * updatetime in ms) (units: grunts/sec)
        self.basic_grunt_spawn_timer_ += self.spawn_velocity_
        if self.basic_grunt_spawn_timer_ > self.basic_grunt_spawn_delay_:
            self.spawn_basic_grunt()
            self.basic_grunt_spawn_timer_ = 0
            #/// TEST FOR LINEAR
            #///grunt_count += 1
            #///print("Grunt count =" grunt_count)
            #///print("Update count =" update_count) 
        self.universe_.update(events)
