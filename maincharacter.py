import pygame

from gameobject import GameObject
from homing_missiles import HomingMissiles
from rifle import Rifle
from shield import Shield

BLACK = 0, 0, 0
CYAN = 0, 255, 255
GREEN = 0, 255, 0
RED = 255, 0, 0
WHITE = 255, 255, 255
YELLOW = 255, 255, 0
EVENT_KEY_1 = 49
EVENT_KEY_5 = 53


class MainCharacter(GameObject):

    def __init__(self, starting_position, universe, screen_size):
        self.position_ = starting_position
        self.universe_ = universe
        self.font_size_ = 22
        self.id_ = self.create_ID()
        self.max_health_ = 100
        self.selected_weapon_index_ = 0
        self.shield_ = Shield(self.position_, 100)
        self.size_ = 20
        self.text_antialias_ = 1
        self.ui_font_ = pygame.font.SysFont("monospace", self.font_size_)
        self.weapon_label_x_spacing_ = 5
        self.weapon_label_y_spacing_ = 10
        self.weapons_ = [Rifle(self.universe_, screen_size),
                         HomingMissiles(self.universe_, screen_size)]

        self.current_weapon_ = self.weapons_[self.selected_weapon_index_]
        self.health_ = self.max_health_

    """
    Access Functions
    """

    def collision_box(self):
        if self.shield_.active_:
            return self.shield_.collision_box()
        else:
            return pygame.Rect(self.position_[0]-self.size_/2,
                           self.position_[1]-self.size_/2,
                           self.size_,
                           self.size_)

    def take_damage(self, damage):
        if self.shield_.active_:
            self.shield_.disable_shield()
        else:
            if damage <= 0:
                print("WARNING MainCharacter taking " + str(damage) + " damage")
                print("Disregarding non positive damage")
            elif damage >= self.health_:
                self.health_ = 0
            else:
                self.health_ -= damage
        # print("MainCharacter health is " + str(self.health_))

    """
    Update Functions
    """

    def update(self, events):
        self.update_weapon_selection(events)
        self.current_weapon_ = self.weapons_[self.selected_weapon_index_]
        self.current_weapon_.update(events)
        self.shield_.update(events)

    def update_weapon_selection(self, events):
        for event in events:
            if event.type == pygame.KEYDOWN:
                if event.key in range(EVENT_KEY_1,
                                      EVENT_KEY_1+len(self.weapons_)):
                    self.selected_weapon_index_ = event.key - EVENT_KEY_1

    """
    Draw Functions
    """

    def draw_view(self, screen):
        self.draw_ui(screen)
        self.current_weapon_.draw(screen)


    def draw_ui(self, screen):
        self.draw_shield_ui(screen)
        self.draw_weapons_ui(screen)
        self.draw_health_ui(screen)


    def draw_weapons_ui(self, screen):
        for i, weapon in enumerate(self.weapons_):
            ui_weapon_text_colour = WHITE
            if i == self.selected_weapon_index_:
                ui_weapon_text_colour = RED

            weapon_label = self.ui_font_.render(str(i+1) + ". " + weapon.NAME_,
                                                self.text_antialias_,
                                                ui_weapon_text_colour)
            screen.blit(weapon_label,
                        (self.weapon_label_x_spacing_,
                         (i*(weapon_label.get_height()))))

    def draw_health_ui(self, screen):
        if self.health_ > self.max_health_ * 0.5:
            health_text_color = GREEN
        elif self.health_ > self.max_health_ * 0.1:
            health_text_color = YELLOW
        else:
            health_text_color = RED

        health_label = self.ui_font_.render("HEALTH " + str(self.health_) + " ",
                                            self.text_antialias_,
                                            health_text_color)
        screen.blit(health_label,
                    ((screen.get_width()-health_label.get_width())/2,
                     screen.get_height()*0.97-health_label.get_height()))

    def draw_shield_ui(self, screen):
        if self.shield_.active_:
            shield_graphic = pygame.Surface((self.shield_.radius_, self.shield_.radius_))
            pygame.draw.circle(shield_graphic, WHITE, (int(self.shield_.radius_/2),int(self.shield_.radius_/2)), int(self.shield_.radius_/2))
            pygame.draw.circle(shield_graphic, CYAN, (int(self.shield_.radius_/2),int(self.shield_.radius_/2)), int(self.shield_.radius_/2),5)
            shield_graphic.set_colorkey((255,0,255))
            shield_graphic.set_alpha(50)
            screen.blit(shield_graphic, (self.shield_.position_[0]-self.shield_.radius_/2, (self.shield_.position_[1]-self.shield_.radius_/2)))
