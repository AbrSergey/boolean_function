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
    bf x("0111");

    int * p = x.walshHadardTransform();

    for (int i = 0; i < (1 << x.var()); i++)
        std::cout << p[i] << " ";

    std::cout << std::endl;
}

void hiCorIm()
{
    bf x("01111010");

    Base m = x.highCorIm();

    std::cout << "highCorIm = " << m << std::endl;
}

void nonLiner()
{
    bf x("01111010");

    Base m = x.nonLinearity();

    std::cout << "Nf = " << m << std::endl;
}

void bestApprox()
{
    bf x("01111010");

    Base * resVector = new Base[x.len()];

    resVector = x.bestAffineApproximation();

    std::cout << "resVector = ";

    for (Base i = 0; i < x.len(); i++)
        std::cout << resVector[i] << std::endl;
}

void autocor()
{
    bf x("0111");

    int * p = x.autocorrelation();

    for (int i = 0; i < (1 << x.var()); i++)
        std::cout << p[i] << " ";

    std::cout << std::endl;
}

void perfNonl()
{
    bf x("0111");

    int p = x.perfectNonlinearity();

    std::cout << p << std::endl;
}

int main()
{
//    testWeight();

//    testMobius();

//    walshHadardTransform();

//    hiCorIm();

//    nonLiner();

//    bestApprox();

//    autocor();

    perfNonl();

    return 0;
}
// написать нелинейность, наилучшее афинное приближение, наибольший порядок корреляционной иммунности
