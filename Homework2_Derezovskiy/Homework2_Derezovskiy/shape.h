#pragma once
#ifndef __shape__
#define __shape__

//------------------------------------------------------------------------------
// shape.h - �������� �������� ���������� �������������� ������,
//------------------------------------------------------------------------------

#include <ostream>
#include <istream>

#include "rnd.h"

//------------------------------------------------------------------------------
// ���������, ���������� ��� ��������� ������

class Shape {
protected:
    double materialDensity; // ��������� ��������� ������ 
    static Random rnd20;
    static Random rnd3;
public:
    virtual ~Shape() {};
    // ���� ���������� ������
    static Shape* StaticIn(std::istream& ifst);
    // ���� ���������� ������
    virtual void In(std::istream& ifst) = 0;
    // ��������� ���� ���������� ������
    static Shape* StaticInRnd();
    // ����������� ����� ����� ��������� ������
    virtual void InRnd() = 0;
    // ����� ���������� ������
    virtual void Out(std::ostream& ofst) = 0;
    // ���������� ��������� ���������� ������
    virtual double Square() = 0;
};

#endif