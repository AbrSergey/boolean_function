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
    while (tmpLen != 1)
    {
        tmpLen >>= 1;
        m_var++;
    }

    // computing m_len
    int whole = lenStr / NUM_BIT_IN_BASE;
    int remainder = lenStr % NUM_BIT_IN_BASE;

    m_len = whole;
    if (remainder != 0) m_len++;

    // allocation memory for m_func
    m_func = new Base[m_len];

    // write str to m_func
    for (int i = 0; i < whole; i++)
        for (int j = 0; j < NUM_BIT_IN_BASE; j++)
        {
            int x = (i + 1) * NUM_BIT_IN_BASE - j - 1;
            char ch = str[x];
            assert(ch == '0' || ch == '1');

            if (ch == '1') m_func[i] |= 1;
            if (j < NUM_BIT_IN_BASE - 1) m_func[i] <<= 1;
        }

    if (remainder != 0)
        for (int j = 0; j < remainder; j++)
        {
            char ch = str[lenStr - (whole * NUM_BIT_IN_BASE + j) - 1];
            assert(ch == '0' || ch == '1');

            if (ch == '1') m_func[whole] |= 1;
            if (j < remainder - 1) m_func[whole] <<= 1;
        }

}

bf::bf(int numberVar)
{
    assert (numberVar > 0 && numberVar <= 31);

    m_var = numberVar;

    unsigned int numberBits = 1 << m_var;

    // computing m_len
    int whole = numberBits / NUM_BIT_IN_BASE;
    int remainder = numberBits % NUM_BIT_IN_BASE;

    m_len = whole;
    if (remainder != 0) m_len++;

    // allocation memory for m_func
    m_func = new Base[m_len];

    // fill in m_func ramdom bits
    for (unsigned int i = 0; i < m_len; i++)
        m_func[i] = rand() - rand();

    if (remainder != 0) // can without it?
    {
        m_func[m_len - 1] <<= remainder;
        m_func[m_len - 1] >>= remainder;
    }
}

bf::~bf()
{
    if (m_func) delete [] m_func;
}

unsigned int bf::weight()
{
    assert (m_len != 0);    // boolean function not set

    unsigned int result = 0;

    for (unsigned int i = 0; i < m_len; i++)
    {
        unsigned int n = 0; // n is weight of current base
        Base x = m_func[i];
        while (x)
        {
            x &= x - 1;
            n++;
        }
        result += n;
    }
    return result;
}

void bf::print() const
{
    std::cout << "m_len = " << m_len << std::endl;
    std::cout << "m_var = " << m_var << std::endl;
    std::cout << "m_func = ";

    int whole = (2 << (m_var - 1)) / NUM_BIT_IN_BASE;
    int remainder = (2 << (m_var - 1)) % NUM_BIT_IN_BASE;

    unsigned int funcHelper;
    for (int i = 0; i < whole; i++)
    {
        funcHelper = m_func[i];
        for (int j = 0; j < NUM_BIT_IN_BASE; j++)
        {
            if ((funcHelper & 1) == 1) std::cout << "1";
            else std::cout << "0";

            funcHelper >>= 1;
        }
    }

    if (remainder != 0){
        funcHelper = m_func[m_len - 1];
        for (int j = 0; j < remainder; j++)
        {
            if ((funcHelper & 1) == 1) std::cout << "1";
            else std::cout << "0";

            funcHelper >>= 1;
        }
    }

    std::cout << std::endl;
}
