#include "engine.h"

int main()
{
    Game ruffini(600, 400);

    while(ruffini.isOpen())
    {
        ruffini.handleEvent();
        ruffini.update();
        ruffini.render();
    }
    return 0;
}
