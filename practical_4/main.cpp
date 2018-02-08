#include <SFML/Graphics.hpp>
#include <iostream>
#include "player.h"
#include "ghost.h"

using namespace sf;
using namespace std;

const int gameWidth = 800;
const int gameHeight = 600;

//create instances of ghost and the player classes
//Player *player;
vector<shared_ptr<Entity>> ghosts;
//vector<Entity*> playerPos;
void Reset() {}

void Load() {
	//create an instance of player and four instances of ghosts
	//player = new Player();
	//playerPos.push_back(player);
	
	//setting random pos for each the ghosts...
	srand(static_cast <unsigned> (time(0)));
	float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	Vector2f rv = Vector2f(r, r);
	for (int i=0; i<4;++i)
	{
		r+=1.0f;
		auto ghost = make_shared<Ghost>();
		ghost->setPosition(rv);
		ghosts.push_back(ghost);
	}
	
}

void Update(RenderWindow &window) {
	// recalculate delta time
	static Clock clock;
	float dt = clock.restart().asSeconds();
	//check and consume events
	Event event;
	while (window.pollEvent(event)) {
		if (event.type == Event::Closed) {
			window.close();
			return;
		}
	}

	if (Keyboard::isKeyPressed(Keyboard::Escape)) {
		window.close();
	}
	//player->update(dt);
	for(auto &_e : ghosts) //ghosts.capacity()
	{
		_e->update(dt);
	}
}

void Render(RenderWindow &window) {
	//player->render(window);
	for (int i = 0; i<ghosts.capacity(); ++i)
	{
		for (auto &_e : ghosts) //ghosts.capacity()
		{
			_e->render(window);
		}
	}
}

  int main() {
	RenderWindow window(VideoMode(gameWidth, gameHeight), "Coursework");
	
	Load();

	while (window.isOpen()) {
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}

    return 0;
  }
