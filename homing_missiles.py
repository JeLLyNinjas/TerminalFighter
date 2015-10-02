import math

import pygame

from gameobject import GameObject
from targeting_terminal import TargetingTerminal
from wordgenerator import WordGenerator

pygame.font.init()

BLACK = 0, 0, 0
GREEN = 0, 255, 0
WHITE = 255, 255, 255
YELLOW = 255, 255, 0

EVENT_KEY_a = 97
EVENT_KEY_BACKSPACE = 8
EVENT_KEY_ENTER = 13
EVENT_KEY_z = 122


class HomingMissilesTargetingSystem():

    def __init__(self, universe, DRAWING_SCALE):
        self.DRAWING_SCALE_ = DRAWING_SCALE
        self.universe_ = universe

        self.current_text_ = ""
        self.enemy_color_ = YELLOW
        self.font_size_ = 15
        self.ids_for_target_tags_ = dict()
        self.main_character_color_ = GREEN
        self.projectile_color_ = WHITE
        self.target_tag_y_spacing_ = 5
        self.target_tags_ = dict()
        self.targeting_terminal_ = TargetingTerminal(DRAWING_SCALE)
        self.text_antialias_ = 1
        self.ui_font_ = pygame.font.SysFont("monospace", 
        									self.font_size_*DRAWING_SCALE)
        self.word_generator_ = WordGenerator()
        self.word_length_min_ = 12
        self.word_length_range_ = 1

    def get_target_id(self, terminal_input):
        for enemy in self.universe_.enemies():
            if terminal_input == self.target_tags_[enemy.id_]:
                return self.ids_for_target_tags_[terminal_input]
        return None

    def get_target_position(self, current_text):
        if self.get_target_id(current_text):
            return self.universe_.enemies_[target_ID].position_
        else:
            return None

    """
    Update Functions
    """

    def update(self, events):
        for enemy in self.universe_.enemies():
            if enemy.id_ not in self.target_tags_:
                new_word = self.word_generator_.request_word(self.word_length_min_, 
                	 										 self.word_length_range_)
                self.target_tags_[enemy.id_] = new_word
                self.ids_for_target_tags_[new_word] = enemy.id_

        for event in events:
            if event.type == pygame.KEYDOWN:
                if event.key == EVENT_KEY_ENTER:
                    target_location = self.get_target_position(self.current_text_)
                    self.current_text_ = ""
                elif event.key == EVENT_KEY_BACKSPACE:
                    self.current_text_ = self.current_text_[:-1]
                elif event.key in range(EVENT_KEY_a, EVENT_KEY_z+1):
                    if len(self.current_text_) <= self.targeting_terminal_.max_word_size_:
                        self.current_text_ += chr(event.key)

        self.targeting_terminal_.update(self.current_text_)

    """
    Draw Functions
    """

    def draw(self, screen):
        self.draw_background(screen)
        self.draw_entities(screen)
        self.draw_target_tags(screen)
        self.targeting_terminal_.draw_terminal(screen)

    def draw_background(self, screen):
        pygame.draw.rect(screen, BLACK, pygame.Rect((0, 0), screen.get_size()))

    def draw_entities(self, screen):
        self.draw_friendly_projectiles(screen)
        self.draw_enemies(screen)
        self.draw_target_tags(screen)
        self.draw_main_character(screen)

    def draw_enemies(self, screen):
        for enemy in self.universe_.enemies():
            enemy_rect = pygame.Rect((enemy.position_[0]-enemy.size_/2) * self.DRAWING_SCALE_,
                                     (enemy.position_[1]-enemy.size_/2) * self.DRAWING_SCALE_,
                                     enemy.size_ * self.DRAWING_SCALE_,
                                     enemy.size_ * self.DRAWING_SCALE_)
            pygame.draw.rect(screen, self.enemy_color_, enemy_rect)

    def draw_main_character(self, screen):
        main_character = self.universe_.main_character_
        main_character_rect = pygame.Rect((main_character.position_[0]-main_character.size_/2) * self.DRAWING_SCALE_,
                                          (main_character.position_[1]-main_character.size_/2) * self.DRAWING_SCALE_,
                                          main_character.size_ * self.DRAWING_SCALE_,
                                          main_character.size_ * self.DRAWING_SCALE_)
        pygame.draw.rect(screen, self.main_character_color_, main_character_rect)

    def draw_target_tags(self, screen):
        for enemy in self.universe_.enemies():
            target_tag_word = self.target_tags_[enemy.id_]
            target_tag_label = self.ui_font_.render(target_tag_word,
                                                    self.text_antialias_,
                                                    self.enemy_color_)
            width = self.ui_font_.size(target_tag_word)[0]
            screen.blit(target_tag_label,
                        (enemy.position_[0] * self.DRAWING_SCALE_ - (width/2),
                        (enemy.position_[1] * self.DRAWING_SCALE_ + enemy.size_/2) + (self.target_tag_y_spacing_ * self.DRAWING_SCALE_)))

    def draw_friendly_projectiles(self, screen):
        for projectile in self.universe_.friendly_projectiles():
            projectile_rect = pygame.Rect((projectile.position_[0]-projectile.size_/2) * self.DRAWING_SCALE_,
                                          (projectile.position_[1]-projectile.size_/2) * self.DRAWING_SCALE_,
                                          projectile.size_ * self.DRAWING_SCALE_,
                                          projectile.size_ * self.DRAWING_SCALE_)
            pygame.draw.rect(screen, self.projectile_color_, projectile_rect)



class HomingMissiles():

    def __init__(self, universe, DRAWING_SCALE):
        self.universe_ = universe
        self.DRAWING_SCALE_ = DRAWING_SCALE

        self.NAME_ = "Homing Missiles"
        self.targeting_system = HomingMissilesTargetingSystem(
            universe, DRAWING_SCALE)

    def update(self, events):
        self.targeting_system.update(events)

    def draw(self, screen):
        self.targeting_system.draw(screen)
