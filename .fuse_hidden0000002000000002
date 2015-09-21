import pygame

from maincharacter import MainCharacter
from basic_grunt import BasicGrunt


class Universe():

    def __init__(self, bounds):
        self.bounds_ = bounds
        self.width_ = bounds[0]
        self.height_ = bounds[1]
        self.entities_ = dict()
        self.main_character_ = None
        self.enemies_ = dict()
        self.projectiles_ = dict()

    def create_main_character(self, the_main_character):
        self.main_character_ = the_main_character
        self.entities_[the_main_character.ID_] = the_main_character

    def create_enemy(self, the_enemy):
        self.enemies_[the_enemy.ID_] = the_enemy
        self.entities_[the_enemy.ID_] = the_enemy

    def create_projectile(self, the_projectile):
        self.projectiles_[the_projectile.ID_] = the_projectile
        self.entities_[the_projectile.ID_] = the_projectile

    def update(self, events):
        # print(str(len(self.entities_)) + "entities, " +
              # str(len(self.enemies_)) + " enemies")
        self.delete_out_of_bounds_entities()
        for entity in self.entities():
            entity.update(events)

    def delete_out_of_bounds_entities(self):
        out_of_bounds_IDs = []

        for entity_ID in self.entities_:
            if not pygame.Rect((0, 0), self.bounds_).collidepoint(self.entities_[entity_ID].position_):
                out_of_bounds_IDs.append(entity_ID)

        for entity_ID in out_of_bounds_IDs:
            self.entities_.pop(entity_ID, None)
            self.enemies_.pop(entity_ID, None)
            self.projectiles_.pop(entity_ID, None)

    def entities(self):
        return self.entities_.values()

    def main_character(self):
        return self.main_character_

    def enemies(self):
        return self.enemies_.values()

    def projectiles(self):
        return self.projectiles_.values()
