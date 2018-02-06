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

//reference player (byRef)
Player *player;

//things loaded at the start of the game
void Load()
{
	//throw err message if the file for the spritesheet cannot be found
	if(!spritesheet.loadFromFile("res/img/invaders_sheet.png"))
	{
		cerr << "Failed to load spritesheet!" << std::endl;
	}

	//coords for the gamescreen to translate the ships within the future loops
	float x = 17;
	float y = 17;

	//create variable to change the x on the spritesheeet to change the sprite for each row of invaders
	float invspritex = 0;

	//add an instance a the referenced player
	player = new Player();
	//puts the player in the ships vector
	ships.push_back(player);

	//loop within loop for each row and column of the invaders
	for (int r = 0; r < invaders_rows; ++r)
	{
		//location of the sprite within the spritesheet
		auto rect = IntRect(invspritex, 0, 32, 32);
		for (int c = 0; c < invaders_columns; ++c)
		{
			//the pos of each invader
			Vector2f position = {x, y};
			//creation of the invader with the correct sprite and pos
			auto *inv = new Invader(rect, position);
			//shove the newly created invader into the ships vector
			ships.push_back(inv);
			//x changed at the end of the loop for creation of each of the previous invaders buddy placed next to them
			x += 32.0f;
		}
		//reset the starting x at the start of each new row
		x = 17;
		//increment the x in the spritesheet for every row
		invspritex += 32;
		//add the next row below the last by changing y
		y += 32.0f;
	}

	
}

//update the frames
void Update(RenderWindow &window)
{
	//reset clock, recalulate deltatime
	static Clock clock;
	float dt = clock.restart().asSeconds();
	//check and consume events
	Event event;
	//while the game is running check if the event is the close button click
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
	//update each ships actions every frame within the delta time limits
	for (auto &s : ships)
	{
		s->Update(dt);
	};
	//include the bullet updates
	Bullet::Update(dt);
}

//paint the stuff on the canvas
void Render(RenderWindow &window)
{
	//for all the ships draw each one...
	for(const auto s : ships)
	{
		window.draw(*s);
	}
	//call the bullet drawings...
	Bullet::Render(window);
}

int main()
{
	//setup the window for the game
	RenderWindow window(VideoMode(gameWidth, gameHeight), "SPACE INVADERS");
	//call the load function
	Load();
	//update the contents of the window whilst its open
	while (window.isOpen())
	{
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}
	return 0;
}