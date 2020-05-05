import pygame

class Shield():
	def __init__(self, position, radius):
		self.active_ = 1
		self.disabled_waiting_time = 200
		self.position_ = position
		self.radius_ = radius

		self.disabled_counter_ = self.disabled_waiting_time

	def collision_box(self):
		return pygame.Rect(self.position_[0]-self.radius_/2,
						   self.position_[1]-self.radius_/2,
						   self.radius_,
						   self.radius_)
	def disable_shield(self):
		self.active_ = 0

	def update(self, events):
		if not self.active_ and self.disabled_counter_:
			self.disabled_counter_ = self.disabled_counter_ - 1
		elif not self.active_ and not self.disabled_counter_:
			self.disabled_counter_ = self.disabled_waiting_time
			self.active_ = 1
