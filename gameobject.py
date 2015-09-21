import pygame


class GameObject():
    counter_ = 0

    def create_ID(self):
        GameObject.counter_ += 1
        return GameObject.counter_
