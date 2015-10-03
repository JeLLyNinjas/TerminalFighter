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
        self.ui_font_ = pygame.font.SysFont("monospace", self.font_size_*DRAWING_SCALE)
        self.word_generator_ = WordGenerator()
        self.word_length_min_ = 12
        self.word_length_range_ = 1
        self.targetted_enemies_ = list() 

        self.target_color_ = WHITE
        
    def get_target_id(self, terminal_input): 
        target_ID = None
        for enemy in self.universe_.enemies(): 
            if terminal_input == self.target_tags_[enemy.ID_]:
                target_ID = self.ids_for_target_tags_[terminal_input]
                break
        return target_ID  

    def get_target_position(self, current_text): 
        target_ID =  self.get_target_id(current_text)
        if target_ID: 
            target_position = self.universe_.enemies_[target_ID].position_  
            return target_position 
        else:
            return None
    
    """
    Update Functions
    """
    def update(self, events):
        for enemy in self.universe_.enemies():
            if enemy.ID_ not in self.target_tags_:
                new_word = self.word_generator_.request_word(self.word_length_min_, self.word_length_range_)
                self.target_tags_[enemy.ID_] = new_word
                self.ids_for_target_tags_[new_word] = enemy.ID_ 

        for event in events:
            if event.type == pygame.KEYDOWN:
                if event.key == EVENT_KEY_ENTER:
                    target_id = self.get_target_id(self.current_text_)
                    if target_id and self.current_text_ != "fire":
                        if len(self.targetted_enemies_) == 5:
                            untargetted_enemy = self.targetted_enemies_.pop(0)
                        self.targetted_enemies_.append(self.universe_.enemies_[target_id])
                       
                    if len(self.targetted_enemies_) > 0 and self.current_text_ == "fire":
                        for enemy in self.targetted_enemies_:
                            homing_missiles_projectile = HomingMissilesProjectile(self.universe_.main_character_.position_, enemy)
                            self.universe_.create_friendly_projectile(homing_missiles_projectile)
                        self.targetted_enemies_.clear()

                    self.current_text_ = ""

                if event.key == EVENT_KEY_BACKSPACE:
                    self.current_text_ = self.current_text_[:-1]
                elif event.key in range(EVENT_KEY_a, EVENT_KEY_z+1):
                    if len(self.current_text_)<= self.targeting_terminal_.max_word_size_:
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
        
        self.draw_friendly_projectiles(screen)
        self.draw_targets(screen)

    def draw_background(self, screen):
        pygame.draw.rect(screen, BLACK, pygame.Rect((0, 0), screen.get_size()))

    def draw_entities(self, screen):
        for enemy in self.universe_.enemies():
            enemy_rect = pygame.Rect((enemy.position_[0]-enemy.size_/2) * self.DRAWING_SCALE_,
                                     (enemy.position_[1]-enemy.size_/2) * self.DRAWING_SCALE_,
                                     enemy.size_ * self.DRAWING_SCALE_,
                                     enemy.size_ * self.DRAWING_SCALE_)
            pygame.draw.rect(screen, self.enemy_color_, enemy_rect)

        main_character = self.universe_.main_character_
        main_character_rect = pygame.Rect((main_character.position_[0]-main_character.size_/2) * self.DRAWING_SCALE_,
                                          (main_character.position_[1]-main_character.size_/2) * self.DRAWING_SCALE_,
                                          main_character.size_ * self.DRAWING_SCALE_,
                                          main_character.size_ * self.DRAWING_SCALE_)
        pygame.draw.rect(screen, self.main_character_color_, main_character_rect)
        self.draw_friendly_projectiles(screen)

    def draw_target_tags(self, screen):
        for enemy in self.universe_.enemies():
            target_tag_word = self.target_tags_[enemy.ID_]
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
        
    def draw_targets(self, screen):
        for enemy in self.targetted_enemies_: 
            enemy_rect = pygame.Rect((enemy.position_[0]-enemy.size_/2) * self.DRAWING_SCALE_,
                                     (enemy.position_[1]-enemy.size_/2) * self.DRAWING_SCALE_,
                                     enemy.size_ * self.DRAWING_SCALE_,
                                     enemy.size_ * self.DRAWING_SCALE_)

            target_tag_word = self.target_tags_[enemy.ID_]
            target_tag_label = self.ui_font_.render(target_tag_word, 
                                                    self.text_antialias_, 
                                                    self.target_color_)
            width = self.ui_font_.size(target_tag_word)[0]
            screen.blit(target_tag_label,
                        (enemy.position_[0] * self.DRAWING_SCALE_ - (width/2),
                        (enemy.position_[1] * self.DRAWING_SCALE_ + enemy.size_/2) + (self.target_tag_y_spacing_ * self.DRAWING_SCALE_)))
            pygame.draw.rect(screen, self.target_color_, enemy_rect)

class HomingMissilesProjectile(GameObject): 

    def __init__(self, initial_position, enemy):
        self.ID_ = self.create_ID()
        self.position_ = initial_position
        self.targetted_enemy_ = enemy
        self.speed_ = 15
        self.size_ = 5
        self.velocity_ = self.calculate_trajectory(self.position_, self.targetted_enemy_.position_)
        
    def calculate_trajectory(self, initial_position, target_position):
        x_distance = target_position[0] - initial_position[0]
        y_distance = target_position[1] - initial_position[1]
        distance = math.sqrt(x_distance**2 + y_distance**2)
        
        x_velocity = (x_distance * self.speed_) / distance
        y_velocity = (y_distance * self.speed_) / distance

        return (x_velocity, y_velocity)

    def update(self,events):
        target_position_ = self.targetted_enemy_.position_
        self.velocity_ = self.calculate_trajectory(self.position_, target_position_)
        self.position_ = (self.position_[0] + self.velocity_[0], self.position_[1] + self.velocity_[1])


    def collision_box(self):
        return pygame.Rect(self.position_[0]-self.size_/2,
                        self.position_[1]-self.size_/2,
                        self.size_,
                        self.size_)
            
            
class HomingMissiles():
            
    def __init__(self, universe, DRAWING_SCALE):
        self.universe_ = universe
        self.DRAWING_SCALE_ = DRAWING_SCALE

        self.NAME_ = "Homing Missiles"
        self.targeting_system = HomingMissilesTargetingSystem(universe, DRAWING_SCALE)

    def update(self, events):
        self.targeting_system.update(events)

    def draw(self, screen):
        self.targeting_system.draw(screen)
