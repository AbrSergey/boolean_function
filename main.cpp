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

void testWeight ()
{
    for (int i = 1; i < 32; i++){

        bf x(i);
        unsigned int w = x.weight();

        std::cout << "w = " << w << std::endl;

        unsigned int n = 1 << i;
        float f = float(w) / float(n);

        std::cout << "f = " << std::fixed << f << std::endl;
        std::cout << std::endl;
    }
}

void testMobius ()
{
//    int q = 3;

    for (int i = 0; i < 1; i++)
    {
        bf x("01100000");

        bf y = x.mobius();

        x.print();

        y.print();

//        bf z = y.mobius();
//        if (z == x) cout << "TRUE" << endl;
//        else cout << "False" << endl;

        // Anf
        std::cout << "ANF = ";
        x.printAnf();

        // degree
        std::cout << "degree = " << x.degree() << endl;
    }
}

void walshHadardTransform()
{
    bf x("0001000100011110000100010001111000010001000111101110111011100001");

    int * p = x.walshHadardTransform();

    for (int i = 0; i < (1 << x.var()); i++)
        std::cout << p[i] << " ";

    std::cout << std::endl;
}

int main()
{
//    testWeight();

//    testMobius();

    walshHadardTransform();



    return 0;
}
// написать нелинейность, наилучшее афинное приближение, наибольший порядок корреляционной иммунности
