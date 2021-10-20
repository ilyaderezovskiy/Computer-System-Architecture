#pragma once
#ifndef __tetrahedron__
#define __tetrahedron__

//------------------------------------------------------------------------------
// tetrahedron.h - �������� �������� ���������
//------------------------------------------------------------------------------

#include <istream>
#include <ostream>

#include "rnd.h"
#include "shape.h"

//------------------------------------------------------------------------------
// ��������
class Tetrahedron : public Shape {
public:
    virtual ~Tetrahedron() {}
    // ���� ���������� ��������� �� �����
    virtual void In(std::istream& ifst);
    // ��������� ���� ���������� ���������
    virtual void InRnd();
    // ����� ���������� ��������� � ������������� �����
    virtual void Out(std::ostream& ofst);
    // ���������� ������� ����������� ���������
    virtual double Square();
private:
    int a; // �����
};

#endif
