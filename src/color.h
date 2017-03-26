#ifndef COLOR_H
#define COLOR_H

#include <string>

class ALLEGRO_COLOR;

namespace sgl
{
    /*
     * Color - wrapper of ALLEGRO_COLOR
    */

    class Color
    {
    public:
        Color();
        Color(const std::string &name);
        Color(ALLEGRO_COLOR color);
        Color(unsigned char r, unsigned char g, unsigned char b);
        ~Color();

        void setFromMap(unsigned char r, unsigned char g, unsigned char b);

        void setFromName(const std::string &name);

        void setR(unsigned char r);
        void setG(unsigned char g);
        void setB(unsigned char b);


        void get(unsigned char &r, unsigned char &g, unsigned char &b) const;
        unsigned char getR() const;
        unsigned char getG() const;
        unsigned char getB() const;

        operator ALLEGRO_COLOR() const;

    private:
        ALLEGRO_COLOR *_color;
    };
}

#endif // COLOR_H

