import pygame

class MainCharacter():

    def __init__(self):
        self.colour_ = (0, 128, 255)
        self.position_ = 500, 800
        self.size_ = 50
        self.visual_rect = pygame.Rect(self.position_[0]-self.size_/2, self.position_[1]-self.size_/2, 
                                       self.size_, self.size_)
    def draw(self, screen):
        pygame.draw.rect(screen, self.colour_, self.visual_rect)