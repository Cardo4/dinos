#include "SFML-2.5.1/include/SFML/Graphics.hpp"
#include "SFML-2.5.1/include/SFML/Audio.hpp"

#include <iostream>
#include <time.h>

using namespace sf;
using namespace std;

#include "headers/game1.h"

int main()
{
    srand(time(NULL));

    Game1 dinos({1280,600},"Dinooos");


    return EXIT_SUCCESS;
}
