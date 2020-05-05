from destroy_listener import DestroyListener
import pygame

WHITE = (255, 255, 255)

class ScoreCounter(DestroyListener):

    def __init__(self):
        self.score_ = 0

        self.font_size_ = 20
        self.text_antialias_ = 1
        self.ui_font_ = pygame.font.SysFont("monospace", self.font_size_)

    def reported_destroyed(self, destroyed_enemy):
        self.score_ += 400

    def update(self):
        self.score_ += 1


    def draw(self, screen):
        score_text_color = WHITE
        score_label = self.ui_font_.render("SCORE: " + str(self.score_),
                                          self.text_antialias_,
                                          score_text_color)

        screen.blit(score_label, ((screen.get_width()-score_label.get_width())/2, 0));