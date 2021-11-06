import sys
import time
import string
from container import Container

def ErrorMessage():
    print("Incorrect command line!\n"
        "  Expected:\n"
        "     <main.py> -f <input file> <output file>\n"
        "  Or:\n"
        "     <main.py> -n <container size> <output file>\n"
    )

if __name__ == '__main__':
    #start_time = time.clock()
    if len(sys.argv) != 4:
        ErrorMessage()
        exit()

    print('==> Start')
    container = Container()

    print('Container collecting...')
    if sys.argv[1] == "-n":
        try:
            length = int(sys.argv[2])
            if length < 0 or length > 10000:
                raise RangeError("Incorrect container size")
        except:
            print("Container size must be in range [0,10000]!")
            exit()
        container.FillRandom(length)
    elif sys.argv[1] == "-f":
        try:
            with open(sys.argv[2], 'r') as file:
                container.Read(file)
        except FileNotFoundError:
            print("Input file does not exist!")
            exit()
    else:
        ErrorMessage()
        exit()

    print('Sorting...')
    container.BinaryInsertionSort()

    with open(sys.argv[3], 'w') as file:
        container.Write(file)

    print("==> End")
    #print("Time elapsed {} ms".format((time.clock() - start_time) * 1000))
