import pygame

from maincharacter import MainCharacter
from basic_grunt import BasicGrunt


class Universe():

    def __init__(self, bounds):
        self.bounds_ = bounds
        self.width_ = bounds[0]
        self.height_ = bounds[1]
        self.gameobjects_ = dict()
        self.main_character_ = None
        self.enemies_ = dict()
        self.projectiles_ = dict()

    def create_main_character(self, the_main_character):
        self.main_character_ = the_main_character
        self.gameobjects_[the_main_character.ID_] = the_main_character

    def create_enemy(self, the_enemy):
        self.enemies_[the_enemy.ID_] = the_enemy
        self.gameobjects_[the_enemy.ID_] = the_enemy

    def create_projectile(self, the_projectile):
        self.projectiles_[the_projectile.ID_] = the_projectile
        self.gameobjects_[the_projectile.ID_] = the_projectile

    def update(self, events):
        # print(str(len(self.gameobjects_)) + "gameobjects, " +
              # str(len(self.enemies_)) + " enemies")
        self.delete_out_of_bounds_gameobjects()
        for entity in self.gameobjects():
            entity.update(events)

    def delete_out_of_bounds_gameobjects(self):
        out_of_bounds_IDs = []

        for entity_ID in self.gameobjects_:
            if not pygame.Rect((0, 0), self.bounds_).collidepoint(self.gameobjects_[entity_ID].position_):
                out_of_bounds_IDs.append(entity_ID)

        for entity_ID in out_of_bounds_IDs:
            self.gameobjects_.pop(entity_ID, None)
            self.enemies_.pop(entity_ID, None)
            self.projectiles_.pop(entity_ID, None)

    def gameobjects(self):
        return self.gameobjects_.values()

    def main_character(self):
        return self.main_character_

    def enemies(self):
        return self.enemies_.values()

    def projectiles(self):
        return self.projectiles_.values()

