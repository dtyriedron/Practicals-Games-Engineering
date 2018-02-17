#include "cmp_enemy_ai.h"
#include "maths.h"
#include "ecm.h"
#include "levelsystem.h"
#include <iostream>

using namespace sf;
static const Vector2i directions[] =  {{1,0}, {0,1}, {0,-1}, {-1,0} };

EnemyAIComponent::EnemyAIComponent(Entity * p) : ActorMovementComponent(p)
{
	_speed = 100.f;
	_direction = Vector2f(directions[rand() % 4]);
	_state = ROAMING;
}

void EnemyAIComponent::update(double dt)
{
	//amount to move
	const auto mva = (float)(dt* _speed);
	//Current position
	const Vector2f pos = _parent->getPosition();
	//next position
	const Vector2f newpos = pos + _direction * mva;
	//inverse of our current direction
	const Vector2i baddir = -1 * Vector2i(_direction);
	//random new direction
	Vector2i newdir = directions[(rand() % 4)];

	switch (_state)
	{
		
	case ROAMING:
		//std::cout << "hey";
		if(LevelSystem::getTileAt(newpos) == LevelSystem::WALL || LevelSystem::getTileAt(pos) == LevelSystem::WAYPOINT)
		{
			_state = ROTATING;
		}
		else
		{
			move(mva*_direction);
		}
		break;
	case ROTATING:
		while (newdir == baddir && LevelSystem::getTileAt(newpos) == LevelSystem::WALL)
		{
			newdir = directions[rand() % 4];
		}
		_direction = Vector2f(newdir);
		_state = ROTATED;
		break;
	case ROTATED:
		if (LevelSystem::getTileAt(newpos) != LevelSystem::WAYPOINT)
		{
			_state = ROAMING;
		}
		move(_direction * mva);
		break;
	}
	ActorMovementComponent::update(dt);
}