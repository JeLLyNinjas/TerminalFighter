import pygame

from gameobject import GameObject


class BasicGrunt(GameObject):

    def __init__(self, starting_position):
        self.position_ = starting_position

        self.ID_ = self.create_ID()
        self.size_ = 15
        self.speed_ = 0.5

    """
    Access Functions
    """

    def collision_box(self):
        return pygame.Rect(self.position_[0]-self.size_/2,
                           self.position_[1]-self.size_/2,
                           self.size_, self.size_)

    """
    Update Functions
    """

    def update(self, events):
        self.position_ = (self.position_[0], self.position_[1]+self.speed_)
