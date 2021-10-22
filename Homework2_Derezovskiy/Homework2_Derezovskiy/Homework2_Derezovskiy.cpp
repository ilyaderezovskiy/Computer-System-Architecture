//
// main.cpp- содержит главную функцию,
// обеспечивающую простое тестирование
//
//  Homework2_Derezovskiy
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
//  Created by Ilya Derezovskiy BPI203 on 20.10.2021.
//

// example usage
// command -f <input file> <output file 1> <output file 2>
// command -n <container size> <output file 1> <output file 2>

// command -f ..\tests\1.txt ..\out\1.txt ..\out\1sorted.txt
// command -n 224 out1.txt out2.txt


#include <fstream>
#include "stdlib.h" // для функций rand() и srand()
#include "time.h"   // для функции time()

#include "container.h"

void errMessage1() {
    printf("Incorrect command line!\n"
        "  Expected:\n"
        "     command -f <input file> <output file 1> <output file 2>\n"
        "  Or:\n"
        "     command -n <container size> <output file 1> <output file 2>\n"
    );
}

void errMessage2() {
    printf("Incorrect qualifier value!\n"
        "  Expected:\n"
        "     command -f <input file> <output file 1> <output file 2>\n"
        "  Or:\n"
        "     command -n <container size> <output file 1> <output file 2>\n"
    );
}

int binarySearch(Shape* arr[], Shape* item, int low, int high) {
    if (high <= low)
        return (item->Square() > arr[low]->Square()) ? (low + 1) : low;
    int mid = (low + high) / 2;
    if (item->Square() == arr[mid]->Square())
        return mid + 1;
    if (item->Square() > arr[mid]->Square())
        return binarySearch(arr, item, mid + 1, high);
    return binarySearch(arr, item, low, mid - 1);
}

void binaryInsertionSort(Shape* arr[], int n) {
    int i, loc, j;
    Shape* selected;
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
    unsigned int start_time = clock();
    if (argc != 5) {
        errMessage1();
        return 1;
    }

    printf("Start\n");
    Container container;

    if (strcmp(argv[1], "-n") == 0) {
        int size = atoi(argv[2]);

        if (size < 0 || size > 10000) {
            printf("<container size> must be in range [0, 10000]\n");
            return 0;
        }

        srand(static_cast<unsigned int>(time(nullptr)));
        container.InRnd(size);
    } else if (strcmp(argv[1], "-f") == 0) {
        std::ifstream ifst(argv[2]);

        if (!ifst.is_open()) {
            printf("Input file does not exist.");
            return 0;
        }
        container.In(ifst);
        ifst.close();
    } else {
        errMessage2();
        return 0;
    }

    // Вывод содержимого контейнера в файл
    std::ofstream ofst1(argv[3]);
    ofst1 << "Filled container:\n";
    container.Out(ofst1);

    // The 2nd part of task
    // Сортировка контейнера методом деления пополам (Binary Insertion)
    binaryInsertionSort(container.cont, container.len);

    std::ofstream ofst2(argv[4]);
    ofst2 << "Sorted container:\n";
    container.Out(ofst2);
    ofst2 << "Square sum = " << container.SquareSum() << "\n";

    container.Clear();
    printf("Stop\n Time elapsed : ");
    printf("%d", clock() - start_time);
    printf(" ms");
    return 0;
}
