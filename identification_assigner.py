class IdentificationAssigner():

    def __init__(self):
        self.id_meter_ = 0

    def get_id(self):
        self.id_meter_ += 1
        return self.id_meter_
