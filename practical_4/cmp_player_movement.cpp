#include "cmp_player_movement.h"

PlayerMovementComponent::PlayerMovementComponent(ActorMovementComponent * p)
{

}

void PlayerMovementComponent::getKey()
{
	//finds the control for pos1
	_controls->at(1);
}

void PlayerMovementComponent::setKey()
{
	//inserts the keys into the controls list
	auto left = _controls->insert->A;
	auto right = _controls->insert->D;
	auto up = _controls->insert->W;
	auto down = _controls->insert->S;
}

void PlayerMovementComponent::validKey()
{
	//checks if the key being used is in the controls list
	std::make_shared<sf::Keyboard>();
	if (_controls)
	{
		_parent->getPosition += p;
	}
}

void PlayerMovementComponent::update(double dt)
{
	//updates the pos depending on the key being used
	//_parent->getPosition(_parent->setPostion())
}
