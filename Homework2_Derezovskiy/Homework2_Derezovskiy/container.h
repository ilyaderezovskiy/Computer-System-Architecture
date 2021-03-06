#pragma once
#ifndef __container__
#define __container__

//------------------------------------------------------------------------------
// container.h - ???????? ??? ??????,
// ?????????????? ?????????? ?????????
//------------------------------------------------------------------------------

#include "shape.h"
#include <istream>
#include <ostream>

//------------------------------------------------------------------------------
// ?????????? ????????? ?? ?????? ??????????? ???????
class Container {
public:
    Container();
    ~Container();

    // ???? ??????????? ?????????? ?? ?????????? ??????
    void In(std::istream& ifst);
    // ????????? ???? ??????????? ??????????
    void InRnd(int size);
    // ????? ??????????? ?????????? ? ????????? ?????
    void Out(std::ostream& ofst);
    // ?????????? ????? ???????? ???????????? ???? ????? ? ??????????
    double SquareSum();
    // ??????? ?????????? ?? ????????? (???????????? ??????)
    void Clear();
    int len; // ??????? ?????
    Shape* cont[10000];
};

#endif //__container__