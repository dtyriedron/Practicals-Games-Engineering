#pragma once
#include <SFML/Graphics.hpp>

class Bullet : public sf::Sprite
{
	public:
		//updates all the bullets
		static void Update(const float &dt);
		//renders all the bullets
		static void Render(sf::RenderWindow &window);
		//choose an inactive bullet an use it
		static void Fire(const sf::Vector2f & pos, const bool mode);

		Bullet(const sf::Vector2f &pos, const bool mode);

		~Bullet() = default;
	protected:
		static unsigned char bulletPointer;
		static Bullet bullets[256];
		//Called by the static update()
		void _Update(const float &dt);
		//never called by our code
		 Bullet();
		 //false = player bullet, true = enemy bullet
		 bool _mode;
};