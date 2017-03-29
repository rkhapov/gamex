#include <iostream>

#include "sgl.h"

int main()
{
    sgl::initialize();

    sgl::Window w(400, 500);

    sgl::Menu menu;
    menu.addItem("item1");
    menu.addItem("item2");
    menu.addItem("item3");
    menu.addItem("item4");

    sgl::Font font("./font/font.ttf", 15);
    sgl::Color color("green");

    sgl::TextPrinter textPrinter(w, color, font);

    std::cout << menu.run(textPrinter) << std::endl;
    return 0;
}
