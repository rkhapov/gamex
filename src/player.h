#ifndef PLAYER_H
#define PLAYER_H

#include "cords.h"
#include "vector.h"

namespace gamex
{
    class Player
    {
    public:
        Player();
        Player(int health, Cords cords, Vector velocity);
        void setCords(Cords cords);
        void setHealth(int health);
        void setVelocity(Vector velocity);

        Cords getCords() const;
        int getHealth() const;
        Vector getVelocity() const;

    private:
        int _health;
        Cords _cords;
        Vector _velocity;
    }
}

#endif // PLAYER_H
