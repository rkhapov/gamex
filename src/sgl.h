#ifndef GRAPHICS_H
#define GRAPHICS_H

/*
 * graphics.h - allegro graphics wrappers and other graphic classes
*/

#include <stdexcept>

#include "window.h"
#include "image.h"
#include "color.h"
#include "font.h"

namespace sgl
{

    class AllegroInitializeErrorException: public std::runtime_error
    {
    public:
        AllegroInitializeErrorException(const std::string &msg):
            runtime_error(msg)
        {}
    };

    void initializeGraphics();
    void shutdownGraphics();
}

#endif // GRAPHICS_H
