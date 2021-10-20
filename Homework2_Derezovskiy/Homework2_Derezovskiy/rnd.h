#ifndef __rnd__
#define __rnd__

#include <ctime>   // ��� ������� time()

//------------------------------------------------------------------------------
// rnd.h - �������� ��������� ��������� ����� � ��������� �� 1 �� 20
//------------------------------------------------------------------------------

class Random {
public:
    Random(int f, int l) {
        if (f <= l) {
            first = f;
            last = l;
        }
        else {
            first = l;
            last = f;
        }
        // ��������� ���� � �������� ��������������
        srand(static_cast<unsigned int>(time(0)));
    }
    // ��������� ���������� ����� � �������� ���������
    int Get() {
        return rand() % (last - first + 1) + first;
    }
private:
    int first;
    int last;
};

#endif //__rnd__
