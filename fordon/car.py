import fordon

class bil:

    def __init__(self, model, color, trunk_volume):
        self.model = model
        self.color = color
        self.trunk_volume = trunk_volume

        def set_trunk_volume(self, trunk_volume):
            self.trunk_volume = trunk_volume

        def get_trunk_volume(self):
            return self.trunk_volume
        
    def print_fordon(self):
        print(self.model + " color: " + self.color + ", trunk_volume: " + str(self.trunk_volume) + " L")