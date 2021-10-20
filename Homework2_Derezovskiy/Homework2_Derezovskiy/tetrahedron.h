#pragma once
#ifndef __tetrahedron__
#define __tetrahedron__

//------------------------------------------------------------------------------
// tetrahedron.h - содержит описание тетраэдра
//------------------------------------------------------------------------------

#include <istream>
#include <ostream>

#include "rnd.h"
#include "shape.h"

//------------------------------------------------------------------------------
// тетраэдр
class Tetrahedron : public Shape {
public:
    virtual ~Tetrahedron() {}
    // Ввод параметров тетраэдра из файла
    virtual void In(std::istream& ifst);
    // Случайный ввод параметров тетраэдра
    virtual void InRnd();
    // Вывод параметров тетраэдра в форматируемый поток
    virtual void Out(std::ostream& ofst);
    // Вычисление площади поверхности тетраэдра
    virtual double Square();
private:
    int a; // ребро
};

#endif
