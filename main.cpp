#include <iostream>
#include "bf.h"

using namespace std;

void testOperator ()
{
//    bf x("0010001001101110001001001010101111100010011011100010010010101011");
    bf x("00110101");
    x.print();

    unsigned int maxVar = 1 << x.var();

    for (unsigned int i = 0; i < maxVar; i++)
        cout << "x[" << i << "] = " << x[i] << endl;
}

void testMobius()
{
    bf x("00110101");

    x.print();

    // initialization mobFunc

    bf mobFunc("00000000");

    x.mobius(mobFunc);

    mobFunc.print();

    // test

    bf z("00000000");

    mobFunc.mobius(z);

    z.print();

    if (z == x) cout << "TRUE" << endl;
    else cout << "False" << endl;
}

int main()
{
    testMobius();

    return 0;
}


//написать оператор == и сделать нормальный тест для мобиуса
