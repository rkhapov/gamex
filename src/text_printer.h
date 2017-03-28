#ifndef TEXT_PRINTER_H
#define TEXT_PRINTER_H

#include <stdexcept>

#include "color.h"
#include "font.h"

namespace sgl
{
    /*
     * TextPrinter - class that contatines font and color of printing
     * Just for some comfort :)
    */

    class TextPrinter
    {
    public:
        TextPrinter();
        TextPrinter(Window &window, const Color &color, const Font &font);
        TextPrinter(const TextPrinter &textPrinter);
        ~TextPrinter();

        void setColor(const Color &color);
        void setFont(const Font &font);

        const Color& getColor() const;
        const Font& getFont() const;

        void setTargetWindow(Window &window);
        Window& getTargetWindow() const;

        void drawText(const std::string &text, float x, float y, int flags = 0) const;

        TextPrinter& operator =(const TextPrinter &textPrinter);

    private:
        Color  *_color;
        Font   *_font;
        mutable Window *_targetWindow;
    };


    class TextPrinterException: public std::runtime_error
    {
    public:
        TextPrinterException(const std::string &msg):
            runtime_error(msg)
        {}
    };
}

#endif // TEXT_PRINTER_H
