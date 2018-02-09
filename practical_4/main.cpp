#include <SFML/Graphics.hpp>
#include <iostream>
#include "player.h"
#include "ghost.h"
#include "pacman.h"
#include "system_renderer.h"

using namespace sf;
using namespace std;

const int gameWidth = 800;
const int gameHeight = 600;

shared_ptr<Scene> gameScene;
shared_ptr<Scene> menuScene;
shared_ptr<Scene> activeScene;

//create instances of ghost and the player classes
//Player *player;
//vector<shared_ptr<Entity>> ghosts;
EntityManager em;
//vector<Entity*> playerPos;
void Reset() {}

void Load() {
	//create an instance of player and four instances of ghosts
	//player = new Player();
	//playerPos.push_back(player);
	
	//Load Scene-Local Assets
	gameScene.reset(new GameScene());
	menuScene.reset(new MenuScene());
	gameScene->load();
	menuScene->load();
	//start at the main menu
	activeScene = menuScene;
	
	//   <- this is where main.Load() should end->


	auto player = make_shared<Player>();
	em.list.push_back(player);
	
	//setting random pos for each the ghosts...
	//srand(static_cast <unsigned> (time(0)));
	//float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	Vector2f rv = Vector2f(300.0f, 500.0f);
	for (int i=0; i<4;++i)
	{
		auto ghost = make_shared<Ghost>();
		ghost->setPosition(rv);
		em.list.push_back(ghost);
		rv.x += 60.0f;
	}
	
}

void Update(RenderWindow &window) {
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
	static Clock clock;
	float dt = clock.restart().asSeconds();
	activeScene->update(dt);
}

void Render(RenderWindow &window) {
	Renderer::initialise(window);
	/*for (auto &_e : em.list)
	{	
		_e->render(window);
	}//Renderer::queue(&text);
	*/
	activeScene->render(window);
	//flush to screen
	Renderer::render();
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
