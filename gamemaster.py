import pygame

from maincharacter import MainCharacter
from basic_grunt import BasicGrunt

class GameMaster():
	
	def __init__(self):
		self.maincharacter_ = MainCharacter((500, 800))
		self.enemies_ = [BasicGrunt((800	, 50))]

	def update(self, events):
		self.maincharacter_.update(events)
		for enemy in self.enemies_:
			enemy.update()

	def draw(self, screen):
		self.maincharacter_.draw(screen)
		for enemy in self.enemies_:
			enemy.draw(screen)

		self.maincharacter_.draw_ui(screen)
