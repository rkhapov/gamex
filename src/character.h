#ifndef CHARACTER_H
#define CHARACTER_H

#include "cords.h"
#include "vector.h"

namespace gamex
{
    class Character
    {
    public:
        Character();
        Character(int health, Cords cords, Vector velocity);
        void setCords(Cords cords);
        void setHealth(int health);
        void setVelocity(Vector velocity);
        void UpdateCords(double dt, Vector accelerate);

        Cords getCords() const;
        int getHealth() const;
        Vector getVelocity() const;

    private:
        int _health;
        Cords _cords;
        Vector _velocity;
    }
}

#endif // CHARACTER_H
