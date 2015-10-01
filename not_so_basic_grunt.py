import pygame
import math

from gameobject import GameObject


class NotSoBasicGrunt(GameObject):
    

    def __init__(self, starting_position, universe):
        self.position_ = starting_position

        self.ID_ = self.create_ID()
        self.size_ = 15
        self.health_ = 30
        self.universe_ = universe

        self.x_velocity = 0
        self.y_velocity = 0.3 

        self.x_accel = 0
        self.y_accel = 0.01

        self.gravity_hole_1 = (500,350)
        #self.gravity_hole_1 = (300,175)
        #self.gravity_hole_2 = (800,200)
        #self.gravity_hole_3 = (500,350)
    

    """
    Update Functions
    """

    def update(self, events):
        force_1 = self.calculate_force_from_(self.gravity_hole_1)
        print("x_force = " + str(force_1[0]))
        print("y_force = " + str(force_1[1]))
        print("x_accel = " + str(self.x_accel))
        print("y_accel = " + str(self.y_accel))
        print("x_velocity = " + str(self.x_velocity))
        print("y_velocity = " + str(self.y_velocity))

        #force_1 = self.calculate_force_from_(self.gravity_hole_1)
        #force_2 = self.calculate_force_from_(self.gravity_hole_2)
        #force_3 = self.calculate_force_from_(self.gravity_hole_3)

        self.x_accel = force_1[0]# + force_2[0] + force_3[0]
        self.y_accel = force_1[1]# + force_2[1] + force_3[1]

        self.x_velocity += self.x_accel
        self.y_velocity += self.y_accel

        self.x_velocity += -self.x_velocity*0.00001
        self.y_velocity += -self.y_velocity*0.003

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
            self.health_ = 0
        else:
            self.health_ -= damage
    """"
    Private Functions
    """
    

    def calculate_force_from_(self, gravity_hole):
        x_distance = gravity_hole[0] - self.position_[0]
        y_distance = gravity_hole[1] - self.position_[1]
        print("x_distance = " + str(x_distance))
        print("y_distance = " + str(y_distance))

        if x_distance < 0:
            x_force = -0.18
        else:
            x_force = 0.18

        if y_distance < 0:
            y_force = -0.18
        else:
            y_force = 0.18


        return (x_force, y_force)

