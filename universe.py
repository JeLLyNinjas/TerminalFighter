import pygame

from basic_grunt import BasicGrunt
from maincharacter import MainCharacter


class Universe():

    def __init__(self, bounds):
        self.bounds_ = bounds
        self.height_ = bounds[1]
        self.width_ = bounds[0]

        self.collisions_ = dict()
        self.enemies_ = dict()
        self.gameobjects_ = dict()
        self.main_character_ = None
        self.projectiles_ = dict()

    """
    Access Functions
    """
    def get_collisions(self, gameobject):
        return self.collisions_[gameobject.ID_]

    def enemies(self):
        return self.enemies_.values()

    def gameobjects(self):
        return self.gameobjects_.values()

    def main_character(self):
        return self.main_character_

    def projectiles(self):
        return self.projectiles_.values()

    """
    Update Functions
    """
    def update_collisions(self):
        self.collisions_ = dict()
        for gameobject_id in self.gameobjects_:
            self.collisions_[gameobject_id] = []
        for gameobject_a_id in self.gameobjects_:
            for gameobject_b_id in self.gameobjects_:
                if gameobject_a_id == gameobject_b_id:
                    pass
                else:
                    gameobject_a_collision_box = self.gameobjects_[gameobject_a_id].collision_box() 
                    gameobject_b_collision_box = self.gameobjects_[gameobject_b_id].collision_box() 
                    if gameobject_a_collision_box.colliderect(gameobject_b_collision_box):
                        self.collisions_[gameobject_a_id].append(gameobject_b_id)

    def create_enemy(self, the_enemy):
        self.enemies_[the_enemy.ID_] = the_enemy
        self.gameobjects_[the_enemy.ID_] = the_enemy
    
    def create_main_character(self, the_main_character):
        self.main_character_ = the_main_character
        self.gameobjects_[the_main_character.ID_] = the_main_character

    def create_projectile(self, the_projectile):
        self.projectiles_[the_projectile.ID_] = the_projectile
        self.gameobjects_[the_projectile.ID_] = the_projectile

    def delete_out_of_bounds_gameobjects(self):
        out_of_bounds_IDs = []

        for entity_ID in self.gameobjects_:
            if not pygame.Rect((0, 0), self.bounds_).collidepoint(self.gameobjects_[entity_ID].position_):
                out_of_bounds_IDs.append(entity_ID)

        for entity_ID in out_of_bounds_IDs:
            self.gameobjects_.pop(entity_ID, None)
            self.enemies_.pop(entity_ID, None)
            self.projectiles_.pop(entity_ID, None)

    def update(self, events):
        self.update_collisions()
        print("Collisions : " + str(self.collisions_))
        # print(str(len(self.gameobjects_)) + "gameobjects, " +
              # str(len(self.enemies_)) + " enemies")
        self.delete_out_of_bounds_gameobjects()
        for entity in self.gameobjects():
            entity.update(events)

