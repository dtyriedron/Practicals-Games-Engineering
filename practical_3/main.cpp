#include <SFML/Graphics.hpp>
#include <iostream>
#include "player.h"
#include "levelsystem.h"

using namespace std;
using namespace sf;

//create the player
Player *player;

void Load()
{
	//create new instance of player
	player = new Player();
	
	ls::loadLevelFile("res/levels/maze_2.txt");
	
	//print the level to the console
	for(size_t y=0; y< ls::getHeight(); ++y)
	{
		for(size_t x=0; x< ls::getWidth(); ++x)
		{
			cout<< ls::getTile({x,y});
		}
		cout<<endl;
	}
}

void update(RenderWindow &window)
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
	player->update(dt);
}

//paint the stuff on the canvas
void render(RenderWindow &window)
{
	ls::render(window);
	player->render(window);
}

int main()
{
	//setup the window for the game
	RenderWindow window(VideoMode(800, 600), "Maze");
	//call the load function
	Load();
	//update the contents of the window whilst its open
	while (window.isOpen())
	{
		window.clear();
		update(window);
		render(window);
		window.display();
	}
	return 0;
}