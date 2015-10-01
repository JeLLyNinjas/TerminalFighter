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
        # Initalization Constants
        self.DRAWING_SCALE_ = DRAWING_SCALE
        self.current_text_ = ""
        self.terminal_rect_ = None
        
        # Terminal Visual Constants
        self.terminal_rect_x_ = 10
        self.terminal_rect_y_ = 40
        self.terminal_size_height_ = 25
        self.terminal_size_width_ = 400
        self.terminal_border_width_ = 2

        # Terminal Text Input Constants
        self.font_size_ = 15
        self.ui_font_ = pygame.font.SysFont("monospace", self.font_size_*DRAWING_SCALE)
        self.text_alias_ = 1
        self.text_input_x_ = 15
        self.text_input_y_ = 35
        self.text_input_max_size_ = self.terminal_size_width_ - 20 

        self.max_word_size_ = self.text_input_max_size_ / self.ui_font_.size("W")[0]
       
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
            self.terminal_rect_ = pygame.Rect(self.terminal_rect_x_*self.DRAWING_SCALE_, 
                                              screen.get_height()-self.terminal_rect_y_*self.DRAWING_SCALE_,
                                              self.terminal_size_width_*self.DRAWING_SCALE_, 
                                              self.terminal_size_height_*self.DRAWING_SCALE_)

        pygame.draw.rect(screen, BLUE, self.terminal_rect_)
        pygame.draw.rect(screen, 
                         WHITE, 
                         self.terminal_rect_, 
                         self.terminal_border_width_*self.DRAWING_SCALE_)

        text_label = self.ui_font_.render(self.current_text_, 
                                          self.text_alias_, 
                                          WHITE)
        screen.blit(text_label, 
                    (self.text_input_x_ * self.DRAWING_SCALE_,
                     screen.get_height()-(self.text_input_y_ * self.DRAWING_SCALE_)))
