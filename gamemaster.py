import random

import pygame

from identification_assigner import IdentificationAssigner
from maincharacter import MainCharacter
from basic_grunt import BasicGrunt

class GameMaster():
	

	def __init__(self, gameboard):
		self.gameobject_id_assigner_ = IdentificationAssigner()
		self.gameboard_ = gameboard
		self.maincharacter_ = self.instantiate_main_character()
		self.enemies_ = [self.instantiate_basic_grunt()]
		self.basic_grunt_spawn_timer = 0
		self.basic_grunt_spawn_delay = 200

	def instantiate_main_character(self):
		starting_position = [self.gameboard_.width_*0.5, self.gameboard_.height_*0.9]
		return MainCharacter(starting_position, self.gameobject_id_assigner_.get_id())

	def instantiate_basic_grunt(self):
		starting_position = [self.gameboard_.width_*random.randint(200,800)/1000, 0]
		return BasicGrunt(starting_position, self.gameobject_id_assigner_.get_id())

	def update(self, events):
		self.maincharacter_.update(events, list(self.enemies_))
		
		self.basic_grunt_spawn_timer += 1
		if self.basic_grunt_spawn_timer > self.basic_grunt_spawn_delay:
			self.enemies_.append(self.instantiate_basic_grunt())
			self.basic_grunt_spawn_timer = 0

		for enemy in list(self.enemies_):
			if pygame.Rect((0,0), self.gameboard_.bounds_).collidepoint(enemy.position_) :
				enemy.update()
			else:
				self.enemies_.remove(enemy)

	def draw(self, screen):
		for enemy in self.enemies_:
			enemy.draw(screen)

		self.maincharacter_.draw(screen)
		self.maincharacter_.draw_ui(screen)
