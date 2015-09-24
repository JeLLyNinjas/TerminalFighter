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
        self.friendly_projectiles_ = dict()
        self.enemy_projectiles_ = dict()
        self.collisions_ = dict()

    def create_main_character(self, the_main_character):
        self.main_character_ = the_main_character
        self.gameobjects_[the_main_character.ID_] = the_main_character

    def create_enemy(self, the_enemy):
        self.enemies_[the_enemy.ID_] = the_enemy
        self.gameobjects_[the_enemy.ID_] = the_enemy

    def create_friendly_projectile(self, the_projectile):
        self.friendly_projectiles_[the_projectile.ID_] = the_projectile
        self.gameobjects_[the_projectile.ID_] = the_projectile

    def create_enemy_projectile(self, the_projectile):
        self.enemy_projectiles_[the_projectile.ID_] = the_projectile
        self.gameobjects_[the_projectile.ID_] = the_projectile

    def update(self, events):
        self.update_collisions()
        print("Collisions : " + str(self.collisions_))
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
        return self.friendly_projectiles_.values()

    def enemy_projectiles(self):
        return self.enemy_projectiles_.values()

    def update_collisions(self):
        self.collisions_ = dict()
        self.update_main_character_collisions()
        self.update_enemies_collisions()
        self.update_friendly_projectiles_collisions()
        self.update_enemy_projectiles_collisions()

    def update_main_character_collisions(self):
        pass # main character doesn't care what it collides with

    def update_enemies_collisions(self):
        pass # enemies don't care what they collide with

    def update_friendly_projectiles_collisions(self):
        for friendly_projectile_id in self.friendly_projectiles_:
            self.collisions_[friendly_projectile_id] = [] 
            friendly_projectiles_collision_box = self.gameobjects_[friendly_projectile_id].collision_box()
            for enemy_id in self.enemies_:
                enemy_collision_box = self.gameobjects_[enemy_id].collision_box()
                if enemy_collision_box.colliderect(friendly_projectiles_collision_box):
                    self.collisions_[friendly_projectile_id].append(enemy_id)

    def update_enemy_projectiles_collisions(self):
        for enemy_projectile_id in self.enemy_projectiles_:
            self.collisions_[enemy_projectile_id] = [] 
            enemy_projectile_collision_box = self.gameobjects_[enemy_projectile_id].collision_box()

            main_character_collision_box = self.gameobjects_[self.main_character_.ID_].collision_box()
            if main_character_collision_box.colliderect(enemy_projectile_collision_box):
                self.collisions_[enemy_projectile_id].append(main_character_)

    def get_collisions(self, gameobject_ID):
        return self.collisions_[gameobject_ID]