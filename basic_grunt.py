import pygame

class BasicGrunt():
    def __init__(self, starting_position):
        print("Creating basic grunt")
        self.colour_ = 255, 0, 0
        self.position_ = starting_position
        self.size_ = 40
        self.speed_ = 1

    def draw(self, screen):
        visual_rect = pygame.Rect(self.position_[0]-self.size_/2, self.position_[1]-self.size_/2, 
                                       self.size_, self.size_)
        pygame.draw.rect(screen, self.colour_, visual_rect)

    def update(self, position=None):
        if position:
            self.position_ = position
        else:
            self.position_ = (self.position_[0], self.position_[1]+self.speed_)