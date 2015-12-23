HIGH_SCORE_FILE = "HighScore.txt"

def get_highscore():
    try:
        with open(HIGH_SCORE_FILE, 'r') as f:
            high_score = f.readline().rstrip('\n')
            if high_score:
                return int(high_score)

    except FileNotFoundError:
        return None

def overwrite_highscore(new_highscore):
    with open(HIGH_SCORE_FILE, "w") as f:
        f.write(str(new_highscore))

def update_highscore(new_highscore):
    if not get_highscore() or new_highscore > get_highscore():
        overwrite_highscore(new_highscore)


