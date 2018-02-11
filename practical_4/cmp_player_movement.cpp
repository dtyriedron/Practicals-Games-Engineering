#include "cmp_player_movement.h"
#include <iostream>

PlayerMovementComponent::PlayerMovementComponent(Entity * p) : ActorMovementComponent(p) {
	_speed = 100.f;
}

/*std::vector<std::shared_ptr<sf::Keyboard>> PlayerMovementComponent::getKeys()
{
	return _controls[4];
}

void PlayerMovementComponent::setKeys(std::vector<std::shared_ptr<sf::Keyboard::Key>> controls[])
{
	controls[] =
	{
		sf::Keyboard::W, //player up
		sf::Keyboard::S, //player down
		sf::Keyboard::A, //player left
		sf::Keyboard::D //player right
	};
}*/

//void PlayerMovementComponent::validKey()
//{
	//checks if the key being used is in the controls list
	//std::make_shared<sf::Keyboard>();
	//if (_controls)
	//{
	//	_parent->getPosition += p;
	//}
//}

void PlayerMovementComponent::setDirection(float &xdirection, float &ydirection)
{
	xdirection = _xdirection;
	ydirection = _ydirection;
}

float PlayerMovementComponent::getXDirection()
{
	return _xdirection;
}

float PlayerMovementComponent::getYDirection()
{
	return _ydirection;
}

void PlayerMovementComponent::update(double dt)
{
	//updates the pos depending on the key being used
	//_parent->getPosition(_parent->setPostion())
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		move(sf::Vector2f(-_speed*dt,0));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		move(sf::Vector2f(_speed * dt,0));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		move(sf::Vector2f(0, _speed * dt));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		move(sf::Vector2f(0, -_speed * dt));
	}


}
