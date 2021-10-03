//------------------------------------------------------------------------------
// tetrahedron.cpp - содержит функции обработки тетраэдра
//------------------------------------------------------------------------------

#include "math.h"
#include "tetrahedron.h"

//------------------------------------------------------------------------------
// Ввод параметров тетраэдра из потока
void In(tetrahedron &t, ifstream &ifst) {
    ifst >> t.a >> t.materialDensity;
}

// Случайный ввод параметров тетраэдра
void InRnd(tetrahedron &t) {
    t.a = Random();
    t.materialDensity = Random();
}

//------------------------------------------------------------------------------
// Вывод параметров тетраэдра в поток
void Out(tetrahedron &t, ofstream &ofst) {
    ofst << "It is Tetrahedron: a = " << t.a << ". Material density = " << t.materialDensity
         << ". Square = " << Square(t) << "\n";
}

//------------------------------------------------------------------------------
// Вычисление площади поверхности тетраэдра
double Square(tetrahedron &t) {
    return double(t.a * t.a * sqrt(3));
}
