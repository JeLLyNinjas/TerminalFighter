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
        self.terminal_RectX_ = 10
        self.terminal_RectY_ = 40
        self.terminal_SizeHeight_ = 25
        self.terminal_SizeWidth_ = 400
        self.terminal_BorderRectWidth_ = 2

        # Terminal Text Input Constants
        self.fontSize_ = 15
        self.ui_font_ = pygame.font.SysFont("monospace", self.fontSize_*DRAWING_SCALE)
        self.textAlias_ = 1
        self.text_input_x_ = 15
        self.text_input_y_ = 35
        self.text_input_maxSize_ = self.terminal_SizeWidth_ - 20 



    """
    Update functions
    """

    def update(self, events):
        for event in events:
            if event.type == pygame.KEYDOWN:
                textWidth = self.ui_font_.size(self.current_text_)[0]
                if event.key == EVENT_KEY_ENTER:
                    self.current_text_ = ""
                if event.key == EVENT_KEY_BACKSPACE:
                    self.current_text_ = self.current_text_[:-1]
                elif event.key in range(EVENT_KEY_a, EVENT_KEY_z + 1) and \
                                textWidth < self.text_input_maxSize_*self.DRAWING_SCALE_:
                    self.current_text_ += chr(event.key)

    """
    Draw functions
    """

    def draw_terminal(self, screen):
        if not self.terminal_rect_:
            self.terminal_rect_ = pygame.Rect(self.terminal_RectX_*self.DRAWING_SCALE_, 
                                              screen.get_height()-self.terminal_RectY_*self.DRAWING_SCALE_,
                                              self.terminal_SizeWidth_*self.DRAWING_SCALE_, 
                                              self.terminal_SizeHeight_*self.DRAWING_SCALE_)

        pygame.draw.rect(screen, BLUE, self.terminal_rect_)
        pygame.draw.rect(screen, 
                         WHITE, 
                         self.terminal_rect_, 
                         self.terminal_BorderRectWidth_*self.DRAWING_SCALE_)

        text_label = self.ui_font_.render(self.current_text_, 
                                          self.textAlias_, 
                                          WHITE)
        screen.blit(text_label, 
                    (self.text_input_x_ * self.DRAWING_SCALE_,
                     screen.get_height()-(self.text_input_y_ * self.DRAWING_SCALE_)))
