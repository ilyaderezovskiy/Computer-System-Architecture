#pragma once
#ifndef __parallelepiped__
#define __parallelepiped__

//------------------------------------------------------------------------------
// parallelepiped.h - �������� �������� ��������������� � ��� ����������
//------------------------------------------------------------------------------

#include <istream>
#include <ostream>

#include "rnd.h"
#include "shape.h"

// ��������������
class Parallelepiped : public Shape {
public:
    virtual ~Parallelepiped() {}
    // ���� ���������� ��������������� �� �����
    virtual void In(std::istream& ifst);
    // ��������� ���� ���������� ���������������
    virtual void InRnd();
    // ����� ���������� ��������������� � ������������� �����
    virtual void Out(std::ostream& ofst);
    // ���������� ������� ����������� ���������������
    virtual double Square();
private:
    int x, y, z; // ����
};

#endif //__parallelepiped__
