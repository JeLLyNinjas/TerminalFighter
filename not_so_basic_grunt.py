import pygame
import math

from gameobject import GameObject


class NotSoBasicGrunt(GameObject):
    

    def __init__(self, starting_position, universe):
        self.position_ = starting_position

        self.enemy_type_ = "NotSoBasicGrunt"
        self.health_ = 30
        self.ID_ = self.create_ID()
        self.listeners_ = []
        self.size_ = 15
        self.universe_ = universe

        self.x_velocity = 0
        self.y_velocity = 0.3 
        self.x_accel = 0
        self.y_accel = 0

        self.gravity_holes_ = [(500,300)]
        self.gravity_hole_force_ = 0.18

    """
    Update Functions
    """

    def update(self, events):
        forces = [self.calculate_force_from(gravity_hole) 
                  for gravity_hole in self.gravity_holes_]

        self.x_accel = sum([force[0] for force in forces])
        self.y_accel = sum([force[1] for force in forces])

        self.x_velocity += self.x_accel
        self.y_velocity += self.y_accel

        #Space friction, the not_so_basic_grunt will eventuall be at a stanstill
        self.x_velocity *= 0.999999
        self.y_velocity *= 0.997

        self.position_ = (self.position_[0] + self.x_velocity, self.position_[1] + self.y_velocity)


    """
    Access Functions
    """

    def collision_box(self):
        return pygame.Rect(self.position_[0]-self.size_/2,
                           self.position_[1]-self.size_/2,
                           self.size_,
                           self.size_)

    def take_damage(self, damage):
        if damage <= 0:
            print("WARNING BasicGrunt " + str(self.ID_) + " taking " + str(damage) + " damage")
            print("Disregarding non positive damage")
        elif damage >= self.health_:
            self.report_destroyed()
        else:
            self.health_ -= damage

    def get_type(self):
        return self.enemy_type_
    """"
    Private Functions
    """
    

    def calculate_force_from(self, gravity_hole):
        x_distance = gravity_hole[0] - self.position_[0]
        y_distance = gravity_hole[1] - self.position_[1]

        x_force = self.gravity_hole_force_
        if x_distance < 0:
            x_force *= -1.0

        y_force = self.gravity_hole_force_
        if y_distance < 0:
            y_force *= -1.0

        return x_force, y_force

    """
    Listener Functions
    """

    def report_destroyed(self):
        for listener in self.listeners_:
            listener.reported_destroyed(self)
    
    def register(self, listeners):
        self.listeners_.append(listeners)

