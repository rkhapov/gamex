
#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <stdexcept>

#include "color.h"
#include "image.h"

class ALLEGRO_DISPLAY;
class ALLEGRO_MOUSE_CURSOR;

/*
 * Window - class to control Windows
 * wrapper of ALLEGRO_DISPLAY
*/

namespace sgl
{

    class WindowErrorException: public std::runtime_error
    {
    public:
        WindowErrorException(const std::string &msg):
            runtime_error(msg)
        {}
    };

    class Window
    {
    public:

        Window(int width, int height);
        ~Window();

        int getWidth() const;
        int getHeight() const;

        void resize(int width, int height);


        void setPosition(int x, int y);


        void setTitle(const std::string &title);


        void setIcon(Image &image);


        void clear(Color color = static_cast<std::string>("white"));


        void makeTarget();


        void setCursor(Image &image, int xfocus, int yfocus);
        void hideCursor();
        void showCursor();

        /*
         * Flip display's buffer (same as update)
        */
        void flip();

        Image getBackBufferImage() const;

        /*
         * You can use this call with allegro functions
        */
        operator ALLEGRO_DISPLAY *();
        operator const ALLEGRO_DISPLAY *() const;

    private:
        ALLEGRO_DISPLAY *_display;
        ALLEGRO_MOUSE_CURSOR *_cursor;

        Window(const Window &window);
        Window &operator =(const Window &window) const;
    };
}

#endif // WINDOW_H

