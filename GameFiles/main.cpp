#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Config.h"
#include "Game.h"
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode(MAX_WIDTH, MAX_HEIGHT), "FLAP LOSER");
    Game game(window);
    game.Run();
    return 0;
}