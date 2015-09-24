import pygame

from gameobject import GameObject
from homing_missiles import HomingMissiles
from rifle import Rifle


BLACK = 0, 0, 0
RED = 255, 0, 0
WHITE = 255, 255, 255

EVENT_KEY_1 = 49
EVENT_KEY_5 = 53


class MainCharacter(GameObject):

    def __init__(self, starting_position, universe, DRAWING_SCALE):
        self.DRAWING_SCALE_ = DRAWING_SCALE
        self.position_ = starting_position
        self.universe_ = universe

        self.ID_ = self.create_ID()
        self.selected_weapon_index_ = 0
        self.size_ = 20
        self.ui_font = pygame.font.SysFont("monospace", 15 * DRAWING_SCALE)
        self.weapons_ = [Rifle(self.universe_, DRAWING_SCALE), 
                         HomingMissiles(self.universe_, DRAWING_SCALE)]
        
        self.current_weapon_ = self.weapons_[self.selected_weapon_index_]

    """
    Access Functions
    """

    def collision_box(self):
        return pygame.Rect(self.position_[0]-self.size_/2,
                           self.position_[1]-self.size_/2,
                           self.size_, 
                           self.size_)

    """
    Update Functions
    """

    def update(self, events, position=None):
        if position:
            self.position_ = position

        self.update_weapon_selection(events)

        self.current_weapon_ = self.weapons_[self.selected_weapon_index_]
        self.current_weapon_.update(events)

    def update_weapon_selection(self, events):
        for event in events:
            if event.type == pygame.KEYDOWN:
                if event.key in range(EVENT_KEY_1, EVENT_KEY_1+len(self.weapons_)):
                    self.selected_weapon_index_ = event.key - EVENT_KEY_1

    """
    Draw Functions
    """

    def draw_view(self, screen):
        self.current_weapon_.draw(screen)
        self.draw_ui(screen)

    def draw_ui(self, screen):
        for i, weapon in enumerate(self.weapons_):
            ui_weapon_text_colour = WHITE
            if i == self.selected_weapon_index_:
                ui_weapon_text_colour = RED

            weapon_label = self.ui_font.render(
                str(i+1) + ". " + weapon.NAME_, 1, ui_weapon_text_colour)
            screen.blit(
                weapon_label, (5 * self.DRAWING_SCALE_, (i*10) * self.DRAWING_SCALE_))
