#include "cmp_actor_movement.h"
#include "cmp_sprite.h"
#include "system_renderer.h"
#include "levelsystem.h"

using namespace sf;

bool ActorMovementComponent::validMove(const sf::Vector2f & pos)
{
	return (LevelSystem::getTileAt(pos) != LevelSystem::WALL);
}

ActorMovementComponent::ActorMovementComponent(Entity * p) : _speed(100.0f), Component(p) {}

float ActorMovementComponent::getSpeed() const
{
	return _speed;
}

void ActorMovementComponent::setSpeed(float &speed)
{
	_speed = speed;
}

void ActorMovementComponent::move(const sf::Vector2f & p)
{
	auto pp = _parent->getPosition() + p;
	if (validMove(pp))
	{
		_parent->setPosition(pp);
	}
}

void ActorMovementComponent::move(float &x, float &y)
{
	move(Vector2f(x, y));
}

void ActorMovementComponent::update(double dt)
{
}
