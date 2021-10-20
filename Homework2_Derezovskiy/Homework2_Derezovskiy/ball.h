#pragma once
#ifndef __ball__
#define __ball__

//------------------------------------------------------------------------------
// ball.h - �������� �������� ���� � ��� ����������
//------------------------------------------------------------------------------

#include <istream>
#include <ostream>

#include "rnd.h"
#include "shape.h"

// ���
class Ball : public Shape {
public:
    virtual ~Ball() {}
    // ���� ���������� ���� �� �����
    virtual void In(std::istream& ifst);
    // ��������� ���� ���������� ����
    virtual void InRnd();
    // ����� ���������� ���� � ������������� �����
    virtual void Out(std::ostream& ofst);
    // ���������� ������� ����������� ����
    virtual double Square();
private:
    int r; // ������
};

#endif //__ball__
