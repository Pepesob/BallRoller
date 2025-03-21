
#include "src/Screen.hpp"

int main()
{
    Screen screen;
    // run the program as long as the window is open
    while (screen.isOpen())
    {
        screen.serveWindowEvents();
    }
}
