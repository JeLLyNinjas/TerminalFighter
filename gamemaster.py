import pygame

from maincharacter import MainCharacter
from basic_grunt import BasicGrunt

class GameMaster():
	
	def __init__(self):
		self.maincharacter_ = MainCharacter((500, 800))
		self.enemies_ = [BasicGrunt((300, 50))]

	def update(self):
		self.maincharacter_.update()
		for enemy in self.enemies_:
			enemy.update()

	def draw(self, screen):
		self.maincharacter_.draw(screen)
		for enemy in self.enemies_:
			enemy.draw(screen)
