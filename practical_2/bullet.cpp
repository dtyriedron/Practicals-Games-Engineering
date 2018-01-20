#include "bullet.h"
#include "game.h"
using namespace sf;
using namespace std;

unsigned char Bullet::bulletPointer = '0';
Bullet Bullet::bullets[256];

//create definition for the constructor
Bullet::Bullet(){};

Bullet::Bullet(const sf::Vector2f &pos, const bool mode) : Sprite()
{
	setOrigin(0, 0);
	setPosition(pos);
	setTexture(spritesheet);
	_mode = mode;
	if (mode)
	{
		//set the sprite for the enemy
		setTextureRect(IntRect(32, 32, 32, 32));
	}
	else
	{
		//set the sprite for the player bullet
		setTextureRect(IntRect(64, 32, 32, 32));
	}
}

void Bullet::Update(const float &dt)
{
	//bullet is moved from either an enemy towards the player or the player towards the enemy
	for (auto &b : bullets)
	{
		b.move(0, dt * 200.0f * (b._mode ? 1.0f : -1.0f));
		b._Update(dt);
	}
	
}

void Bullet::Render(sf::RenderWindow &window)
{
	for (auto b : bullets)
	{
		window.draw(b);
	}
}

void Bullet::Fire(const sf::Vector2f &pos, const bool mode)
{
	//pos is fired from the player pos
	bullets[bulletPointer++] = Bullet(pos, mode);
	
}

void Bullet::_Update(const float &dt)
{
	if (getPosition().y < -32 || getPosition().y > gameHeight + 32)
	{
		//off screen
		return;
	}
	else
	{
		move(0, dt * 200.0f * (_mode ? 1.0f : -1.0f));
		const FloatRect boundingBox = getGlobalBounds();

		for (auto s : ships)
		{
			if (!_mode && s == player)
			{
				//players bullets will not collide with player
				continue;
			}
			if (_mode && s != player)
			{
				//invader bullets dont collide with invaders
				continue;
			}
			if (!s->is_exploded() &&
				s->getGlobalBounds().intersects(boundingBox))
			{
				//explode the ship
				s->Explode();
				//wrap the bullet off the screen
				setPosition(-100, -100);
				return;
			}
		}
	}

}
