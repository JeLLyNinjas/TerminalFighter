import pygame

from identification_assigner import IdentificationAssigner
from maincharacter import MainCharacter
from basic_grunt import BasicGrunt

class GameMaster():
	
	def __init__(self):
		self.gameobject_id_assigner_ = IdentificationAssigner()
		self.maincharacter_ = MainCharacter((500, 600), self.gameobject_id_assigner_.get_id())
		self.enemies_ = [BasicGrunt((800, 100), self.gameobject_id_assigner_.get_id())]

	def update(self, events):
		self.maincharacter_.update(events, self.enemies_)
		for enemy in list(self.enemies_):
			if pygame.Rect((0,0), (1000,700)).collidepoint(enemy.position_) :
				enemy.update()
			else:
				self.enemies_.remove(enemy)

	def draw(self, screen):
		self.maincharacter_.draw(screen)
		for enemy in self.enemies_:
			enemy.draw(screen)

		self.maincharacter_.draw_ui(screen)
