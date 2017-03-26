#ifndef CORDS_H
#define CORDS_H

namespace gamex
{
    class Cords
    {
    public:
        typedef long double cord_t;

        Cords();
        Cords(cord_t x, cord_t y);

        virtual ~Cords();

        void setx(cord_t x);
        void sety(cord_t y);

        cord_t getx() const;
        cord_t gety() const;

    private:
        cord_t _x;
        cord_t _y;
    };
}

#endif // CORDS_H
