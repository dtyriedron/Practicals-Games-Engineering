#include "cmp_ai_movement.h"

AiMovementComponent::AiMovementComponent(Entity * p) : ActorMovementComponent(p) {}

void AiMovementComponent::setDirection(float & xdirection, float & ydirection)
{
	xdirection = _xdirection;
	ydirection = _ydirection;
}

float AiMovementComponent::getXDirection()
{
	return _xdirection;
}

float AiMovementComponent::getYDirection()
{
	return _ydirection;
}

void AiMovementComponent::update(double dt)
{
	/*
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		_xdirection--;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		_xdirection++;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		_ydirection--;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		_ydirection++;
	}
	move(sf::Vector2f(_xdirection* _speed*dt, _ydirection* _speed*dt));
	*/ //move the ghosts in different directions depending on AI 
}
