#ifndef VECTOR_H
#define VECTOR_H

#include "cords.h"

namespace gamex
{
    class Vector: public Cords
    {
    public:
        Vector(): Cords() {}
        Vector(Cords::cord_t x, Cords::cord_t y): Cords(x, y) {}

        long double lenght() const;
    };
}

#endif // VECTOR_H
