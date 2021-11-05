import random

class Parallelepiped:
    def __init__(self):
        self.x = 0
        self.y = 0
        self.z = 0
        self.materialDensity = 0

    def In(self, strArray):
        self.x = int(strArray[1])
        self.y = int(strArray[2])
        self.z = int(strArray[3])
        self.materialDensity = int(strArray[4])

    def InRnd(self):
        self.x = random.randint(1, 20)
        self.y = random.randint(1, 20)
        self.z = random.randint(1, 20)
        self.materialDensity = random.randint(1, 20)

    def Write(self, ostream):
        ostream.write("Parallelepiped: x = {}, y = {}, z = {}, materialDensity = {}, Square = {}".
                      format(self.x, self.y, self.z, self.materialDensity, self.Square()))
        pass

    def Square(self):
        return 2.0 * (self.x * self.y + self.y * self.z + self.x * self.z);
        pass
