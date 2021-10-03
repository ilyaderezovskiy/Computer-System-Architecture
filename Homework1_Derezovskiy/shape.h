#ifndef __shape__
#define __shape__

//------------------------------------------------------------------------------
// shape.h - содержит описание обобщающей геометрической фигуры,
//------------------------------------------------------------------------------

#include "ball.h"
#include "parallelepiped.h"
#include "tetrahedron.h"

//------------------------------------------------------------------------------
// структура, обобщающая все имеющиеся фигуры
struct shape {
    // значения ключей для каждой из фигур
    enum key {BALL, PARALLELEPIPED, TETRAHEDRON};
    key k; // ключ
    // используемые альтернативы
    double materialDensity;
    union { // используем простейшую реализацию
        ball b;
        parallelepiped p;
        tetrahedron t;
    };
};

// Ввод обобщенной фигуры
shape *In(ifstream &ifdt);

// Случайный ввод обобщенной фигуры
shape *InRnd();

// Вывод обобщенной фигуры
void Out(shape &s, ofstream &ofst);

// Вычисление периметра обобщенной фигуры
double Square(shape &s);

#endif
