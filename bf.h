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

    bf (std::string str);

    ~bf ();

    void print() const;
};

#endif // BF_H
