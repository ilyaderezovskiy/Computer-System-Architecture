import random
from ball import Ball
from parallelepiped import Parallelepiped
from tetrahedron import Tetrahedron

def GetRandom():
    key = random.randint(1, 3)
    if key == 1:
        shape = Ball()
        shape.InRnd()
    elif key == 2:
        shape = Parallelepiped()
        shape.InRnd()
    elif key == 3:
        shape = Tetrahedron()
        shape.InRnd()
    return shape

def ReadFromFile(str):
    key = int(str[0])
    strArray = str.split()
    if key == 1:
        shape = Ball()
        shape.In(strArray)
    elif key == 2:
        shape = Parallelepiped()
        shape.In(strArray)
    elif key == 3:
        shape = Tetrahedron()
        shape.In(strArray)
    return shape

