#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>

#include "sgl.h"

#include "my_string.h"

#define THROW_ALLEGRO_INITIALIZE_EXCEPTION(fname) \
    throw sgl::AllegroInitializeErrorException(gamex::\
    constructMessage("Fatal Error: %s() returned false", #fname))

void sgl::initializeGraphics()
{
    if (!al_init())
        THROW_ALLEGRO_INITIALIZE_EXCEPTION(al_init);

    if (!al_init_image_addon())
        THROW_ALLEGRO_INITIALIZE_EXCEPTION(al_init_image_addon);

    if (!al_init_primitives_addon())
        THROW_ALLEGRO_INITIALIZE_EXCEPTION(al_init_primitives_addon);

    if (!al_init_font_addon())
        THROW_ALLEGRO_INITIALIZE_EXCEPTION(al_init_font_addon);

    if (!al_init_ttf_addon())
        THROW_ALLEGRO_INITIALIZE_EXCEPTION(al_init_ttf_addon);
}


void sgl::shutdownGraphics()
{
    al_shutdown_font_addon();
    al_shutdown_image_addon();
    al_shutdown_primitives_addon();
    al_shutdown_ttf_addon();
    al_uninstall_keyboard();
    al_uninstall_mouse();
    al_uninstall_system();
}
