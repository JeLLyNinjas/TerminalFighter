import random

import pygame

from maincharacter import MainCharacter
from basic_grunt import BasicGrunt


class GameMaster():

	def __init__(self, universe):
		self.universe_ = universe
		self.basic_grunt_spawn_timer = 0
		self.basic_grunt_spawn_delay = 200
		self.spawn_main_character()
		self.spawn_basic_grunt()

	def spawn_main_character(self):
		starting_position = [self.universe_.width_*0.5, self.universe_.height_*0.9]
		the_main_character = MainCharacter(starting_position, self.universe_)
		self.universe_.create_main_character(the_main_character)

	def spawn_basic_grunt(self):
		starting_position = [self.universe_.width_*random.randint(200,800)/1000, 0]
		the_basic_grunt = BasicGrunt(starting_position)
		self.universe_.create_enemy(the_basic_grunt)

	def update(self, events):
		self.basic_grunt_spawn_timer += 1
		if self.basic_grunt_spawn_timer > self.basic_grunt_spawn_delay:
			self.spawn_basic_grunt()
			self.basic_grunt_spawn_timer = 0
		
		self.universe_.update(events)

	def draw(self, screen):
		self.universe_.main_character_.draw_view(screen)
		self.universe_.main_character_.draw_ui(screen)
