//------------------------------------------------------------------------------
// ball_In.cpp - содержит процедуру ввода параметров
// для уже созданного шара
//------------------------------------------------------------------------------

#define _USE_MATH_DEFINES
#include "math.h"
#include "ball.h"

//------------------------------------------------------------------------------
// Ввод параметров шара из файла
void Ball::In(std::istream& ifst) {
    ifst >> r >> materialDensity;
}

// Случайный ввод параметров шара
void Ball::InRnd() {
    r = Shape::rnd20.Get();
    materialDensity = Shape::rnd20.Get();
}

//------------------------------------------------------------------------------
// Вывод параметров шара в форматируемый поток
void Ball::Out(std::ostream& ofst) {
    ofst << "It is Ball: r = " << r << ". Material density = " << materialDensity
        << ". Square = " << Square() << "\n";
}

//------------------------------------------------------------------------------
// Вычисление площади поверхности шара
double Ball::Square() {
    return 4.0 * M_PI * (r * r);
}
