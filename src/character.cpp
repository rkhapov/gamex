#include "character.h"

gamex::Character::Character():
    health(0),
    cords(0, 0),
    velocity(0, 0)
{

}

gamex::Character::Character(int health, Cords cords, Vector velocity):
    _health(health),
    _cords(cords),
    _velocity(velocity)
{

}

void gamex::Character::setCords(Cords cords)
{
    _cords = cords;
}

void gamex::Character::setHealth(int health)
{
    _health = health;
}

void gamex::Character::setVelocity(Vector velocity)
{
    _velocity = velocity;
}

void gamex::Character::UpdateCords(double dt, Vector accelerate)
{
    coordx = _cords.getx() + _velocity.getx() * dt + accelerate.getx() * dt * dt / 2;
    coordy = _cords.gety() + _velocity.gety() * dt + accelerate.gety() * dt * dt / 2;
    velx = _velocity.getx() + accelerate.getx() * dt;
    vely = _velocity.gety() + accelerate.gety() * dt;
    _velocity.setx(velx);
    _velocity.sety(vely);
    _cords.setx(coordx);
    _cords.sety(coordy)
}

gamex::Cords gamex::Character::getCords() const
{
    return _cords;
}

int gamex::Character::getHealth() const
{
    return _health;
}

gamex::Vector gamex::Character::getVelocity() const
{
    return _velocity;
}
