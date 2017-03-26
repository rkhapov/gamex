#include <allegro5/allegro5.h>

#include "window.h"
#include "image.h"
#include "color.h"

sgl::Window::Window(int width, int height)
{
    al_set_new_display_flags(ALLEGRO_WINDOWED);
    _cursor = nullptr;

    _display = al_create_display(width, height);

    if (_display == nullptr)
        throw WindowErrorException("Cann\'t create display: al_create_display() returned NULL");
}

sgl::Window::~Window()
{
    al_destroy_display(_display);
    al_destroy_mouse_cursor(_cursor);
}


int sgl::Window::getHeight() const
{
    if (_display == nullptr)
        throw WindowErrorException("getHeight() for Window with _display == nullptr");

    return al_get_display_height(_display);
}

int sgl::Window::getWidth() const
{
    if (_display == nullptr)
        throw WindowErrorException("getWidth() for Window with _display == nullptr");

    return al_get_display_width(_display);
}

void sgl::Window::resize(int width, int height)
{
    if (_display == nullptr)
        throw WindowErrorException("resize() for Window with _display == nullptr");

    al_resize_display(_display, width, height);
}

void sgl::Window::setPosition(int x, int y)
{
    if (_display == nullptr)
        throw WindowErrorException("setPosition() for Window with _display == nullptr");

    al_set_window_position(_display, x, y);
}

void sgl::Window::setTitle(const std::string &title)
{
    if (_display == nullptr)
        throw WindowErrorException("setTitle() for Window with _display == nullptr");

    al_set_window_title(_display, title.c_str());
}

void sgl::Window::setIcon(Image &image)
{
    if (_display == nullptr)
        throw WindowErrorException("setIcon() for Window with _display == nullptr");

    al_set_display_icon(_display, image);
}

void sgl::Window::setCursor(Image &image, int xfocus, int yfocus)
{
    if (_display == nullptr)
        throw WindowErrorException("setCursor() for Window with _display == nullptr");

    al_destroy_mouse_cursor(_cursor);

    _cursor = al_create_mouse_cursor(image, xfocus, yfocus);

    al_set_mouse_cursor(_display, _cursor);
}

void sgl::Window::showCursor()
{
    if (_display == nullptr)
        throw WindowErrorException("showCursor() for Window with _display == nullptr");

    al_show_mouse_cursor(_display);
}

void sgl::Window::hideCursor()
{
    if (_display == nullptr)
        throw WindowErrorException("hideCursor() for Window with _display == nullptr");

    al_hide_mouse_cursor(_display);
}

void sgl::Window::clear(Color color)
{
    if (_display == nullptr)
        throw WindowErrorException("clear() for Window with _display == nullptr");

    makeTarget();

    al_clear_to_color(color);
}

void sgl::Window::makeTarget()
{
    if (_display == nullptr)
        throw WindowErrorException("makeTarget() for Window with _display == nullptr");

    al_set_target_backbuffer(_display);
}

void sgl::Window::flip()
{
    if (_display == nullptr)
        throw WindowErrorException("flip() for Window with _display == nullptr");

    makeTarget();

    al_flip_display();
}

sgl::Window::operator const ALLEGRO_DISPLAY *() const
{
    return _display;
}

sgl::Window::operator ALLEGRO_DISPLAY *()
{
    return _display;
}

sgl::Image sgl::Window::getBackBufferImage() const
{
    if (_display == nullptr)
        throw WindowErrorException("getWindowBackBuffer() for Window with _display == nullptr");

    return Image(al_get_backbuffer(_display));
}
