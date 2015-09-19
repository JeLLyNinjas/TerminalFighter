import pygame

class GameBoard():

	def __init__(self, bounds):
		self.bounds_ = bounds
		self.width_ = bounds[0]
		self.height_ = bounds[1]
		self.entities_ = []
		self.enemies_ = []
		self.maincharacter_ = None
		self.projectiles = []
