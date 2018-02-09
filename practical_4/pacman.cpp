#include "pacman.h"
#include <SFML/Graphics.hpp>
#include "system_renderer.h"
#include <iostream>

using namespace sf;

Font font;

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

void GameScene::load()
{
}
