

#include <iostream>

#include "Network.hpp"
#include "Display.hpp"

int main()
{
    Network.Connect();
    Display.Create(800, 600, "iPaint");
    return 0;
}
