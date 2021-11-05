import math
import random

class Tetrahedron:
    def __init__(self):
        self.a = 0
        self.materialDensity = 0

    def In(self, strArray):
        self.a = int(strArray[1])
        self.materialDensity = int(strArray[2])

    def InRnd(self):
        self.a = random.randint(1, 20)
        self.materialDensity = random.randint(1, 20)

    def Write(self, ostream):
        ostream.write("Tetrahedron: a = {}, materialDensity = {}, Square = {}".
                      format(self.a, self.materialDensity, self.Square()))
        pass

    def Square(self):
        return float(self.a * self.a * math.sqrt(3));
        pass
