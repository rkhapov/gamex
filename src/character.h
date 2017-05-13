#ifndef CHARACTER_H
#define CHARACTER_H

#include "sgl.h"

#include "cords.h"
#include "vector.h"

namespace gamex
{
    class Character
    {
    public:
        Character(const std::string &imgPath);
        Character(const sgl::Image &image);
        Character(const std::string &imgPath, int health, Cords cords, Vector velocity);
        Character(const sgl::Image &image, int health, Cords cords, Vector velocity);
        virtual ~Character();

        void setCords(Cords cords);
        void setHealth(int health);
        void setVelocity(Vector velocity);
        void updateCords(double dt, Vector accelerate);

        Cords getCords() const;
        int getHealth() const;
        Vector getVelocity() const;

    private:
        int _health;
        Cords _cords;
        Vector _velocity;
        sgl::Image _image;
    };
}

#endif // CHARACTER_H
