import pygame

from gameobject import GameObject

class BasicGrunt(GameObject):
    def __init__(self, starting_position):
        self.position_ = starting_position
        self.ID_ = self.create_ID()
        self.size_ = 30
        self.speed_ = 0.3

    def update(self, events):
        self.position_ = (self.position_[0], self.position_[1]+self.speed_)