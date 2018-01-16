#include <SFML/Graphics.hpp>
#include <iostream>
#include "ship.h"
//add an instance of a ship
std::vector<Ship *> ships;

using namespace sf;
using namespace std;

const int gameWidth = 800;
const int gameHeight = 600;

sf::Texture spritesheet;
sf::Sprite invader;

void Load()
{
	if(!spritesheet.loadFromFile("res/img/invaders_sheet.png"))
	{
		cerr << "Failed to load spritesheet!" << std::endl;
	}
	invader.setTexture(spritesheet);
	invader.setTextureRect(sf::IntRect(0, 0, 32, 32));
	
	Invader* inv = new Invader(sf::IntRect(0, 0, 32, 32), {100, 100});
	ships.push_back(inv);
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
}

void Render(RenderWindow &window)
{
	window.draw(invader);
	
	for(const auto s : ships)
	{
		window.draw(*s);
	}
	
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