#ifndef __tetrahedron__
#define __tetrahedron__

//------------------------------------------------------------------------------
// tetrahedron.h - содержит описание тетраэдра
//------------------------------------------------------------------------------

#include <fstream>
using namespace std;

#include "rnd.h"

//------------------------------------------------------------------------------
// тетраэдр
struct tetrahedron {
    int a; // ребро
    double materialDensity; // плотность материала фигуры
};

// Ввод параметров тетраэдра из файла
void In(tetrahedron &t, ifstream &ifst);

// Случайный ввод параметров тетраэдра
void InRnd(tetrahedron &t);

// Вывод параметров тетраэдра в форматируемый поток
void Out(tetrahedron &t, ofstream &ofst);

// Вычисление площади поверхности тетраэдра
double Square(tetrahedron &t);

#endif //__tetrahedron__
