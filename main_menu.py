import sys

import pygame

from basic_grunt import BasicGrunt
from destroy_listener import DestroyListener 
from maincharacter import MainCharacter
from universe import Universe

pygame.init()

GAME_WIDTH = 1000
GAME_HEIGHT = 700

WHITE = 255, 255, 255
BLACK = 0, 0, 0

class SelectionListener(DestroyListener):

    def __init__(self):
        self.selections_ = dict()
        self.selected_ = None

    def register_selection(self, name, gameobject):
        self.selections_[gameobject.id_] = name
        gameobject.register(self)

    """
    Listeners
    """

    def reported_destroyed(self, type_gameobject):
        if not self.selected_:
            self.selected_ = self.selections_[type_gameobject.id_]

def spawn_main_character(universe, DRAWING_SCALE):
    the_main_character = MainCharacter([universe.width_/2, universe.height_*0.9], universe, DRAWING_SCALE)
    the_main_character.weapons_ = the_main_character.weapons_[:1]
    universe.create_main_character(the_main_character)

def spawn_selection(starting_pos, name, universe, selection_listener):
    the_selection = BasicGrunt(starting_pos, universe)
    the_selection.speed_ = 0
    the_selection.weapon_delay_ = 0
    universe.create_enemy(the_selection)
    selection_listener.register_selection(name, the_selection)

def main_menu(screen, DRAWING_SCALE):
    universe = Universe((GAME_WIDTH, GAME_HEIGHT))
    selection_listener = SelectionListener()
    ui_font_ = pygame.font.SysFont("monospace", 30*DRAWING_SCALE)
    LABEL_SPACING = 50
    play_position = [GAME_WIDTH*(1/3), GAME_HEIGHT*(1/4)]
    quit_position = [GAME_WIDTH*(2/3), GAME_HEIGHT*(1/4)]

    spawn_main_character(universe, DRAWING_SCALE)   
    spawn_selection(play_position, "PLAY",  universe,  selection_listener)
    spawn_selection(quit_position, "QUIT",  universe,  selection_listener)


    # pygame ticks, one tick is 1/1000 second
    # 15 pygame ticks per update is approximately 30 updates per second
    FRAME_LENGTH_TICKS = 33
    
    prev_frame_start_time = 0
    
    while 1:
        frame_start_time = pygame.time.get_ticks()
        # print("Elapsed time since last update : " + str(frame_start_time - prev_frame_start_time))
        prev_frame_start_time = frame_start_time
    
        update_start_time = pygame.time.get_ticks()
        events = pygame.event.get()
        for event in events:
            if event.type == pygame.QUIT:
                sys.exit()
        if selection_listener.selected_:
            return selection_listener.selected_

        universe.update(events)
        # print("update time : " + str(pygame.time.get_ticks() - update_start_time))
    
        draw_start_time = pygame.time.get_ticks()
        universe.main_character_.current_weapon_.draw(screen)

        play_label = ui_font_.render("PLAY", 1, WHITE)
        screen.blit(play_label, 
                    (play_position[0] * DRAWING_SCALE - (play_label.get_width()/2), 
                     play_position[1] * DRAWING_SCALE - LABEL_SPACING*DRAWING_SCALE))

        quit_label = ui_font_.render("QUIT", 1, WHITE)
        screen.blit(quit_label, 
                    (quit_position[0] * DRAWING_SCALE - (quit_label.get_width()/2), 
                     quit_position[1] * DRAWING_SCALE - LABEL_SPACING*DRAWING_SCALE))
    
        instruction_label = ui_font_.render("TYPE TO SHOOT!", 1, WHITE)
        screen.blit(instruction_label, 
                    (screen.get_width()/2 - (instruction_label.get_width()/2), 
                     screen.get_height()/2))
        # print("draw time : " + str(pygame.time.get_ticks() - draw_start_time))
    
        flip_start_time = pygame.time.get_ticks()
        pygame.display.flip()
        # print("flip time : " + str(pygame.time.get_ticks() - flip_start_time))
    
        frame_end_time = pygame.time.get_ticks()
        frame_time_elapsed = frame_end_time - frame_start_time
        if frame_time_elapsed < FRAME_LENGTH_TICKS:
            pygame.time.wait(FRAME_LENGTH_TICKS - frame_time_elapsed)
        else:
            print("WARNING: Cannot keep up with 30FPS update time!")
