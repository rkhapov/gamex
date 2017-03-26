#include <allegro5/allegro5.h>

#include "image.h"
#include "window.h"
#include "my_string.h"

const int sgl::Image::FLIP_HORIZONTAL = ALLEGRO_FLIP_HORIZONTAL;
const int sgl::Image::FLIP_VERTICAL   = ALLEGRO_FLIP_VERTICAL;

void sgl::Image::Image::_copyFrom(const Image &image)
{
    if (_bitmap != nullptr)
        al_destroy_bitmap(_bitmap);

    _bitmap = al_clone_bitmap(image._bitmap);

    if (_bitmap == nullptr)
        throw ImageErrorException("Cann't clone image: al_clone_bitmap() returned NULL");
}

sgl::Image::Image()
{
    _bitmap = nullptr;
}

sgl::Image::Image(const std::string &path)
{
    _bitmap = al_load_bitmap(path.c_str());

    if (_bitmap == nullptr)
    {
        std::string msg = gamex::constructMessage("Cann't load image \"%s\": %s", path.c_str(),
                                                   std::strerror(al_get_errno()));

        throw ImageErrorException(msg);
    }
}

sgl::Image::Image(const Image &image)
{
    _bitmap = nullptr;

    _copyFrom(image);
}

sgl::Image::Image(ALLEGRO_BITMAP *bitmap)
{
    _bitmap = al_clone_bitmap(bitmap);

    if (_bitmap == nullptr)
        throw ImageErrorException("Constructor: bitmap == NULL");
}

sgl::Image::~Image()
{
    if (_bitmap != nullptr)
        al_destroy_bitmap(_bitmap);
}


void sgl::Image::draw(Window &window, float destx, float desty, int flags) const
{
    window.makeTarget();

    if (_bitmap == nullptr)
        throw ImageErrorException("Attempt to draw image with _bitmap == nullptr");

    al_draw_bitmap(_bitmap, destx, desty, flags);
}



void sgl::Image::draw(Window &window, float destx, float desty, float srcx,
                          float srcy, float width, float height, int flags) const
{
    window.makeTarget();

    if (_bitmap == nullptr)
        throw ImageErrorException("Attempt to draw image with _bitmap == nullptr");

    al_draw_bitmap_region(_bitmap, srcx, srcy, width, height, destx, desty, flags);
}


void sgl::Image::drawRotated(Window &window, float destx, float desty,
                          float centerx, float centery, float angle, int flags) const
{
    window.makeTarget();

    if (_bitmap == nullptr)
        throw ImageErrorException("Attempt to draw image with _bitmap == nullptr");

    al_draw_rotated_bitmap(_bitmap, centerx, centery, destx, desty, angle, flags);
}


void sgl::Image::drawScaled(Window &window, float srcx, float scry, float scrw,
                                float srch, float destx, float desty,
                                float destw, float desth, int flags) const
{
    window.makeTarget();

    if (_bitmap == nullptr)
        throw ImageErrorException("Attempt to draw image with _bitmap == nullptr");

    al_draw_scaled_bitmap(_bitmap, srcx, scry, scrw, srch, destx, desty,
                          destw, desth, flags);
}


int sgl::Image::getHeight() const
{
    if (_bitmap == nullptr)
        throw ImageErrorException("Attempt to get height from image with _bitmap == nullptr");

    return al_get_bitmap_height(_bitmap);
}

int sgl::Image::getWidth() const
{
    if (_bitmap == nullptr)
        throw ImageErrorException("Attempt to get width from image with _bitmap == nullptr");

    return al_get_bitmap_width(_bitmap);
}

sgl::Image sgl::Image::getSubImage(int startx, int starty,
                                           int width, int height) const
{
    ALLEGRO_BITMAP *clone = al_create_sub_bitmap(_bitmap, startx, starty,
                                                 width, height);

    if (clone == nullptr)
        throw ImageErrorException("getSubImage failed: al_create_sub_bitmap() returned NULL");

    return clone;
}

sgl::Image::operator ALLEGRO_BITMAP*()
{
    return _bitmap;
}

sgl::Image::operator const ALLEGRO_BITMAP*() const
{
    return _bitmap;
}

sgl::Image &sgl::Image::operator =(const Image &image)
{
    if (this == &image)
        return *this;

    _copyFrom(image);
    return *this;
}
