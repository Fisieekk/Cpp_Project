#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Bird.h"
#include "Pipe.h"
#include <random>
class Game
{
public:
    Game(sf::RenderWindow& window);
    sf::RenderWindow& window;
    void Run();
    sf::SoundBuffer buffer;
    sf::Music music;

private:
    sf::Texture background_texture, ground_texture,game_over_texture;
    sf::Sprite background_sprite, ground_sprite1, ground_sprite2,game_over_sprite;
    sf::Clock clock;
    Bird bird;
    bool first_key_pressed, run_game,monitor;
    const int speed = 300;

    void draw();
    void groundMove(sf::Time&);
    void gameProcces(sf::Time& deltaTime);
    void checkCollision();
    void resetGame();
    void checkScore();
    int pipe_counter, pipe_time,score;
    std::vector<Pipe> pipes;
    std::random_device rd;
    std::uniform_int_distribution<int> dist{ 250, 350 };

    sf::Font arial_font;
    sf::Font flappy_font;
    sf::Text text;
    sf::Text score_text;
    sf::Text start_text;
};

