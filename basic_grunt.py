import pygame

class BasicGrunt():
    def __init__(self, starting_position, ID):
        self.position_ = starting_position
        self.ID_ = ID
        self.colour_ = 255, 0, 0
        self.size_ = 30
        self.speed_ = 0.3

    def draw(self, screen):
        visual_rect = pygame.Rect(self.position_[0]-self.size_/2, self.position_[1]-self.size_/2, 
                                       self.size_, self.size_)
        pygame.draw.rect(screen, self.colour_, visual_rect)

    def update(self, position=None):
        if position:
            self.position_ = position
        else:
            self.position_ = (self.position_[0], self.position_[1]+self.speed_)