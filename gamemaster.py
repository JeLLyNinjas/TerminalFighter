import pygame

from maincharacter import MainCharacter

class GameMaster():
	
	def __init__(self):
		self.maincharacter_ = MainCharacter()

	def update(self):
		pass

	def draw(self, screen):
		self.maincharacter_.draw(screen)
