import pygame


pygame.font.init()

UI_FONT = pygame.font.SysFont("monospace", 20)
BLACK = 0, 0, 0
BLUE = 0, 0, 255
WHITE = 255, 255, 255
EVENT_KEY_a = 97
EVENT_KEY_z = 122
EVENT_KEY_ENTER = 13
EVENT_KEY_BACKSPACE = 8

class RifleTargetingSystem():
	def __init__(self):
		self.enemies_ = []
		self.target_tags_ = dict()
		self.current_text_ = ""

	def update(self, events, enemies):
		self.enemies_ = enemies

		for enemy in self.enemies_:
			if enemy.ID_ not in self.target_tags_:
				self.target_tags_[enemy.ID_] = self.new_word()

		for event in events:
			if event.type == pygame.KEYDOWN:
				if event.key == EVENT_KEY_ENTER:
					self.current_text_ = ""
				if event.key == EVENT_KEY_BACKSPACE:
					self.current_text_ = self.current_text_[:-1]
				elif event.key in range(EVENT_KEY_a, EVENT_KEY_z+1):
					self.current_text_ += event.unicode.lower()

	def draw_target_tags(self, screen):
		for enemy in self.enemies_:
			target_tag_word = self.target_tags_[enemy.ID_]
			target_tag_label = UI_FONT.render(target_tag_word, 1, enemy.colour_)
			# !!NEW!! Get target tag size and adjust coordinates of tag 	
			width = UI_FONT.size(target_tag_word)[0]
			screen.blit(target_tag_label, (enemy.position_[0] - (width/2),  
										  (enemy.position_[1] + enemy.size_/2)+10))
			
	def draw_terminal(self, screen):
		terminal_rect = pygame.Rect(20, screen.get_height()-75,
								  400, 50)
		pygame.draw.rect(screen, BLUE, terminal_rect)
		pygame.draw.rect(screen, BLACK, terminal_rect, 4)

		text_label = UI_FONT.render(self.current_text_, 1, WHITE)
		screen.blit(text_label, (30, screen.get_height()-60))

	def new_word(self):
		return "RifleTestTag"

class Rifle():
	def __init__(self):
		self.NAME_ = "Rifle"
		self.targeting_system = RifleTargetingSystem()

	def update(self, events, enemies):
		self.targeting_system.update(events, enemies)

	def draw(self, screen):
		self.targeting_system.draw_target_tags(screen)
		self.targeting_system.draw_terminal(screen)
