#include "Pipe.h"
#include "Config.h"

Pipe::Pipe(int gapY)
{
    pipe_sprite_up.setTexture(pipe_texture_up);
    pipe_sprite_down.setTexture(pipe_texture_down);

    float pipeScaleX = static_cast<float>(PIPE_WIDTH) / pipe_texture_up.getSize().x;
    float pipeScaleY = static_cast<float>(PIPE_HEIGHT) / pipe_texture_up.getSize().y;
    pipe_sprite_up.setScale(pipeScaleX, pipeScaleY);
    pipe_sprite_down.setScale(pipeScaleX, pipeScaleY);

    pipe_sprite_up.setPosition(MAX_WIDTH, 0);  // Position top pipe to touch the top of the screen
    pipe_sprite_down.setPosition(MAX_WIDTH, gapY + pipe_distance);  // Position bottom pipe to touch the gap and ground
}

void Pipe::loadTextures()
{
    pipe_texture_up.loadFromFile("GameFiles/assets/Pipe.jpg");
    pipe_texture_down.loadFromFile("GameFiles/assets/Pipe.jpg");
}

void Pipe::update(sf::Time& deltaTime)
{
    pipe_sprite_up.move(-move_speed * deltaTime.asSeconds(), 0.f);
    pipe_sprite_down.move(-move_speed * deltaTime.asSeconds(), 0.f);
}

float Pipe::rightBound()
{
    return pipe_sprite_up.getPosition().x + pipe_sprite_up.getGlobalBounds().width;
}

sf::Texture Pipe::pipe_texture_up, Pipe::pipe_texture_down;
int Pipe::pipe_distance = 250;
int Pipe::move_speed = 400;
