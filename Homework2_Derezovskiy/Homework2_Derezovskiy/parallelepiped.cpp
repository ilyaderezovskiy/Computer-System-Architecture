//------------------------------------------------------------------------------
// parallelepiped_In.cpp - содержит процедуру ввода параметров
// для уже созданного параллелепипеда
//------------------------------------------------------------------------------

#include "parallelepiped.h"

//------------------------------------------------------------------------------
// Ввод параметров параллелепипеда из файла
void Parallelepiped::In(std::istream& ifst) {
    ifst >> x >> y >> z >> materialDensity;
}

// Случайный ввод параметров параллелепипеда
void Parallelepiped::InRnd() {
    x = Shape::rnd20.Get();
    y = Shape::rnd20.Get();
    z = Shape::rnd20.Get();
    materialDensity = Shape::rnd20.Get();
}

//------------------------------------------------------------------------------
// Вывод параметров параллелепипеда в форматируемый поток
void Parallelepiped::Out(std::ostream& ofst) {
    ofst << "It is Parallelepiped: x = " << x << ", y = " << y
         << ", z = " << z << ". Material density = " << materialDensity
         << ". Square = " << Square() << "\n";
}

//------------------------------------------------------------------------------
// Вычисление периметра поверхности параллелепипеда
double Parallelepiped::Square() {
    return 2.0 * (x * y + y * z + x * z);
}