#ifndef __parallelepiped__
#define __parallelepiped__

//------------------------------------------------------------------------------
// parallelepiped.h - содержит описание параллелепипеда и его интерфейса
//------------------------------------------------------------------------------

#include <fstream>
using namespace std;

#include "rnd.h"

// параллелепипед
struct parallelepiped {
    int x, y, z; // рёбра
    double materialDensity; // плотность материала фигуры
};

// Ввод параметров параллелепипеда из файла
void In(parallelepiped &p, ifstream &ifst);

// Случайный ввод параметров параллелепипеда
void InRnd(parallelepiped &p);

// Вывод параметров параллелепипеда в форматируемый поток
void Out(parallelepiped &p, ofstream &ofst);

// Вычисление площади поверхности параллелепипеда
double Square(parallelepiped &p);

#endif //__parallelepiped__
