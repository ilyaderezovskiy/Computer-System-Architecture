#pragma once
#ifndef __parallelepiped__
#define __parallelepiped__

//------------------------------------------------------------------------------
// parallelepiped.h - содержит описание параллелепипеда и его интерфейса
//------------------------------------------------------------------------------

#include <istream>
#include <ostream>

#include "rnd.h"
#include "shape.h"

// параллелепипед
class Parallelepiped : public Shape {
public:
    virtual ~Parallelepiped() {}
    // Ввод параметров параллелепипеда из файла
    virtual void In(std::istream& ifst);
    // Случайный ввод параметров параллелепипеда
    virtual void InRnd();
    // Вывод параметров параллелепипеда в форматируемый поток
    virtual void Out(std::ostream& ofst);
    // Вычисление площади поверхности параллелепипеда
    virtual double Square();
private:
    int x, y, z; // рёбра
};

#endif //__parallelepiped__
