#ifndef BF_H
#define BF_H

typedef unsigned int Base;
const int NUM_BIT_IN_BASE = 8*sizeof(Base);

class bf
{
private:
    Base *m_func; // value of function

    Base m_var; // number of variable. MAX m_var = 31

    Base m_len;

public:
    bf ();

    bf (std::string str);   // data[0]&1 = str[0], data[0]&10 = str[1], data[1]&1 = str[32], data[1]&10 = str[33]

    bf (int numberVar);    // constructor of random bits

    bf &operator = ( const bf & inputFunc );

    unsigned int operator [](const Base var) const;  // max var = '1' * 31 = 2147483647

    ~bf (); // check to correct

    unsigned int weight () const; // MAX weight = 2147483648

    void mobius () const; // Mobius function. It make the boolean values and print them

    void print() const;

    Base var () const;
};

#endif // BF_H
