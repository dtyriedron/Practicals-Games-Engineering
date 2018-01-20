#include <SFML/Graphics.hpp>
#include <iostream>
#include "ship.h"
#include "game.h"
#include "bullet.h"


using namespace sf;
using namespace std;

sf::Texture spritesheet;
sf::Sprite invader;

//add an instance of a ship
vector<Ship *> ships;
Player *player;


void Load()
{
	if(!spritesheet.loadFromFile("res/img/invaders_sheet.png"))
	{
		cerr << "Failed to load spritesheet!" << std::endl;
	}

	float x = 17;
	float y = 17;

	player = new Player();
	ships.push_back(player);

	for (int r = 0; r < invaders_rows; ++r)
	{
		auto rect = IntRect(0, 0, 32, 32);
		for (int c = 0; c < invaders_columns; ++c)
		{
			Vector2f position = {x, y};
			auto *inv = new Invader(rect, position);
			ships.push_back(inv);
			x += 32.0f;
		}
		x = 17;
		y += 32.0f;
	}

	
}

void Update(RenderWindow &window)
{
	//reset clock, recalulate deltatime
	static Clock clock;
	float dt = clock.restart().asSeconds();
	//check and consume events
	Event event;
	while (window.pollEvent(event))
	{
		if (event.type == Event::Closed)
		{
			window.close();
			return;
		}
	}

	//quit via esc key
	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		window.close();
	}
	for (auto &s : ships)
	{
		s->Update(dt);
	};
	Bullet::Update(dt);
}

void Render(RenderWindow &window)
{
	
	for(const auto s : ships)
	{
		window.draw(*s);
	}
	Bullet::Render(window);
}

int main()
{
	RenderWindow window(VideoMode(gameWidth, gameHeight), "SPACE INVADERS");
	Load();
	while (window.isOpen())
	{
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}
	return 0;
}