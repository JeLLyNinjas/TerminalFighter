import pygame

from rifle import Rifle
from homing_missles import HomingMissles

pygame.font.init()
UI_FONT = pygame.font.SysFont("monospace", 20)
BLACK = 0, 0, 0

class MainCharacter():

    def __init__(self, starting_position):
        self.colour_ = 0, 255, 0
        self.position_ = starting_position
        self.size_ = 50
        self.weapons_ = [Rifle(), HomingMissles()]
        self.selected_weapon_index = 0 
        
    def draw(self, screen):
        visual_rect = pygame.Rect(self.position_[0]-self.size_/2, self.position_[1]-self.size_/2, 
                                       self.size_, self.size_)
        pygame.draw.rect(screen, self.colour_, visual_rect)

    def draw_ui(self, screen):
        for i, weapon in enumerate(self.weapons_):
            weapon_label = UI_FONT.render(str(i+1) + '. ' + weapon.NAME_, 1, BLACK)
            screen.blit(weapon_label, (10, i*20))


    def update(self, position=None):
        if position:
           self.position_ = position 
           


