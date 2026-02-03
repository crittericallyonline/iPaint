

#include <iostream>

#include "Display.hpp"
#include "Network.hpp"

#if defined(WIN32)

#endif

int main()
{
    srand(time(0));
    Network.Connect();
    Display.Create(800, 600, "WebITG (Connecting)");

    return 0;
}
