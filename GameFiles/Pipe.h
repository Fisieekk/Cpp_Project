#pragma once

#include <SFML/Graphics.hpp>

class Pipe
{
public:
    Pipe(int gapY);
    sf::Sprite pipe_sprite_up, pipe_sprite_down;
    static void loadTextures();
    void update(sf::Time& deltaTime);
    float rightBound();

private:
    static sf::Texture pipe_texture_up, pipe_texture_down;
    static int pipe_distance, move_speed;
};
