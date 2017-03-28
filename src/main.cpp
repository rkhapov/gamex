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

    std::cout << menu.run(sgl::TextPrinter(w, color, font)) << std::endl;
    return 0;
}
