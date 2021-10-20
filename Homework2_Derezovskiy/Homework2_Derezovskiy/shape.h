#pragma once
#ifndef __shape__
#define __shape__

//------------------------------------------------------------------------------
// shape.h - содержит описание обобщающей геометрической фигуры,
//------------------------------------------------------------------------------

#include <ostream>
#include <istream>

#include "rnd.h"

//------------------------------------------------------------------------------
// структура, обобщающая все имеющиеся фигуры

class Shape {
protected:
    static Random rnd20;
    static Random rnd3;
    double materialDensity; // плотность материала фигуры
public:
    virtual ~Shape() {};
    // Ввод обобщенной фигуры
    static Shape* StaticIn(std::istream& ifst);
    // Ввод обобщенной фигуры
    virtual void In(std::istream& ifst) = 0;
    // Случайный ввод обобщенной фигуры
    static Shape* StaticInRnd();
    // Виртуальный метод ввода случайной фигуры
    virtual void InRnd() = 0;
    // Вывод обобщенной фигуры
    virtual void Out(std::ostream& ofst) = 0;
    // Вычисление периметра обобщенной фигуры
    virtual double Square() = 0;
};

#endif
