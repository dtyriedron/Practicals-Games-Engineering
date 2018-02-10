#include "ecm.h"
using namespace std;
using namespace sf;

Entity::Entity()
{
}

void Entity::render()
{
	for (auto &_c : _components)
	{
		_c->render();
	}
}

const sf::Vector2f & Entity::getPosition() const
{
	return _position;
}

//sets the pos of the entity
void Entity::setPostion(const sf::Vector2f & pos)
{
	_position = pos;
}

bool Entity::is_fordeletion() const
{
	return _fordeletion;
}

float Entity::getRotation() const
{
	return _rotation;
}

void Entity::setRotation(float &rot)
{
	_rotation = rot;
}

bool Entity::isAlive() const
{
	return _alive;
}

void Entity::setAlive(bool & alive)
{
	_alive = alive;
}


void Entity::setfordelete(bool & del)
{
	_fordeletion = del;
}

bool Entity::isVisable() const
{
	return _visable;
}

void Entity::setVisable(bool & vis)
{
	_visable = vis;
}

void Entity::update(double dt)
{
	for (auto &_c : _components)
	{
		_c->update(dt);
	}
}

void EntityManager::update(double dt)
{
	for (auto _e : list)
	{
		_e->update(dt);
	}
}

void EntityManager::render(sf::RenderWindow & window)
{
	for (auto &_e : list)
	{
		_e->render();
	}
}

Component::Component(Entity *p)
{
	_parent = p;
}

bool Component::is_fordeletion() const
{
	return _fordeletion;
}

Component::~Component()
{}
