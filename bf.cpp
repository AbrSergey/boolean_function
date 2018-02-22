#include <iostream>
#include <string>
#include <assert.h>
#include <bf.h>

bf::bf() : m_func (NULL), m_var(0), m_len(0) {}

bf::bf(std::string str)
{
    assert(!str.empty());

    for (unsigned int i = 0; i < str.length(); i++){

    }

}

bf::~bf()
{
    if (m_func) delete [] m_func;
}

//unsigned int bf::lenFunc()
//{
//    unsigned int countComb = 2 << (m_var - 1);
//    unsigned int whole = countComb / NUM_BIT_IN_BASE;
//    unsigned int remainder = countComb / NUM_BIT_IN_BASE;

//    if (remainder != 0) return whole++;
//    else return whole;
//}
