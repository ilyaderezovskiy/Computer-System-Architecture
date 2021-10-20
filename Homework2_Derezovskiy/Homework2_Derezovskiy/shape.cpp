//------------------------------------------------------------------------------
// shape.cpp - содержит процедуры связанные с обработкой обобщенной фигуры
// и создания произвольной фигуры
//------------------------------------------------------------------------------

#include "ball.h"
#include "tetrahedron.h"
#include "parallelepiped.h"
#include "shape.h"

//------------------------------------------------------------------------------
Random Shape::rnd20(1, 20);
Random Shape::rnd3(1, 3);

//------------------------------------------------------------------------------
// Ввод параметров обобщенной фигуры из файла
Shape* Shape::StaticIn(std::istream& ifst) {
    int k;
    ifst >> k;
    Shape* sp = nullptr;
    switch (k) {
    case 1:
        sp = new Ball;
        break;
    case 2:
        sp = new Parallelepiped;
        break;
    case 3:
        sp = new Tetrahedron;
        break;
    }
    sp->In(ifst);
    return sp;
}

// Случайный ввод обобщенной фигуры
Shape* Shape::StaticInRnd() {
    auto k = Shape::rnd3.Get();
    Shape* sp = nullptr;
    switch (k) {
    case 1:
        sp = new Ball;
        break;
    case 2:
        sp = new Parallelepiped;
        break;
    case 3:
        sp = new Tetrahedron;
        break;
    }
    sp->InRnd();
    return sp;
}
