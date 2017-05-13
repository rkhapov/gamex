#include "character.h"

gamex::Character::Character(const std::string &imgPath):
    _health(0),
    _cords(0, 0),
    _velocity(0, 0),
    _image(imgPath)
{
}

gamex::Character::Character(const sgl::Image &image):
    _health(0),
    _cords(0, 0),
    _velocity(0, 0),
    _image(image)
{
}

gamex::Character::Character(const std::string &imgPath, int health, Cords cords, Vector velocity):
    _health(health),
    _cords(cords),
    _velocity(velocity),
    _image(imgPath)
{
}


gamex::Character::Character(const sgl::Image &image, int health, Cords cords, Vector velocity):
    _health(health),
    _cords(cords),
    _velocity(velocity),
    _image(image)
{
}

gamex::Character::~Character()
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

void gamex::Character::updateCords(double dt, Vector accelerate)
{
    Cords::cord_t coordx = _cords.getx() + _velocity.getx() * dt + accelerate.getx() * dt * dt / 2;
    Cords::cord_t coordy = _cords.gety() + _velocity.gety() * dt + accelerate.gety() * dt * dt / 2;
    Cords::cord_t velx = _velocity.getx() + accelerate.getx() * dt;
    Cords::cord_t vely = _velocity.gety() + accelerate.gety() * dt;
    _velocity.setx(velx);
    _velocity.sety(vely);
    _cords.setx(coordx);
    _cords.sety(coordy);
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
