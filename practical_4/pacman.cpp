#define GHOSTS_COUNT 4
#include "pacman.h"
#include "ecm.h"
#include "system_renderer.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "cmp_sprite.h"

using namespace sf;
using namespace std;

Font font;

void GameScene::load()
{
	{
		auto pl = make_shared<Entity>();
		
		auto s = pl->addComponent<ShapeComponent>();
		s->setShape<sf::CircleShape>(12.f);
		s->getShape().setFillColor(Color::Yellow);
		s->getShape().setOrigin(Vector2f(12.f, 12.f));
		
		_ents.list.push_back(pl);
	}
	
	const sf::Color ghost_cols[]
	{
		{208, 62, 25},
		{219, 133, 28},
		{70, 191, 238},
		{234, 130, 229}
	};
	
	for (int i=0; i<GHOSTS_COUNT; ++i)
	{
		auto ghost = make_shared<Entity>();
		auto s = ghost->addComponent<ShapeComponent>();
		s->setShape<sf::CircleShape>(12.f);
		s->getShape().setFillColor(ghost_cols[i % 4]);
		s->getShape().setOrigin(Vector2f(12.f, 12.f));
		
		_ents.list.push_back(ghost);
	}
}

MenuScene::MenuScene()
{
}

void MenuScene::update(double dt)
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		activeScene = gameScene;
	}

	Scene::update(dt);	
}

void MenuScene::render(sf::RenderWindow &window)
{
	Renderer::queue(&text);
}

void MenuScene::load()
{
	if (!font.loadFromFile("res/fonts/ed.ttf")) {
		std:: cout << "error" << std::endl;
	}
	text.setString("Almost Pacman");
	text.setFont(font);
}

//game scene
void GameScene::respawn()
{
}

void GameScene::update(double dt)
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Tab))
	{
		activeScene = menuScene;
	}
	Scene::update(dt);
}

void GameScene::render(sf::RenderWindow &window)
{
	_ents.render(window);
}

