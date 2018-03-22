#include <iostream>
#include "bf.h"

using namespace std;

void testOperator ()
{
    bf x("0010001001101110001001001010101111100010011011100010010010101011");
    x.print();

    unsigned int maxVar = 1 << x.var();

    for (unsigned int i = 0; i < maxVar; i++)
        cout << "x[" << i << "] = " << x[i] << endl;
}

int main()
{


//    bf x("0010001000000000000000000000000000000000011111111111111111111000");

//    bf x("0010001001101110001001001010101111100010011011100010010010101011");

//    x.print();

//    cout << "weight = " << x.weight() << endl;

    testOperator();

    return 0;
}
