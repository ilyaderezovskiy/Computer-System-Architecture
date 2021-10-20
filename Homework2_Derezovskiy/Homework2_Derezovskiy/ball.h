#pragma once
#ifndef __ball__
#define __ball__

//------------------------------------------------------------------------------
// ball.h - содержит описание шара и его интерфейса
//------------------------------------------------------------------------------

#include <istream>
#include <ostream>

#include "rnd.h"
#include "shape.h"

// шар
class Ball : public Shape {
public:
    virtual ~Ball() {}
    // Ввод параметров шара из файла
    virtual void In(std::istream& ifst);
    // Случайный ввод параметров шара
    virtual void InRnd();
    // Вывод параметров шара в форматируемый поток
    virtual void Out(std::ostream& ofst);
    // Вычисление площади поверхности шара
    virtual double Square();
private:
    int r; // радиус
};

#endif //__ball__
