import pygame

pygame.font.init()

BLACK = 0, 0, 0
BLUE = 0, 0, 255
WHITE = 255, 255, 255
EVENT_KEY_a = 97
EVENT_KEY_z = 122
EVENT_KEY_ENTER = 13
EVENT_KEY_BACKSPACE = 8

class TargetingTerminal():
      
    def __init__(self, DRAWING_SCALE):
        self.current_text_ = ""
        self.ui_font_ = pygame.font.SysFont("monospace", 10*DRAWING_SCALE)
        self.DRAWING_SCALE_ = DRAWING_SCALE

    def update(self , events):
        for event in events:
            textWidth = self.ui_font_.size(self.current_text_)[0]
            if event.type == pygame.KEYDOWN:
                if event.key == EVENT_KEY_ENTER:
                    self.current_text_ = ""
                if event.key == EVENT_KEY_BACKSPACE:
                    self.current_text_ = self.current_text_[:-1]
                elif event.key in range(EVENT_KEY_a, EVENT_KEY_z) and textWidth < 380:
                    self.current_text_ += event.unicode.lower()

    def draw_terminal(self, screen):
        terminal_rect = pygame.Rect(10*self.DRAWING_SCALE_, screen.get_height()-(40*self.DRAWING_SCALE_), 400* self.DRAWING_SCALE_, 25*self.DRAWING_SCALE_)

        pygame.draw.rect(screen, BLUE, terminal_rect)
        pygame.draw.rect(screen, WHITE, terminal_rect, 2*self.DRAWING_SCALE_)
    
        text_label = self.ui_font_.render(self.current_text_, 1, WHITE)
        screen.blit(text_label, (15 * self.DRAWING_SCALE_, screen.get_height()-(30 * self.DRAWING_SCALE_)))
