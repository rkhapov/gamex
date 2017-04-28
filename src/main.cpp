#include "sgl.h"

using namespace sgl;

int main()
{
    initialize();
    Window w(400, 500);
    Animation a(".");

    while (true)
    {
        w.clear(Color("black"));
        a.getCurrentFrame().draw(w, 0, 0);
        w.flip();
        delay(1);
        a.goNextFrame();
    }
    return 0;
}
