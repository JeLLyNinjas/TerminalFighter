import cProfile
import sys
import time

import highscore_service
import pygame
from gamemaster import GameMaster
from score_counter import ScoreCounter
from spawn_controller import SpawnController
from universe import Universe

pygame.init()
pygame.font.init()
pygame.key.set_repeat(100, 25)

GAME_WIDTH = 1000
GAME_HEIGHT = 700
WHITE = 255, 255, 255
BLACK = 0, 0, 0
DARK_GREEN = 0, 100, 0


def terminalfighter(screen):
    pygame.mixer.music.load("TerminalFighterPrototypeTheme.ogg")
    pygame.mixer.music.play(loops=-1)
    pygame.mixer.music.set_volume(1.1)
    print("volume is " + str(pygame.mixer.music.get_volume()))
    universe = Universe(screen.get_size())
    score_counter = ScoreCounter()
    spawn_controller = SpawnController(universe, score_counter)
    gamemaster = GameMaster(universe, spawn_controller, score_counter, screen.get_size())
    # pygame ticks, one tick is 1/1000 second
    # 15 pygame ticks per update is ~60 updates per second
    FRAME_LENGTH_TICKS = 15

    background_surface = draw_background(screen.get_width(), screen.get_height())

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
        gamemaster.update(events)
        # print("update time : " + str(pygame.time.get_ticks() - update_start_time))

        draw_start_time = pygame.time.get_ticks()
        screen.blit(background_surface, (0, 0))
        gamemaster.draw(screen)
        # print("draw time : " + str(pygame.time.get_ticks() - draw_start_time))

        flip_start_time = pygame.time.get_ticks()
        pygame.display.flip()
        # print("flip time : " + str(pygame.time.get_ticks() - flip_start_time))
        if gamemaster.universe_.main_character().health_ <= 0:
            pygame.mixer.music.stop()

            gameover_font = pygame.font.SysFont("monospace", 120)
            gameover_label = gameover_font.render("GAME OVER", 1, WHITE)
            screen.blit(gameover_label,
                        (screen.get_width()/2 - gameover_label.get_width()/2,
                         screen.get_height()/2 - gameover_label.get_height()/2))

            highscore_font = pygame.font.SysFont("monospace", 30)
            highscore_text = "Highscore : "
            if not highscore_service.get_highscore() or \
                highscore_service.get_highscore() < gamemaster.score_counter_.score_:
                highscore_service.update_highscore(gamemaster.score_counter_.score_)
                highscore_text += str(highscore_service.get_highscore()) + " NEW HIGHSCORE"
            else:
                highscore_text += str(highscore_service.get_highscore())
            highscore_label = highscore_font.render(highscore_text, 1, WHITE)
            screen.blit(highscore_label,
                        (screen.get_width()/2 - highscore_label.get_width()/2,
                         screen.get_height()/2 + gameover_label.get_height()/2 + highscore_label.get_height()/2))

            press_any_key_font = pygame.font.SysFont("monospace", 30)
            press_any_key_label = press_any_key_font.render("Press any key...", 1, WHITE)
            screen.blit(press_any_key_label,
                        (screen.get_width()/2 - press_any_key_label.get_width()/2,
                         screen.get_height()/2 +
                         gameover_label.get_height()/2 +
                         highscore_label.get_height() +
                         press_any_key_label.get_height()/2))

            pygame.display.flip()
            pygame.time.delay(1000)
            pygame.event.clear()
            while 1:
                for event in pygame.event.get():
                    if event.type == pygame.QUIT:
                        sys.exit()
                    elif event.type == pygame.KEYDOWN:
                        return "MENU"

        frame_end_time = pygame.time.get_ticks()
        frame_time_elapsed = frame_end_time - frame_start_time
        if frame_time_elapsed < FRAME_LENGTH_TICKS:
            pygame.time.wait(FRAME_LENGTH_TICKS - frame_time_elapsed)
        else:
            print("WARNING: Cannot keep up with 30FPS update time!")

def draw_background(width, height):
    background_surface = pygame.Surface((width, height))
    background_surface.fill(BLACK)

    return background_surface


if __name__ == '__main__':
    screen = pygame.display.set_mode((int(GAME_WIDTH), int(GAME_HEIGHT)))
    terminalfighter(screen)
