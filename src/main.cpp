#include <iostream>

#include "sgl.h"

int main()
{
    sgl::initialize();

    sgl::Window w(1000, 600);

    sgl::Menu menu;
    for (int i = 0; i < 50; i++)
        menu.addItem(gamex::constructMessage("item%d", i));
    menu.setTitle("leeel menu realized :p");

    sgl::Font font("./font/font.ttf", 25);
    sgl::Color color("green");

    sgl::TextPrinter textPrinter(w, color, font);

    std::cout << menu.run(textPrinter, sgl::Menu::RIGHT) << std::endl;
    return 0;
}
