import pygame

pygame.font.init()

# CONSTANTS
BLACK = 0, 0, 0
BLUE = 0, 0, 255
WHITE = 255, 255, 255
EVENT_KEY_a = 97
EVENT_KEY_z = 122
EVENT_KEY_ENTER = 13
EVENT_KEY_BACKSPACE = 8
fontSize = 15
rectX = 10
rectY = 40
rectWidth = 400
rectHeight = 25
maxTextWidth = 380
borderRectWidth = 2
textAntialias = 1
textX = 15
textY = 35 

class TargetingTerminal():
    
    def __init__(self, DRAWING_SCALE):
        self.current_text_ = ""
        self.ui_font_ = pygame.font.SysFont("monospace", fontSize*DRAWING_SCALE)
        self.DRAWING_SCALE_ = DRAWING_SCALE
        self.terminal_rect_ = None

    def update(self , events):
        for event in events:
            if event.type == pygame.KEYDOWN:
                textWidth = self.ui_font_.size(self.current_text_)[0]
                if event.key == EVENT_KEY_ENTER:
                    self.current_text_ = ""
                if event.key == EVENT_KEY_BACKSPACE:
                    self.current_text_ = self.current_text_[:-1]
                elif event.key in range(EVENT_KEY_a, EVENT_KEY_z) and textWidth < maxTextWidth:
                    self.current_text_ += chr(event.key)

    def draw_terminal(self, screen):
        if not self.terminal_rect_:
            self.terminal_rect_ = pygame.Rect(rectX*self.DRAWING_SCALE_, screen.get_height()-rectY*self.DRAWING_SCALE_, 
                                              rectWidth*self.DRAWING_SCALE_, rectHeight*self.DRAWING_SCALE_)
        
        pygame.draw.rect(screen, BLUE,self.terminal_rect_)
        pygame.draw.rect(screen, WHITE, self.terminal_rect_, borderRectWidth*self.DRAWING_SCALE_)
    
        text_label = self.ui_font_.render(self.current_text_, textAntialias, WHITE)
        screen.blit(text_label, (textX * self.DRAWING_SCALE_, screen.get_height()-(textY * self.DRAWING_SCALE_)))
