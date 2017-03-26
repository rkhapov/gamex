#include <cmath>

#include "vector.h"

long double gamex::Vector::lenght() const
{
    return std::sqrt(std::pow(getx(), 2) + std::pow(gety(), 2));
}
