#include "cords.h"

gamex::Cords::Cords()
{
    setx(cord_t());
    sety(cord_t());
}

gamex::Cords::Cords(cord_t x, cord_t y)
{
    setx(x);
    sety(y);
}

gamex::Cords::~Cords()
{
}

gamex::Cords::cord_t gamex::Cords::getx() const
{
    return _x;
}

gamex::Cords::cord_t gamex::Cords::gety() const
{
    return _y;
}

void gamex::Cords::setx(cord_t x)
{
    _x = x;
}

void gamex::Cords::sety(cord_t y)
{
    _y = y;
}





