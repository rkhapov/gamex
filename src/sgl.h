#ifndef SGL_H
#define SGL_H

/*
 * sgl.h - allegro graphics wrappers and other graphics classes
*/

#include <stdexcept>

#include "window.h"
#include "image.h"
#include "color.h"
#include "font.h"
#include "timer.h"
#include "event_manager.h"
#include "menu.h"
#include "animation.h"

namespace sgl
{

    class AllegroInitializeErrorException: public std::runtime_error
    {
    public:
        AllegroInitializeErrorException(const std::string &msg):
            runtime_error(msg)
        {}
    };

    void initialize();
    void shutdown();

    void delay(double seconds);
}

#endif // SGL_H

