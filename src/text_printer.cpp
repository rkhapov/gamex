#include "text_printer.h"

sgl::TextPrinter::TextPrinter()
{
    _color        = nullptr;
    _font         = nullptr;
    _targetWindow = nullptr;
}

sgl::TextPrinter::TextPrinter(Window &window, const Color &color,
                              const Font &font)
{
    _color        = nullptr;
    _font         = nullptr;
    _targetWindow = nullptr;
    setColor(color);
    setFont(font);
    setTargetWindow(window);
}

sgl::TextPrinter::TextPrinter(const TextPrinter &textPrinter)
{
    _color        = nullptr;
    _font         = nullptr;
    _targetWindow = nullptr;
    setColor(textPrinter.getColor());
    setFont(textPrinter.getFont());
    setTargetWindow(textPrinter.getTargetWindow());
}

sgl::TextPrinter::~TextPrinter()
{
    delete _color;
    delete _font;
    _color = nullptr;
    _font = nullptr;
}

void sgl::TextPrinter::setColor(const Color &color)
{
    delete _color;
    _color = new Color(color);
}

void sgl::TextPrinter::setFont(const Font &font)
{
    delete _font;
    _font = new Font(font);
}


void sgl::TextPrinter::setTargetWindow(Window &window)
{
    _targetWindow = &window;
}


const sgl::Color& sgl::TextPrinter::getColor() const
{
    return *_color;
}

const sgl::Font& sgl::TextPrinter::getFont() const
{
    return *_font;
}

sgl::Window& sgl::TextPrinter::getTargetWindow() const
{
    return *_targetWindow;
}

void sgl::TextPrinter::drawText(const std::string &text, float x,
                                float y, int flags) const
{
    if (_color == nullptr)
        throw TextPrinterException("No color for TextPrinter");

    if (_font == nullptr)
        throw TextPrinterException("No font fot TextPrinter");

    if (_targetWindow == nullptr)
        throw TextPrinterException("No target window for TextPrinter");

    _font->drawText(*_targetWindow, *_color, text, x, y, flags);
}

sgl::TextPrinter& sgl::TextPrinter::operator =(const TextPrinter &textPrinter)
{
    if (this == &textPrinter)
        return *this;
    setColor(textPrinter.getColor());
    setFont(textPrinter.getFont());
    setTargetWindow(textPrinter.getTargetWindow());
    return *this;
}
