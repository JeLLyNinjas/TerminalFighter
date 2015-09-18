import pygame

from rifle import Rifle
from homing_missles import HomingMissles

pygame.font.init()
UI_FONT = pygame.font.SysFont("monospace", 20)

BLACK = 0, 0, 0
RED = 255, 0, 0

EVENT_KEY_1 = 49
EVENT_KEY_5 = 53

class MainCharacter():

    def __init__(self, starting_position):
        self.colour_ = 0, 255, 0
        self.position_ = starting_position
        self.size_ = 50
        self.weapons_ = [Rifle(), HomingMissles()]
        self.selected_weapon_index_ = 0

    def draw(self, screen):
        visual_rect = pygame.Rect(self.position_[0]-self.size_/2, self.position_[1]-self.size_/2, 
                                       self.size_, self.size_)
        pygame.draw.rect(screen, self.colour_, visual_rect)

    def draw_ui(self, screen):
        for i, weapon in enumerate(self.weapons_):
            
            ui_weapon_text_colour = BLACK 
            if i == self.selected_weapon_index_:
                ui_weapon_text_colour = RED

            weapon_label = UI_FONT.render(str(i+1) + '. ' + weapon.NAME_, 1, ui_weapon_text_colour)
            screen.blit(weapon_label, (10, i*20))


    def update(self, events, position=None):
        if position:
           self.position_ = position

        self.update_weapon_selection(events)

    def update_weapon_selection(self, events):
        for event in events:
            if event.type == pygame.KEYDOWN:
                if event.key in range(EVENT_KEY_1, EVENT_KEY_1 + len(self.weapons_)):
                    self.selected_weapon_index_ = event.key - EVENT_KEY_1





