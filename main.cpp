#include <iostream>
#include "bf.h"

using namespace std;

int main()
{


//    bf x("0010001000000000000000000000000000000000011111111111111111111000");

    bf x("0010001001101110001001001010101111100010011011100010010010101011");

    x.print();

    bf y(5);
    y.print();

    return 0;
}
