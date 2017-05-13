#ifndef PLAYER_H
#define PLAYER_H

#include "character.h"

namespace gamex
{
    class Player: public Character
    {
    public:
        Player();
        Player(int health, Cords cords, Vector velocity);
    };
}

#endif // PLAYER_H
