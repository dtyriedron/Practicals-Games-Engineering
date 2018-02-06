#include "player.h"
#include <iostream>

using namespace sf;
using namespace std;

const Keyboard::Key controls[4] =
{
	Keyboard::W, //player up
	Keyboard::S, //player down
	Keyboard::A, //player left
	Keyboard::D, //player right
};

void Player::update(double dt)
{
	float xdirection = 0.0f;
	float ydirection = 0.0f;

	//move in for directions based on keys
	if(Keyboard::isKeyPressed(controls[0]))
	{
		ydirection--;
		cout << "up key pressed" << std::endl;
	}
	if(Keyboard::isKeyPressed(controls[1]))
	{
		ydirection++;
		cout << "down key pressed" << std::endl;
	}
	if(Keyboard::isKeyPressed(controls[2]))
	{
		xdirection--;
		cout << "left key pressed" << std::endl;
	}
	if(Keyboard::isKeyPressed(controls[3]))
	{
		xdirection++;
		cout << "right key pressed" << std::endl;
	}

	//move the player
	move(Vector2f(xdirection*_speed*dt, ydirection*_speed*dt));
	
	//update the pos of the player
	Entity::update(dt);
}

//player constructor setting default values for every new player made of speed: 200 and a circle shape
Player::Player() : _speed(200.0f), Entity(make_unique<CircleShape>(25.f))
{
	//set the shape settings
	_shape->setFillColor(Color::Magenta);
	_shape->setOrigin(Vector2f(25.f, 25.f));
}

//render the player's drawings
void Player::render(sf::RenderWindow &window) const
{
	//draw the player shape which is taken from entity that was set in the player's constructor
	window.draw(*_shape);
}