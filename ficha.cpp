#include "ficha.h"

ficha::ficha(char idd)
{
    this->idd = idd;
}

char ficha::getidd() const
{
    return idd;
}

void ficha::setidd(char idd1)
{
    this->idd = idd1;
}
