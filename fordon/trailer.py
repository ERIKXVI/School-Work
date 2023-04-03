import fordon

class trailer:

    def __init__(self, model, color, trailer_volume):
        self.model = model
        self.color = color
        self.trailer_volume = trailer_volume

        def set_trailer_volume(self, trailer_volume):
            self.trailer_volume = trailer_volume

        def get_trailer_volume(self):
            return self.trailer_volume

    def print_fordon(self):
        print(self.model + " color: " + self.color + ", trailer_volume: "+ str(self.trailer_volume) + " L")
        