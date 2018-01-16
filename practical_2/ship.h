#pragma once
#include <SFML/Graphics.hpp>

class Ship : public sf::Sprite
{
	protected:
	sf::IntRect _sprite;
	Ship();
	public:
	
	explicit Ship(sf::IntRect ir);
	
	virtual ~Ship() = 0;
	
	virtual void Update(const float &dt);
	
};

//create Invader class that inherits from ship class
class Invader : public Ship
{
	public:
		static bool direction;
		static float speed;
		Invader(sf::IntRect ir, sf::Vector2f pos);
		Invader();
		void Update(const float &dt) override;
};