#include "Bird.h"
#include "Config.h"
#include <iostream>

Bird::Bird() :
    counter(0),
    texture_num(1),
    is_flapping(false),
    y_velocity(0)
{
    bird_textures[0].loadFromFile("GameFiles/assets/bird1.png");
    bird_textures[1].loadFromFile("GameFiles/assets/bird2.png");
    bird_textures[2].loadFromFile("GameFiles/assets/bird3.png");
    bird_sprite.setTexture(bird_textures[0]);
    bird_sprite.setScale(1.f, 1.f);  // Adjust if scaling is needed
    resetPosition();
}

void Bird::setIsFlapping(bool is_flapping)
{
    this->is_flapping = is_flapping;
}

void Bird::flap(sf::Time& deltaTime)
{
    y_velocity = -flap_force;  // Apply the flap force directly
}

void Bird::resetPosition()
{
    bird_sprite.setPosition(100, 100);
    y_velocity = 0;
}

void Bird::update(sf::Time& deltaTime)
{
    if (is_flapping) {
        if (counter == 5) {
            bird_sprite.setTexture(bird_textures[texture_num]);
            texture_num = (texture_num + 1) % 3;
            counter = 0;
        }
        counter++;

        y_velocity += gravity;  // Apply gravity constantly
        bird_sprite.move(0, y_velocity * deltaTime.asSeconds());

        // Prevent the bird from falling below the ground
        if (bird_sprite.getPosition().y + BIRD_HEIGHT > MAX_HEIGHT - GROUND_HEIGHT / 4) {
            bird_sprite.setPosition(100, MAX_HEIGHT - GROUND_HEIGHT / 4 - BIRD_HEIGHT);
            y_velocity = 0;  // Stop the bird's movement
        }

        // Prevent the bird from flying out of the top of the screen
        if (bird_sprite.getPosition().y < 0) {
            bird_sprite.setPosition(100, 0);
            y_velocity = 0;
        }
    }
}

float Bird::rightBound()
{
    return bird_sprite.getGlobalBounds().left + bird_sprite.getGlobalBounds().width;
}
