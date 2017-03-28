#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include "window.h"
#include "color.h"
#include "font.h"
#include "my_string.h"

const int sgl::Font::ALIGN_CENTRE = ALLEGRO_ALIGN_CENTRE;
const int sgl::Font::ALIGN_CENTER = ALLEGRO_ALIGN_CENTER;
const int sgl::Font::ALIGN_LEFT   = ALLEGRO_ALIGN_LEFT;
const int sgl::Font::ALIGN_RIGHT  = ALLEGRO_ALIGN_RIGHT;

void sgl::Font::_copyFrom(const Font &font)
{
    if (_font != nullptr)
    {
        al_destroy_font(_font);
    }

    _path = font._path;
    _openSize = font._openSize;

    _font = al_load_font(_path.c_str(), _openSize, 0);

    if (_font == nullptr)
    {
        std::string msg = gamex::constructMessage("Cann't load font \"%s\": %s", _path.c_str(),
                                                   std::strerror(al_get_errno()));

        throw FontErrorException(msg);
    }
}

sgl::Font::Font(const std::string &path, int size)
{
    _font = al_load_font(path.c_str(), size, 0);
    _path = path;
    _openSize = size;

    if (_font == nullptr)
    {
        std::string msg = gamex::constructMessage("Cann't load font \"%s\": %s", path.c_str(),
                                                   std::strerror(al_get_errno()));

        throw FontErrorException(msg);
    }
}

sgl::Font::Font(const Font &font)
{
    _font = nullptr;
    _copyFrom(font);
}

sgl::Font::~Font()
{
    al_destroy_font(_font);
    _font = nullptr;
}


int sgl::Font::getLineHeight() const
{
    if (_font == nullptr)
        throw FontErrorException("getLineHeight() for Font with _font == nullptr");

    return al_get_font_line_height(_font);
}

int sgl::Font::getAscent() const
{
    if (_font == nullptr)
        throw FontErrorException("getAscent() fot Font with _font == nullptr");

    return al_get_font_ascent(_font);
}

int sgl::Font::getDescent() const
{
    if (_font == nullptr)
        throw FontErrorException("getDescent() for Font woth _font == nullptr");

    return al_get_font_descent(_font);
}


void sgl::Font::drawText(Window &window, const Color &color,
                             const std::string &text, float x, float y, int flags) const
{
    window.makeTarget();

    al_draw_text(_font, color, x, y, flags, text.c_str());
}


sgl::Font::operator ALLEGRO_FONT *()
{
    return _font;
}

sgl::Font::operator const ALLEGRO_FONT*() const
{
    return _font;
}

const std::string sgl::Font::path() const
{
    return _path;
}

sgl::Font& sgl::Font::operator = (const Font &font)
{
    if (this == &font)
        return *this;

    _copyFrom(font);
    return *this;
}
