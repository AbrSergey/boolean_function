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

bf::bf(const bf &input)
{
    m_var = input.m_var;
    m_len = input.m_len;
    m_func = new Base[m_len];

    for (Base i = 0; i < m_len; i++) m_func[i] = input.m_func[i];
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

bf bf::operator >>(const Base numberShifts) const
{
    // this operator write for mobius function, where 0 < numberShifts < 2**31==2147483648
    assert (numberShifts > 0 && numberShifts < 2147483648);

    bf result = (*this);

    int whole = numberShifts / NUM_BIT_IN_BASE;
    int remainder = numberShifts % NUM_BIT_IN_BASE;

    if (whole != 0) // base shift
    {
        for (int i = m_len - 1; i >= whole; i--)
            result.m_func[i] = result.m_func[i - whole];

        for (int i = 0; i < whole; i++)
            result.m_func[i] = 0;
    }

    // remainder shift
    // construct the mask

    Base mask = 1;
    for (int j = 1; j < remainder; j++)
    {
        mask <<= 1;
        mask |= 1;
    }
    mask <<= (NUM_BIT_IN_BASE - remainder);

    // shift algorithm

    result.m_func[m_len - 1] <<= remainder;

    // to remove unnecessary bits
    Base tmp = NUM_BIT_IN_BASE - ((1 << m_var) % NUM_BIT_IN_BASE);
    result.m_func[m_len - 1] <<= tmp;
    result.m_func[m_len - 1] >>= tmp;

    for (Base i = m_len - 1; i > 0; i--)
    {
        Base help = result.m_func[i - 1] & mask;

        help >>= (NUM_BIT_IN_BASE - remainder);

        result.m_func[i] |= help;

        result.m_func[i - 1] <<= numberShifts;
    }

    return result;
}

bf bf::operator &(const bf input) const
{
    assert (m_len > 0);

    bf result = (*this);

    for (Base i = 0; i < m_len; i++)
        result.m_func[i] = m_func[i] & input.m_func[i];

    return result;
}

bf bf::operator ^(const bf input) const
{
    assert ((m_len == input.m_len) && (m_var == input.m_var) && m_len > 0);

    bf result(m_var);

    for (Base i = 0; i < m_len; i++)
        result.m_func[i] = m_func[i] ^ input.m_func[i];

    return result;
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

bf bf::mobius() const
{
    assert (m_len != 0);    // function must be specified

////    // initialiation data for mobius

//////    bf mobiusFunc;
//////    mobiusFunc.m_var = m_var;
//////    mobiusFunc.m_len = m_len;
//////    mobiusFunc.m_func = new Base [m_len];

////    // fill in mobiusData

////    Base maxVar = 1 << m_var;

////    for (Base i = 0; i < maxVar; i++)
////    {
////        unsigned int tmpMobiusData = 0;

////        for (Base j = 0; j <= i; j++)
////        {
////            Base tmp = j | i;
////            if (tmp <= i) tmpMobiusData = (tmpMobiusData + (*this)[j]) % 2;
////        }

////        Base whole = i / NUM_BIT_IN_BASE;
////        Base remainder = i % NUM_BIT_IN_BASE;
////        Base mask = tmpMobiusData << remainder;
////        mobFunc.m_func[whole] |= mask;
////    }

//    Base const1 = 0xaaaaaaaa;   // 0b10101010101010101010101010101010
//    Base const2 = 0xcccccccc;   // 0b11001100110011001100110011001100
//    Base const3 = 0xf0f0f0f0;   // 0b11110000111100001111000011110000
//    Base const4 = 0xff00ff00;   // 0b11111111000000001111111100000000
//    Base const5 = 0xffff0000;   // 0b11111111111111110000000000000000

//    bf g = (*this);

//    Base i = 0;

//    for (; i < 5 && i < m_var; i++)
//    {
//        Base cons;

//        if (i == 0) cons = const1;
//        if (i == 1) cons = const2;
//        if (i == 2) cons = const3;
//        if (i == 3) cons = const4;
//        if (i == 4) cons = const5;

//        bf h (m_var, FillTypeZero);

//        for (Base j = 0; j < m_len; j++)
//            h.m_func[j] = cons;

//        g = g ^ ((g >> (1 << i)) & h);
//    }

//    for (; i >= 5 && i < m_var; i++)
//    {
//        int subBase = 1 << (i - 5); // quantity of bases with same value

//        assert (m_len % subBase == 0);  // ?? subBase*2 ??

//        bf h (m_var, FillTypeZero);

//        bool flag = false;

//        for (Base j = 0; j < m_len / subBase; j++)
//        {
//            for (int k = 0; k < subBase; k++)
//            {
//                if (!flag) h.m_func[j * subBase + k] = 0x00000000;
//                else h.m_func[j * subBase + k] = 0xffffffff;
//            }
//            if (flag == true) flag = false;
//            else flag = true;
//        }

//        g = g ^ ((g >> (1 << i)) & h);
//    }

//    return g;

    bf f = (*this);
    bf g = (*this);

    for (int i = 1; i <= m_var; i++)
    {
        int arg = 0;

        Base quant = 1 << i;

        Base numberIter = (1 << m_var) / quant;

        for (int j = 0; j < numberIter; j++)
        {
            for (int k = 0; k < quant / 2; k++)
            {
                g.m_func[arg] = f.m_func[arg];
                arg++;
            }

            for (int k = 0; k < quant / 2; k++)
            {
                g.m_func[arg] = f.m_func[arg] ^ f.m_func[arg - (quant / 2)];
                arg++;
            }
        }
        f = g;
    }

    return g;
}

void bf::print() const
{
//    std::cout << "m_len = " << m_len << std::endl;
//    std::cout << "m_var = " << m_var << std::endl;
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
