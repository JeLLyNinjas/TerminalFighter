from destroy_listener import DestroyListener

class ScoreCounter(DestroyListener):

    def __init__(self):
        self.score_ = 0

    def reported_destroyed(self, destroyed_enemy):
        self.score_ += 200

    def update(self):
        self.score_ += 1
        print('score is ' + str(int(self.score_)))
