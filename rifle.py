import pygame
import math

from targeting_terminal import TargetingTerminal
from wordgenerator import WordGenerator
from gameobject import GameObject
pygame.font.init()

BLACK = 0, 0, 0
BLUE = 0, 0, 255
GREEN = 0, 255, 0
RED = 255, 0, 0
WHITE = 255, 255, 255

EVENT_KEY_a = 97
EVENT_KEY_BACKSPACE = 8
EVENT_KEY_ENTER = 13
EVENT_KEY_z = 122


class RifleTargetingSystem():

    def __init__(self, universe, DRAWING_SCALE):
        self.DRAWING_SCALE_ = DRAWING_SCALE
        self.universe_ = universe

        self.current_text_ = ""
        self.enemy_color_ = RED
        self.projectile_color_ = WHITE 
        self.font_size_ = 15
        self.main_character_color_ = GREEN
        self.target_tags_ = dict()
        self.ids_for_target_tags_ = dict() 
        self.current_text_ = ""
        self.target_tag_y_spacing_ = 5
        self.targeting_terminal_ = TargetingTerminal(DRAWING_SCALE)
        self.text_antialias_ = 1
        self.ui_font_ = pygame.font.SysFont("monospace", self.font_size_*DRAWING_SCALE)
        self.word_generator_ = WordGenerator()
        self.word_length_min_ = 3
        self.word_length_range = 3

    def getTargetID(self,input): 
        for enemy in self.universe_.enemies(): 
            target_tag_word = self.target_tags_[enemy.ID_]
            if(input == target_tag_word):
                target_ID = self.ids_for_target_tags_[input]
                break
            else:       # input does not exist 
                target_ID = -1
        return target_ID  

    def checkIfInputMatchesTargetTag(self): 
        target_ID =  self.getTargetID(self.current_text_)
        if (target_ID != -1): 
            target_position = self.universe_.enemies_[target_ID].position_  
            return target_position 
        else:
            return -1
    """
    Update Functions
    """
    def update(self, events):
        for enemy in self.universe_.enemies():
            if enemy.ID_ not in self.target_tags_:
                new_word = self.word_generator_.request_word(self.word_length_min_, self.word_length_range)
                self.target_tags_[enemy.ID_] = new_word
                self.ids_for_target_tags_[new_word] = enemy.ID_ 

        for event in events:
            if event.type == pygame.KEYDOWN:
                if event.key == EVENT_KEY_ENTER:
                    target_location = self.checkIfInputMatchesTargetTag()
                    self.current_text_ = ""
                    if (target_location == -1):
                        pass
                    else:
                        rifle_projectile = RifleProjectile(self.universe_.main_character_.position_, target_location, self.universe_)
                        self.universe_.create_friendly_projectile(rifle_projectile)
                    
                if event.key == EVENT_KEY_BACKSPACE:
                    self.current_text_ = self.current_text_[:-1]
                elif event.key in range(EVENT_KEY_a, EVENT_KEY_z+1):
                    self.current_text_ += event.unicode.lower()
                
        self.targeting_terminal_.update(events)

    """
    Draw Functions
    """

    def draw(self, screen):
        self.draw_background(screen)
        self.draw_entities(screen)
        self.draw_target_tags(screen)
        self.targeting_terminal_.draw_terminal(screen)
        self.draw_friendly_projectiles(screen)

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

        main_character = self.universe_.main_character_
        main_character_rect = pygame.Rect((main_character.position_[0]-main_character.size_/2) * self.DRAWING_SCALE_,
                                          (main_character.position_[1]-main_character.size_/2) * self.DRAWING_SCALE_,
                                          main_character.size_ * self.DRAWING_SCALE_,
                                          main_character.size_ * self.DRAWING_SCALE_)
        pygame.draw.rect(screen, self.main_character_color_, main_character_rect)

class RifleProjectile(GameObject): 

    def __init__(self, initial_position, target_position, universe):
        self.universe_ = universe 
        self.ID_ = self.create_ID()
        self.initial_position_ = initial_position
        self.position_ = self.initial_position_
        self.target_position_ = target_position
        self.speed_ = 15
        self.size_ = 5

    def update(self,events):
        y2 = self.target_position_[1]
        y1 = self.initial_position_[1]
        x2 = self.target_position_[0]
        x1 = self.initial_position_[0]

        tx = x2 - x1
        ty = y2 - y1
        dist = math.sqrt(tx*tx+ty*ty)
        rad = math.atan2(ty,tx)
        angle = rad/math.pi*180

        velx = (tx/dist)*self.speed_
        vely = (ty/dist)*self.speed_

        self.position_ = (self.position_[0] + velx, self.position_[1] - abs(vely))
        self.check_collisions()

    def check_collisions(self):
        collisions = self.universe_.get_collisions(self)
        for collision in collisions:
            collision.take_damage(1000)

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
        pass

	

class Rifle():

    def __init__(self, universe, DRAWING_SCALE):
        self.universe_ = universe
        self.DRAWING_SCALE_ = DRAWING_SCALE

        self.NAME_ = "Rifle"
        self.targeting_system = RifleTargetingSystem(universe, DRAWING_SCALE)

    def update(self, events):
        self.targeting_system.update(events)

    def draw(self, screen):
        self.targeting_system.draw(screen)
