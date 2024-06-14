#pragma once

#include <SFML/Graphics.hpp>

class Bird
{
	private:
		sf::Texture bird_textures[3];
		const float gravity=10.f;
		const float flap_force=250.f;
		float y_velocity;
		int counter, texture_num;
		bool is_flapping;
	public:
		sf::Sprite bird_sprite;
		Bird();
		void setIsFlapping(bool is_flapping);
		void flap(sf::Time& deltaTime);
		void resetPosition();
		void update(sf::Time & deltaTime);
		float rightBound();
};