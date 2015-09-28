import pygame

from basic_grunt import BasicGrunt
from maincharacter import MainCharacter


class Universe():

    def __init__(self, bounds):
        self.bounds_ = bounds
        self.height_ = bounds[1]
        self.width_ = bounds[0]

        self.created_enemies = list()
        self.created_friendly_projectiles = list() 
        self.created_enemy_projectiles = list()
        self.created_main_character = list()
        self.collisions_ = dict()
        self.enemies_ = dict()
        self.enemy_projectiles_ = dict()
        self.friendly_projectiles_ = dict()
        self.gameobjects_ = dict()
        self.main_character_ = None

    """
    Access Functions
    """

    def get_collisions(self, gameobject):
        return self.collisions_[gameobject.ID_]

    def enemies(self):
        return self.enemies_.values()

    def enemy_projectiles(self):
        return self.enemy_projectiles_.values()

    def friendly_projectiles(self):
        return self.friendly_projectiles_.values()

    def gameobjects(self):
        return self.gameobjects_.values()

    def main_character(self):
        return self.main_character_

    """
    Update Functions
    """

    def update(self, events):
        for the_projectile in self.created_friendly_projectiles:
            self.friendly_projectiles_[the_projectile.ID_] = the_projectile
            self.gameobjects_[the_projectile.ID_] = the_projectile
        
        for the_enemy in self.created_enemies:
            self.enemies_[the_enemy.ID_] = the_enemy
            self.gameobjects_[the_enemy.ID_] = the_enemy

        for the_projectile in self.created_enemy_projectiles: 
            self.enemy_projectiles_[the_projectile.ID_] = the_projectile
            self.gameobjects_[the_projectile.ID_] = the_projectile

        for the_main_character in self.created_main_character:
            self.main_character_ = the_main_character
            self.gameobjects_[the_main_character.ID_] = the_main_character

        self.created_friendly_projectiles.clear()
        self.created_enemies.clear()
        self.created_main_character.clear()
        self.created_enemy_projectiles.clear()

        self.update_collisions()
        self.delete_out_of_bounds_gameobjects()
        for gameobject in self.gameobjects():
            gameobject.update(events)

        #print("Collisions : " + str(self.collisions_))
        # print(str(len(self.gameobjects_)) + " gameobjects")
        # print(str(len(self.enemies_)) + " enemies")

    def create_enemy(self, the_enemy):
        self.created_enemies.append(the_enemy)
        
    def create_enemy_projectile(self, the_projectile):
        self.created_enemy_projectiles.append(the_projectilee)

    def create_friendly_projectile(self, the_projectile):
        self.created_friendly_projectiles.append(the_projectile)

    def create_main_character(self, the_main_character):
        self.created_main_character.append(the_main_character)

    def update_collisions(self):
        self.collisions_ = dict()
        self.update_main_character_collisions()
        self.update_enemies_collisions()
        self.update_friendly_projectiles_collisions()
        self.update_enemy_projectiles_collisions()

    def update_main_character_collisions(self):
        self.collisions_[self.main_character_.ID_] = []
        # main character doesn't care what it collides with

    def update_enemies_collisions(self):
        for enemy_id in self.enemies_:
        	self.collisions_[enemy_id] = []
        # enemies don't care what they collide with

    def update_friendly_projectiles_collisions(self):
        for friendly_projectile_id in self.friendly_projectiles_:
            self.collisions_[friendly_projectile_id] = []
            friendly_projectiles_collision_box = self.gameobjects_[
                friendly_projectile_id].collision_box()
            for enemy_id in self.enemies_:
                enemy_collision_box = self.gameobjects_[
                    enemy_id].collision_box()
                if enemy_collision_box.colliderect(friendly_projectiles_collision_box):
                    self.collisions_[friendly_projectile_id].append(enemy_id)

    def update_enemy_projectiles_collisions(self):
        for enemy_projectile_id in self.enemy_projectiles_:
            self.collisions_[enemy_projectile_id] = []
            enemy_projectile_collision_box = self.gameobjects_[
                enemy_projectile_id].collision_box()

            main_character_collision_box = self.gameobjects_[
                self.main_character_.ID_].collision_box()
            if main_character_collision_box.colliderect(enemy_projectile_collision_box):
                self.collisions_[enemy_projectile_id].append(main_character_)

    def delete_out_of_bounds_gameobjects(self):
        out_of_bounds_IDs = []

        for entity_ID in self.gameobjects_:
            if not pygame.Rect((0, 0), self.bounds_).collidepoint(self.gameobjects_[entity_ID].position_):
                out_of_bounds_IDs.append(entity_ID)

        for entity_ID in out_of_bounds_IDs:
            self.gameobjects_.pop(entity_ID, None)
            self.enemies_.pop(entity_ID, None)
            self.friendly_projectiles_.pop(entity_ID, None)
            self.enemy_projectiles_.pop(entity_ID, None)
