//------------------------------------------------------------------------------
// tetrahedron.cpp - содержит функции обработки тетраэдра
//------------------------------------------------------------------------------

#include "tetrahedron.h"
#include "math.h"

//------------------------------------------------------------------------------
// Ввод параметров тетраэдра из потока
void Tetrahedron::In(std::istream& ifst) {
    ifst >> a >> materialDensity;
}

// Случайный ввод параметров тетраэдра
void Tetrahedron::InRnd() {
    a = Shape::rnd20.Get();
    materialDensity = Shape::rnd20.Get();
}

//------------------------------------------------------------------------------
// Вывод параметров тетраэдра в поток
void Tetrahedron::Out(std::ostream& ofst) {
    ofst << "It is Tetrahedron: a = " << a << ". Material density = " << materialDensity
        << ". Square = " << Square() << "\n";
}

//------------------------------------------------------------------------------
// Вычисление площади поверхности тетраэдра
double Tetrahedron::Square() {
    return double(a * a * sqrt(3));
}
