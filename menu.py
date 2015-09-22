import pygame 

import sys

from gamemaster import GameMaster

pygame.init()

WHITE = 0, 0, 0


screen = pygame.display.set_mode((1000, 700)) # screen will be passed in 

intro = True
while intro: 
	background = pygame.Surface(screen.get_size())
	
	background.fill((WHITE))
	screen.blit(background, (0, 0))
	
	for event in pygame.event.get():
		if event.type == pygame.QUIT:
			pygame.quit()
			quit()
		if event.type == pygame.KEYDOWN:
			if event.key == pygame.K_ESCAPE:
				print("TEST")
			
	
	
	