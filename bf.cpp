#include <iostream>
#include <string>
#include <assert.h>
#include <math.h>
#include <bf.h>

bf::bf() : m_func (NULL), m_var(0), m_len(0) {}

bf::bf(std::string str)
{
    assert(!str.empty());

    unsigned int lenStr = str.length();
    assert((lenStr & (lenStr - 1)) == 0);   // lenStr must be a power of 2

    // computing m_var
    unsigned int tmpLen = lenStr;
    m_var = 0;
    while (tmpLen != 1){
        tmpLen >>= 1;
        m_var++;
    }

    // computing m_len
    int whole = lenStr / NUM_BIT_IN_BASE;
    int remainder = lenStr % NUM_BIT_IN_BASE;

    m_len = whole;
    if (remainder != 0) m_len++;

    // memory allocation for m_func
    m_func = new Base[m_len];

    // write str to m_func
    for (int i = 0; i < whole; i++)
        for (int j = 0; j < NUM_BIT_IN_BASE; j++){
            char ch = str[i * NUM_BIT_IN_BASE + j];
            assert(ch == '0' || ch == '1');

            if (ch == '1') m_func[i] |= 1;
            if (j < NUM_BIT_IN_BASE - 1) m_func[i] <<= 1;
        }

    if (remainder != 0)
        for (int j = 0; j < remainder; j++){
            char ch = str[whole * NUM_BIT_IN_BASE + j];
            assert(ch == '0' || ch == '1');

            if (ch == '1') m_func[whole] |= 1;
            if (j < remainder - 1) m_func[whole] <<= 1;
        }

}

bf::~bf()
{
    if (m_func) delete [] m_func;
}

void bf::print() const
{
    std::cout << "m_var = " << m_var << std::endl;
    std::cout << "m_len = " << m_len << std::endl;
    std::cout << "m_func = ";

    int whole = (2 << (m_var - 1)) / NUM_BIT_IN_BASE;
    int remainder = (2 << (m_var - 1)) % NUM_BIT_IN_BASE;

    unsigned int funcHelper;
    for (int i = 0; i < whole; i++){
        funcHelper = m_func[i];
        for (int j = 0; j < NUM_BIT_IN_BASE; j++){
            if ((funcHelper & 1) == 1) std::cout << "1 ";
            else std::cout << "0 ";

            funcHelper >>= 1;
        }
    }

    if (remainder != 0){
        funcHelper = m_func[m_len - 1];
        for (int j = 0; j < remainder; j++){
            if ((funcHelper & 1) == 1) std::cout << "1 ";
            else std::cout << "0 ";

            funcHelper >>= 1;
        }
    }

    std::cout << std::endl;
}
