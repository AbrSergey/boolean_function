#include <iostream>
#include <cstdlib>
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

bf::bf(int numberVar, FillType filltype)
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

    switch (filltype){

    case FillTypeRandom:
    {
        // fill in m_func ramdom bits
        for (unsigned int i = 0; i < m_len; i++)
            m_func[i] = rand() - rand();

        if (remainder != 0) m_func[m_len - 1] >>= NUM_BIT_IN_BASE - remainder;

        break;
    }

    case FillTypeZero:
    {
        // fill in m_func with ZEROs
        for (Base i = 0; i < m_len; i++) m_func[i] = 0;
        break;
    }

    case FillTypeOne:
    {
        // fill in m_func with ONEs
        for (Base i = 0; i < m_len; i++) m_func[i] = MAX_NUMBER_IN_BASE;
        if (remainder != 0) m_func[m_len - 1] >>= NUM_BIT_IN_BASE - remainder;
        break;
    }

    default:
        assert("!Invalid FillType");
    }
}

bf &bf::operator =(const bf &inputFunc)
{
    m_var = inputFunc.m_var;

    if (m_len != inputFunc.m_len)
    {
        m_len = inputFunc.m_len;

        delete [] m_func;

        m_func = new Base [m_len];
    }

    for (unsigned int i = 0; i < m_len; i++)
        m_func[i] = inputFunc.m_func[i];

    return *this;
}

unsigned int bf::operator [](const Base var) const
{
    assert (m_len != 0);    // function must be specified
    unsigned int check = 1 << m_var;
    assert (var < check);   // var must be <= ('1' * m_var)

    unsigned int whole = var / NUM_BIT_IN_BASE; // it is number of base
    unsigned int remainder = var % NUM_BIT_IN_BASE; // it is number of bit in m_func[whole]
    unsigned int mask = 1 << remainder;
    unsigned int res = m_func[whole] & mask;
    res >>= remainder;

    assert (res == 0 || res == 1);

    return res;
}

bool bf::operator ==(const bf &inputFunc) const
{
    if (m_var != inputFunc.m_var) return false;

    assert(m_len == inputFunc.m_len); // they must be equal!!!!

    for (Base i = 0; i < m_len; i++)
        if (m_func[i] != inputFunc.m_func[i]) return false;

    return true;
}

bf::~bf()
{
    if (m_func) delete [] m_func;
}

unsigned int bf::weight() const
{
    assert (m_len != 0);    // function must be specified

    unsigned int result = 0;

    for (unsigned int i = 0; i < m_len; i++)
    {
        Base x = m_func[i];
        while (x)
        {
            x &= x - 1;
            result++;
        }
    }
    return result;
}

void bf::mobius(bf &mobFunc) const
{
    assert (m_len != 0);    // function must be specified

    // initialiation data for mobius

//    bf mobiusFunc;
//    mobiusFunc.m_var = m_var;
//    mobiusFunc.m_len = m_len;
//    mobiusFunc.m_func = new Base [m_len];

    // fill in mobiusData

    Base maxVar = 1 << m_var;

    for (Base i = 0; i < maxVar; i++)
    {
        unsigned int tmpMobiusData = 0;

        for (Base j = 0; j <= i; j++)
        {
            Base tmp = j | i;
            if (tmp <= i) tmpMobiusData = (tmpMobiusData + (*this)[j]) % 2;
        }

        Base whole = i / NUM_BIT_IN_BASE;
        Base remainder = i % NUM_BIT_IN_BASE;
        Base mask = tmpMobiusData << remainder;
        mobFunc.m_func[whole] |= mask;
    }
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

Base bf::var() const
{
    return m_var;
}
