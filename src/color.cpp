#include <allegro5/allegro5.h>
#include <allegro5/allegro_color.h>

#include "color.h"
#include "my_string.h"

sgl::Color::Color()
{
    _color = new ALLEGRO_COLOR;

    *_color = al_color_name("black");
}

sgl::Color::Color(ALLEGRO_COLOR color)
{
    _color = new ALLEGRO_COLOR;

    *_color = color;
}

sgl::Color::Color(unsigned char r, unsigned char g, unsigned char b)
{
    _color = new ALLEGRO_COLOR;

    setFromMap(r, g, b);
}

sgl::Color::Color(const std::string &name)
{
    _color = new ALLEGRO_COLOR;

    setFromName(name);
}

sgl::Color::~Color()
{
    delete _color;
}

void sgl::Color::setFromMap(unsigned char r, unsigned char g, unsigned char b)
{   
    *_color = al_map_rgb(r, g, b);
}

void sgl::Color::setFromName(const std::string &name)
{    
    *_color = al_color_name(gamex::convertToLowerCase(name).c_str());
}

void sgl::Color::get(unsigned char &r, unsigned char &g, unsigned char &b) const
{
    al_unmap_rgb(*_color, &r, &g, &b);
}

unsigned char sgl::Color::getB() const
{
    unsigned char b, t;
    get(t, t, b);
    return b;
}

unsigned char sgl::Color::getG() const
{
    unsigned char g, t;
    get(t, g, t);
    return g;
}

unsigned char sgl::Color::getR() const
{
    unsigned char r, t;
    get(r, t, t);
    return r;
}

void sgl::Color::setR(unsigned char r)
{
    setFromMap(r, getG(), getB());
}

void sgl::Color::setB(unsigned char b)
{
    setFromMap(getR(), getG(), b);
}

void sgl::Color::setG(unsigned char g)
{
    setFromMap(getR(), g, getB());
}

sgl::Color::operator ALLEGRO_COLOR() const
{
    return *_color;
}
