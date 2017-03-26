#ifndef FONT_H
#define FONT_H

#include <stdexcept>
#include <string>

class ALLEGRO_FONT;

namespace sgl
{
    class Window;
    class Color;

    /*
     * Font - wrapper of ALLEGRO_FONT
     * Containes methods to write text
    */

    class Font
    {
    public:

        class FontErrorException: public std::runtime_error
        {
        public:
            FontErrorException(const std::string &msg):
                runtime_error(msg)
            {}
        };

        Font(const std::string &path, int size);
        Font(const Font &font);
        ~Font();

        int getLineHeight() const;
        int getAscent() const;
        int getDescent() const;

        const std::string path() const;

        static const int ALIGN_LEFT;
        static const int ALIGN_RIGHT;
        static const int ALIGN_CENTRE;
        static const int ALIGN_CENTER;

        /*
         * Draw one-line text at window with flags
         * flags can be one of ALIGN_CENTRE, ALIGN_LEFT and ALIGN_RIGHT or 0
         * '\n' are ignoring
        */

        void drawText(Window &window, const Color &color, const std::string &text,
                      float x, float y, int flags = 0) const;

        /*
         * You can use this class with allegro functions
        */
        operator ALLEGRO_FONT*();
        operator const ALLEGRO_FONT*() const;

        Font &operator =(const Font &font);

    private:
        ALLEGRO_FONT *_font;
        std::string _path;
        int _openSize;

        void _copyFrom(const Font &font);
    };
}

#endif // FONT_H

