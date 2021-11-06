from getShape import *

class Container:
    def __init__(self):
        self.store = []

    def BinarySearch(self, item, low, high):
        if high <= low:
            if item.Square() > self.store[low].Square():
                return low + 1
            else:
                return low
        mid = int((low + high) / 2)
        if item.Square() == self.store[mid].Square():
            return mid + 1
        if item.Square() > self.store[mid].Square():
            return self.BinarySearch(item, mid + 1, high)
        return self.BinarySearch(item, low, mid - 1)
    
    def BinaryInsertionSort(self):
        length = len(self.store)

        for i in range(1, length, 1):
            j = i - 1
            selected = self.store[i]
            loc = self.BinarySearch(selected, 0, j)
            while j >= loc:
                self.store[j + 1] = self.store[j]
                j -= 1
            self.store[j + 1] = selected

    def Write(self, ostream):
        ostream.write("Container contains {} elements:\n".format(len(self.store)))
        i = 1
        for shape in self.store:
            ostream.write("{}: ".format(i))
            shape.Write(ostream)
            ostream.write("\n")
            i += 1
        pass

    def Read(self, file):
        try:
            for line in file:
                if line != '':
                    shape = ReadFromFile(line)
                    self.store.append(shape)
        except:
            pass

    def FillRandom(self, length):
        for _ in range(length):
            shape = GetRandom()
            self.store.append(shape)
