#include "player.h"

gamex::Player::Player():
    _health(0),
    _cords(0, 0),
    _velocity(0, 0)
{

}

gamex::Player::Player(int health, Cords cords, Vector velocity):
    _health(health),
    _cords(cords),
    _velocity(velocity)
{

}

void gamex::Player::setCords(Cords cords)
{
    _cords = cords;
}

void gamex::Player::setHealth(int health)
{
    _health = health;
}

void gamex::Player::setVelocity(Vector velocity)
{
    _velocity = velocity;
}

gamex::Cords gamex::Player::getCords() const
{
    return _cords;
}

int gamex::Player::getHealth() const
{
    return _health;
}

gamex::Vector gamex::Player::getVelocity() const
{
    return _velocity;
}
