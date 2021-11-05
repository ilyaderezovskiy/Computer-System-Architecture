import random
import math

class Ball:
    def __init__(self):
        self.r = 0
        self.materialDensity = 0

    def In(self, strArray):
        self.r = int(strArray[1])
        self.materialDensity = int(strArray[2])

    def InRnd(self):
        self.r = random.randint(1, 20)
        self.materialDensity = random.randint(1, 20)

    def Write(self, ostream):
        ostream.write("Ball: r = {}, materialDensity = {}, Square = {}".
                      format(self.r, self.materialDensity, self.Square()))
        pass

    def Square(self):
        return 4.0 * math.pi * (self.r * self.r);
        pass
