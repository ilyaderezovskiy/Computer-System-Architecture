#ifndef __ball__
#define __ball__

//------------------------------------------------------------------------------
// ball.h - содержит описание шара и его интерфейса
//------------------------------------------------------------------------------

#include <fstream>
using namespace std;

#include "rnd.h"

// шар
struct ball {
    int r; // радиус
    double materialDensity; // плотность материала фигуры
};

// Ввод параметров шара из файла
void In(ball &b, ifstream &ifst);

// Случайный ввод параметров шара
void InRnd(ball &b);

// Вывод параметров шара в форматируемый поток
void Out(ball &b, ofstream &ofst);

// Вычисление площади поверхности шара
double Square(ball &b);

#endif //__ball__
