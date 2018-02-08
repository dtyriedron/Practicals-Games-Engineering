#pragma once
#include "entity.h"

//creates an instance of an entity that relates to the player
class Player : public Entity
{
	private:
		//stores the speed of the entity player
		float _speed;
	
	public:
		//override the update methods dt so that everything is updating at the same time
		void update(double dt) override;
		//call the player class 
		Player();
		//overriding the render methods window so that everything is rendered at the same time
		void render(sf::RenderWindow &window) const override;
};