#include "Game.h"
#include "Config.h"
#include <iostream>
#include <windows.h>

Game::Game(sf::RenderWindow& window) :
    window(window),
    first_key_pressed(false),
    run_game(true),
    pipe_counter(100),
    pipe_time(70),
    score(0)
{
    background_texture.loadFromFile("GameFiles/assets/Background.jpg");
    background_sprite.setTexture(background_texture);
    background_sprite.setScale(
        static_cast<float>(MAX_WIDTH) / background_texture.getSize().x,
        static_cast<float>(MAX_HEIGHT) / background_texture.getSize().y
    );

    ground_texture.loadFromFile("GameFiles/assets/Ground.jpg");
    ground_sprite1.setTexture(ground_texture);
    ground_sprite2.setTexture(ground_texture);
    float ground_scale_x = static_cast<float>(MAX_WIDTH) / ground_texture.getSize().x;
    float ground_scale_y = static_cast<float>(150) / ground_texture.getSize().y; // 150 is the height we want for the ground
    ground_sprite1.setScale(ground_scale_x, ground_scale_y);
    ground_sprite2.setScale(ground_scale_x, ground_scale_y);
    ground_sprite1.setPosition(0, MAX_HEIGHT - 150);
    ground_sprite2.setPosition(MAX_WIDTH, MAX_HEIGHT - 150);

    game_over_texture.loadFromFile("GameFiles/assets/GameOver.png");
    game_over_sprite.setTexture(game_over_texture);
    game_over_sprite.setPosition(MAX_WIDTH / 2 - game_over_texture.getSize().x / 2, MAX_HEIGHT / 3 - game_over_texture.getSize().y / 2);
    //width of game over sprite
    float game_over_sprite_width = game_over_texture.getSize().x;

    arial_font.loadFromFile("GameFiles/assets/ARIAL.ttf"); 
    flappy_font.loadFromFile("GameFiles/assets/FlappyFont.ttf");
    text.setFont(flappy_font);
    text.setCharacterSize(50);
    text.setPosition(MAX_WIDTH / 2.5, MAX_HEIGHT / 2 - 50);
    text.setString("Press Space to start");
    text.setOutlineColor(sf::Color::Black);
    text.setOutlineThickness(2);

    start_text.setFont(flappy_font);
    start_text.setCharacterSize(50);
    start_text.setPosition(MAX_WIDTH / 3.5, MAX_HEIGHT / 2 - 50);
    start_text.setString("Welcome to Totally legal copy of Flappybird \n Press Space to start \n\n by Marcin Serafin");
    start_text.setOutlineColor(sf::Color::Black);
    start_text.setOutlineThickness(2);

    score_text.setFont(flappy_font);
    score_text.setCharacterSize(50);
    score_text.setPosition(MAX_WIDTH / 2.5, 0);
    score_text.setString("Score: "+ std::to_string(score));
    score_text.setOutlineColor(sf::Color::Black);
    score_text.setOutlineThickness(2);



    buffer.loadFromFile("GameFiles/assets/Flap.mp3");
    if(!music.openFromFile("GameFiles/assets/music.mp3"))
	{
        std::cout << "Error" << std::endl;
	}

    window.setFramerateLimit(60);

    Pipe::loadTextures();
}

void Game::Run()
{
    sf::Clock clock;
    sf::Sound sound;
    sound.setBuffer(buffer);
    sound.setVolume(100.f);
    music.setVolume(30.f);
    while (window.isOpen()) {
        sf::Time deltaTime = clock.restart();
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed && run_game) {
                if (event.key.code == sf::Keyboard::Space && !first_key_pressed) {
                    first_key_pressed = true;
                    music.play();
                    bird.setIsFlapping(true);
                }
                if (event.key.code == sf::Keyboard::Space && first_key_pressed) {
                    bird.flap(deltaTime);
                    sound.play();
                }
            }
            if (event.key.code == sf::Keyboard::Space && !run_game) {
                resetGame();
   			}
        }
        draw();
        gameProcces(deltaTime);
        window.display();
    }
}

void Game::draw()
{

    window.draw(background_sprite);
    for (auto& pipe : pipes) {
        window.draw(pipe.pipe_sprite_up);
        window.draw(pipe.pipe_sprite_down);
    }
    window.draw(ground_sprite1);
    window.draw(ground_sprite2);
    window.draw(bird.bird_sprite);
    window.draw(score_text);

    if (!first_key_pressed && run_game) {
        window.draw(start_text);
    }

    if (!run_game) {
        window.draw(text);
        window.draw(game_over_sprite);
    }
}

void Game::groundMove(sf::Time& time)
{
    ground_sprite1.move(-speed * time.asSeconds(), 0);
    ground_sprite2.move(-speed * time.asSeconds(), 0);

    if (ground_sprite1.getPosition().x + ground_texture.getSize().x * ground_sprite1.getScale().x < 0) {
        ground_sprite1.setPosition(ground_sprite2.getPosition().x + ground_texture.getSize().x * ground_sprite2.getScale().x, MAX_HEIGHT - 150);
    }
    if (ground_sprite2.getPosition().x + ground_texture.getSize().x * ground_sprite2.getScale().x < 0) {
        ground_sprite2.setPosition(ground_sprite1.getPosition().x + ground_texture.getSize().x * ground_sprite1.getScale().x, MAX_HEIGHT - 150);
    }
}

void Game::gameProcces(sf::Time& deltaTime)
{
    if (first_key_pressed) {
        groundMove(deltaTime);

        if (pipe_counter > pipe_time) {
            int gapY = dist(rd);
            pipes.push_back(Pipe(gapY));
            pipe_counter = 0;
        }
        pipe_counter++;

        for (auto& pipe : pipes) {
            pipe.update(deltaTime);
            if (pipe.rightBound() < 0) {
                pipes.erase(pipes.begin());
            }
        }
        checkScore();
        checkCollision();
    }

    bird.update(deltaTime);
}

void Game::checkCollision()
{
    if (pipes.size() > 0) {
        if (pipes[0].pipe_sprite_up.getGlobalBounds().intersects(bird.bird_sprite.getGlobalBounds()) ||
            pipes[0].pipe_sprite_down.getGlobalBounds().intersects(bird.bird_sprite.getGlobalBounds()))
        {
            music.stop();
            first_key_pressed = false;
			run_game = false;
		}
    }
    if (bird.bird_sprite.getPosition().y + BIRD_HEIGHT > MAX_HEIGHT - GROUND_HEIGHT / 3) {
        music.stop();
		first_key_pressed = false;
		run_game = false;
	}
}

void Game::resetGame()
{
    bird.resetPosition();
    bird.setIsFlapping(false);
    run_game = true;
    first_key_pressed = true;
    music.play();
    bird.setIsFlapping(true);
    pipe_counter = 100;
    pipes.clear();
    score = 0;
    score_text.setString("Score: " + std::to_string(score));
}

void Game::checkScore()
{
    
    if (pipes.size() > 0)
    {
        if (!monitor)
        {
            if (bird.bird_sprite.getGlobalBounds().left > pipes[0].pipe_sprite_down.getGlobalBounds().left &&
                bird.rightBound() < pipes[0].rightBound())
            {
                monitor = true;
            }
        }
        else
        {
            if (bird.bird_sprite.getGlobalBounds().left > pipes[0].rightBound())
            {
                score++;
                std:: cout << score << std::endl;
                score_text.setString("Score: " + std::to_string(score));
                monitor = false;
            }
        }
    }
}


