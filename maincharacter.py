import pygame

from rifle import Rifle
from homing_missiles import HomingMissiles
from gameobject import GameObject

UI_FONT = pygame.font.SysFont("monospace", 20)

BLACK = 0, 0, 0
RED = 255, 0, 0
WHITE = 255, 255, 255

EVENT_KEY_1 = 49
EVENT_KEY_5 = 53

class MainCharacter(GameObject):

    def __init__(self, starting_position, universe):
        self.position_ = starting_position
        self.universe_ = universe
        self.ID_ = self.create_ID() 
        self.size_ = 40
        self.weapons_ = [Rifle(self.universe_), HomingMissiles(self.universe_)]
        self.selected_weapon_index_ = 0
        self.current_weapon_ = self.weapons_[self.selected_weapon_index_]

    def draw_view(self, screen):
        self.current_weapon_.draw(screen)
        self.draw_ui(screen)
        
    def draw_ui(self, screen):
        for i, weapon in enumerate(self.weapons_):
            
            ui_weapon_text_colour = WHITE 
            if i == self.selected_weapon_index_:
                ui_weapon_text_colour = RED

            weapon_label = UI_FONT.render(str(i+1) + '. ' + weapon.NAME_, 1, ui_weapon_text_colour)
            screen.blit(weapon_label, (10, i*20))

    def update(self, events, position=None):
        if position:
           self.position_ = position

        self.update_weapon_selection(events)
        
        self.current_weapon_ = self.weapons_[self.selected_weapon_index_]
        self.current_weapon_.update(events)

    def update_weapon_selection(self, events):
        for event in events:
            if event.type == pygame.KEYDOWN:
                if event.key in range(EVENT_KEY_1, EVENT_KEY_1 + len(self.weapons_)):
                    self.selected_weapon_index_ = event.key - EVENT_KEY_1



