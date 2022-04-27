#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "Application.hpp"

int main()
{
    Application app;
    app.MainLoop();

    SlotRow row = SlotRow::NewRandom(5);
    
    float pos = 0.0f;
    while (pos <= 1.0f) {
        // std::printf("%.4f: %d\n", pos, row.IndexFromPosition(pos));
        pos += 0.005f;
    }

    return 0;
}
