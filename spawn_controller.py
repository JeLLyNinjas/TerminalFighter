import random

from basic_grunt import BasicGrunt
from not_so_basic_grunt import NotSoBasicGrunt

class SpawnController():
    def __init__(self, universe, score_counter):
        self.universe_ = universe
        self.score_counter_ = score_counter
        self.basic_grunt_spawn_delay_ = 300
        self.basic_grunt_spawn_timer_ = self.basic_grunt_spawn_delay_
        self.enemy_x_spawn_locations = [x/100 for x in range(20, 80)] 

        self.spawn_difficulty_ = 0.9995
        self.minimum_spawn_delay_ = 40
        
    def update(self):
        # print('self.basic_grunt_spawn_delay_:' + str(self.basic_grunt_spawn_delay_))
        self.basic_grunt_spawn_timer_ += 1

        if self.basic_grunt_spawn_delay_ > self.minimum_spawn_delay_: 
            self.basic_grunt_spawn_delay_ *= self.spawn_difficulty_
        else:
            self.basic_grunt_spawn_delay_ = self.minimum_spawn_delay_
            # print("maximum difficulty reached")

        if self.basic_grunt_spawn_timer_ > self.basic_grunt_spawn_delay_:
            self.spawn_basic_grunt()
            self.spawn_not_so_basic_grunt()
            self.basic_grunt_spawn_timer_ = 0
    
    def spawn_basic_grunt(self):
        starting_position = [self.universe_.width_*random.choice(self.enemy_x_spawn_locations), 0]
        the_basic_grunt = BasicGrunt(starting_position, self.universe_)
        self.universe_.create_enemy(the_basic_grunt)
        the_basic_grunt.register(self.score_counter_)

    def spawn_not_so_basic_grunt(self):
        starting_position = [self.universe_.width_*random.choice(self.enemy_x_spawn_locations), 0]
        not_so_basic_grunt = NotSoBasicGrunt(starting_position, self.universe_)
        self.universe_.create_enemy(not_so_basic_grunt)
        not_so_basic_grunt.register(self.score_counter_)
