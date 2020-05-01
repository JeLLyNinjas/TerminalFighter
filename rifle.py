import math

import pygame

from gameobject import GameObject
from targeting_terminal import TargetingTerminal
from wordgenerator import WordGenerator

pygame.font.init()

BLACK = 0, 0, 0
GREEN = 0, 255, 0
LIGHT_BLUE = 100, 100, 255
RED = 255, 0, 0
WHITE = 255, 255, 255
GRAY = 88, 88, 88

EVENT_KEY_a = 97
EVENT_KEY_BACKSPACE = 8
EVENT_KEY_ENTER = 13
EVENT_KEY_z = 122


class RifleTargetingSystem():

    def __init__(self, universe):
        self.universe_ = universe

        self.current_text_ = ""
        self.default_enemy_color_ = RED
        self.enemy_colors_ = {"NotSoBasicGrunt" : LIGHT_BLUE}
        self.font_size_ = 15
        self.ids_for_target_tags_ = dict()
        self.main_character_color_ = GREEN
        self.projectile_color_ = WHITE
        self.target_tag_y_spacing_ = 5
        self.target_tag_rect_spacing_ = 2
        self.target_tags_ = dict()
        self.targeting_terminal_ = TargetingTerminal()
        self.text_antialias_ = 1
        self.ui_font_ = pygame.font.SysFont("monospace", self.font_size_)
        self.word_generator_ = WordGenerator()
        self.word_length_min_ = 3
        self.word_length_range_ = 3

    def get_target_id(self, terminal_input):
        for enemy in self.universe_.enemies():
            if terminal_input == self.target_tags_[enemy.id_]:
                return self.ids_for_target_tags_[terminal_input]
        return None

    def get_target_position(self, current_text):
        target_id = self.get_target_id(current_text)
        if target_id:
            return self.universe_.enemies_[target_id].position_
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
                    if target_location:
                        rifle_projectile = RifleProjectile(self.universe_.main_character_.position_,
                                                           target_location,
                                                           self.universe_)
                        self.universe_.create_friendly_projectile(rifle_projectile)
                    else:
                        self.targeting_terminal_.notify_misfire()

                if event.key == EVENT_KEY_BACKSPACE:
                    self.current_text_ = self.current_text_[:-1]
                elif event.key in range(EVENT_KEY_a, EVENT_KEY_z+1):
                    if len(self.current_text_) <= self.targeting_terminal_.max_word_size_:
                        self.current_text_ += chr(event.key)

        self.targeting_terminal_.update(self.current_text_)

    """
    Draw Functions
    """

    def draw(self, screen):
        self.draw_entities(screen)
        self.draw_target_tags(screen)
        self.targeting_terminal_.draw_terminal(screen)

    def draw_entities(self, screen):
        self.draw_friendly_projectiles(screen)
        self.draw_enemy_projectiles(screen)
        self.draw_enemies(screen)
        self.draw_target_tags(screen)
        self.draw_maincharacter(screen)

    def draw_enemies(self, screen):
        for enemy in self.universe_.enemies():
            enemy_color = self.enemy_colors_.get(enemy.get_type(), self.default_enemy_color_)
            enemy_rect = pygame.Rect(enemy.position_[0]-enemy.size_/2,
                                     enemy.position_[1]-enemy.size_/2,
                                     enemy.size_,
                                     enemy.size_)
            pygame.draw.rect(screen, enemy_color, enemy_rect)

    def draw_maincharacter(self, screen):
        main_character = self.universe_.main_character_
        main_character_rect = pygame.Rect(main_character.position_[0]-main_character.size_/2,
                                          main_character.position_[1]-main_character.size_/2,
                                          main_character.size_,
                                          main_character.size_)
        pygame.draw.rect(screen, self.main_character_color_, main_character_rect)

    def draw_target_tags(self, screen):
        for enemy in self.universe_.enemies():
            enemy_color = self.enemy_colors_.get(enemy.get_type(), self.default_enemy_color_)
            target_tag_word = self.target_tags_[enemy.id_]
            target_tag_label = self.ui_font_.render(target_tag_word,
                                                    self.text_antialias_,
                                                    enemy_color)
            width = self.ui_font_.size(target_tag_word)[0]
            height = self.ui_font_.size(target_tag_word)[1]

            target_tag_x = enemy.position_[0] - (width/2)
            target_tag_y = (enemy.position_[1] + enemy.size_/2 +(self.target_tag_y_spacing_))

            pygame.draw.rect(screen, BLACK, (target_tag_x-self.target_tag_rect_spacing_, target_tag_y-self.target_tag_rect_spacing_,
                            width+4, height+2), 0) # Filled rect. Dimensions of rect adjusted to contain the word
            pygame.draw.rect(screen, GRAY, (target_tag_x-self.target_tag_rect_spacing_, target_tag_y-self.target_tag_rect_spacing_,
                            width+4, height+2), 1) # Outline rect.  Dimensions of rect adjusted to contain the word

            screen.blit(target_tag_label, (target_tag_x, target_tag_y))

    def draw_friendly_projectiles(self, screen):
        for projectile in self.universe_.friendly_projectiles():
            projectile_rect = pygame.Rect(projectile.position_[0]-projectile.size_/2,
                                          projectile.position_[1]-projectile.size_/2,
                                          projectile.size_,
                                          projectile.size_)
            pygame.draw.rect(screen, self.projectile_color_, projectile_rect)

    def draw_enemy_projectiles(self, screen):
        for projectile in self.universe_.enemy_projectiles():
            projectile_rect = pygame.Rect(projectile.position_[0]-projectile.size_/2,
                                          projectile.position_[1]-projectile.size_/2,
                                          projectile.size_,
                                          projectile.size_)
            pygame.draw.rect(screen, self.default_enemy_color_, projectile_rect)


class RifleProjectile(GameObject):

    def __init__(self, initial_position, target_position, universe):
        self.id_ = self.create_ID()
        self.listeners_ = []
        self.position_ = initial_position
        self.size_ = 5
        self.speed_ = 15
        self.speed_ = 17
        self.universe_ = universe
        self.velocity_ = self.calculate_trajectory(initial_position,
                                                   target_position)

    def calculate_trajectory(self, initial_position, target_position):
        x_distance = target_position[0] - initial_position[0]
        y_distance = target_position[1] - initial_position[1]
        distance = math.sqrt(x_distance**2 + y_distance**2)

        x_velocity = (x_distance * self.speed_) / distance
        y_velocity = (y_distance * self.speed_) / distance

        return x_velocity, y_velocity

    def check_collisions(self):
        collisions = self.universe_.get_collisions(self)

        if collisions:
            collisions[0].take_damage(1000)
            self.report_destroyed()

    def update(self, events):
        self.check_collisions()
        self.position_ = (self.position_[0] + self.velocity_[0],
                          self.position_[1] + self.velocity_[1])

    def collision_box(self):
        return pygame.Rect(self.position_[0]-self.size_/2,
                           self.position_[1]-self.size_/2,
                           self.size_,
                           self.size_)

    """
    Listener Functions
    """

    def report_destroyed(self):
        for listener in self.listeners_:
            listener.reported_destroyed(self)

    def register(self, listeners):
        self.listeners_.append(listeners)


class Rifle():

    def __init__(self, universe):
        self.universe_ = universe

        self.NAME_ = "Rifle"
        self.targeting_system = RifleTargetingSystem(universe)

    def update(self, events):
        self.targeting_system.update(events)

    def draw(self, screen):
        self.targeting_system.draw(screen)
