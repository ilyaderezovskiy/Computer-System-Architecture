//
// main.cpp- содержит главную функцию,
// обеспечивающую простое тестирование
//
//  Homework1_Derezovskiy
//
//  Программа, создающая три типа объектов (объемных геометрических фигур) с
//  одним общим признаком - плотность материала фигуры и
//  со своими уникальными параметрами, задающими отличительные признаки объекта,
//  Шар (целочисленный радиус), Параллелепипед (три целочисленных ребра),
//  Правильный тетраэдр (длина ребра – целое число)
//
//  Программа упорядочивает элементы контейнера по возрастанию используя
//  сортировку методом деления пополам (Binary Insertion).
//  В качестве ключей для сортировки и других действий используются
//  результаты функции, общей для всех альтернатив - Вычисление площади поверхности фигуры.
//
//  Created by Ilya Derezovskiy BPI203 on 25.09.2021.
//

#include <iostream>
#include <fstream>
#include "stdlib.h" // для функций rand() и srand()
#include "time.h"   // для функции time()
#include "string.h"

#include "container.h"

void errMessage1() {
    std::cout << "incorrect command line!\n"
            "  Waited:\n"
            "     command -f infile outfile01 outfile02\n"
            "  Or:\n"
            "     command -n number outfile01 outfile02\n";
}

void errMessage2() {
    std::cout << "incorrect qualifier value!\n"
            "  Waited:\n"
            "     command -f infile outfile01 outfile02\n"
            "  Or:\n"
            "     command -n number outfile01 outfile02\n";
}

int binarySearch(shape arr[], shape item, int low, int high) {
    if (high <= low)
      return (Square(item) > Square(arr[low]))? (low + 1): low;
      int mid = (low + high) / 2;
   if (Square(item) == Square(arr[mid]))
      return mid + 1;
   if (Square(item) > Square(arr[mid]))
      return binarySearch(arr, item, mid + 1, high);
      return binarySearch(arr, item, low, mid - 1);
}

void binaryInsertionSort(shape arr[], int n) {
    int i, loc, j;
    shape selected;
    for (i = 1; i < n; ++i) {
       j = i - 1;
       selected = arr[i];
       loc = binarySearch(arr, selected, 0, j);
       while (j >= loc) {
          arr[j + 1] = arr[j];
          j--;
       }
       arr[j + 1] = selected;
    }
}

//------------------------------------------------------------------------------
int main(int argc, char* argv[]) {
    if(argc != 5) {
        errMessage1();
        return 1;
    }

    std::cout << "Start"<< std::endl;
    container c;
    Init(c);

    ////cout << "argv[1] = " << argv[1] << "\n";
    if(!strcmp(argv[1], "-f")) {
        ifstream ifst(argv[2]);
        In(c, ifst);
    }
    else if(!strcmp(argv[1], "-n")) {
        auto size = atoi(argv[2]);
        if((size < 1) || (size > 10000)) {
            std::cout << "incorrect numer of figures = "
                 << size
                 << ". Set 0 < number <= 10000\n";
            return 3;
        }
        // системные часы в качестве инициализатора
        srand(static_cast<unsigned int>(time(0)));
        // Заполнение контейнера генератором случайных чисел
        InRnd(c, size);
    }
    else {
        errMessage2();
        return 2;
    }
    
    // Сортировка контейнера методом деления пополам (Binary Insertion)
    binaryInsertionSort(*c.cont, c.len);
    
    // Вывод содержимого контейнера в файл
    ofstream ofst1(argv[3]);
    ofst1 << "Filled container:\n";
    Out(c, ofst1);

    // The 2nd part of task
    ofstream ofst2(argv[4]);
    ofst2 << "Square sum = " << SquareSum(c) << "\n";

    Clear(c);
    std::cout << "Stop"<< std::endl;
    return 0;
}
