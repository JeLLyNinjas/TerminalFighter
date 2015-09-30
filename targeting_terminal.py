import pygame

pygame.font.init()

# CONSTANTS
BLACK = 0, 0, 0
BLUE = 0, 0, 255
WHITE = 255, 255, 255

EVENT_KEY_a = 97
EVENT_KEY_BACKSPACE = 8
EVENT_KEY_ENTER = 13
EVENT_KEY_z = 122


class TargetingTerminal():

    def __init__(self, DRAWING_SCALE):
        self.DRAWING_SCALE_ = DRAWING_SCALE

        self.borderRectWidth_ = 2
        self.current_text_ = ""
        self.fontSize_ = 15
        self.maxTextWidth_ = 380
        self.terminal_rect_ = None
        self.terminalHeight_ = 25
        self.terminalRectX_ = 10
        self.terminalRectY_ = 40
        self.terminalWidth_ = 400
        self.textAlias_ = 1
        self.x_input_text_ = 15
        self.y_input_text_ = 35
        self.ui_font_ = pygame.font.SysFont("monospace", 
                                            self.fontSize_*DRAWING_SCALE)

        self.max_word_size_ = self.maxTextWidth_ / self.ui_font_.size("W")[0]
       
    """
    Update functions
    """

    def update(self, current_text):
        self.current_text_ = current_text      

    """
    Draw functions
    """

    def draw_terminal(self, screen):
        if not self.terminal_rect_:
            self.terminal_rect_ = pygame.Rect(self.terminalRectX_*self.DRAWING_SCALE_, 
                                              screen.get_height()-self.terminalRectY_*self.DRAWING_SCALE_,
                                              self.terminalWidth_*self.DRAWING_SCALE_, 
                                              self.terminalHeight_*self.DRAWING_SCALE_)

        pygame.draw.rect(screen, BLUE, self.terminal_rect_)
        pygame.draw.rect(screen, 
                         WHITE, 
                         self.terminal_rect_, 
                         self.borderRectWidth_*self.DRAWING_SCALE_)

        text_label = self.ui_font_.render(self.current_text_, 
                                          self.textAlias_, 
                                          WHITE)
        screen.blit(text_label, 
                    (self.x_input_text_ * self.DRAWING_SCALE_,
                     screen.get_height()-(self.y_input_text_ * self.DRAWING_SCALE_)))
