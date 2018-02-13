#define GHOSTS_COUNT 4
#include "pacman.h"
#include "ecm.h"
#include "system_renderer.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "cmp_sprite.h"
#include "cmp_actor_movement.h"
#include "cmp_player_movement.h"
#include "cmp_enemy_ai.h"
#include "levelsystem.h"

using namespace sf;
using namespace std;

Font font;

vector<shared_ptr<Entity>> ghosts;
shared_ptr<Entity> player;

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
void GameScene::load()
{
	ls::loadLevelFile("res/levels/pacman.txt", 25.0f);

	auto pl = make_shared<Entity>();

	auto s = pl->addComponent<ShapeComponent>();
	s->setShape<sf::CircleShape>(12.f);
	s->getShape().setFillColor(Color::Yellow);
	s->getShape().setOrigin(Vector2f(12.f, 12.f));

	auto plm = pl->addComponent<PlayerMovementComponent>();

	_ents.list.push_back(pl);
	player = pl;

	const sf::Color ghost_cols[]
	{
		{ 208, 62, 25 },
		{ 219, 133, 28 },
		{ 70, 191, 238 },
		{ 234, 130, 229 }
	};

	for (int i = 0; i<GHOSTS_COUNT; ++i)
	{
		auto ghost = make_shared<Entity>();

		auto s = ghost->addComponent<ShapeComponent>();
		s->setShape<sf::CircleShape>(12.f);
		s->getShape().setFillColor(ghost_cols[i % 4]);
		s->getShape().setOrigin(Vector2f(12.f, 12.f));

		auto aim = ghost->addComponent<EnemyAIComponent>();

		ghosts.push_back(ghost);
		_ents.list.push_back(ghost);
		
	}
	respawn();
}

void GameScene::respawn()
{
	player->setPosition((ls::findTiles(ls::START)[0]));
	
	auto ghost_spawns = ls::findTiles(ls::ENEMY);
	for (int i = 1; i < _ents.list.size(); ++i)
	{
		_ents.list[i]->setPosition(ghost_spawns[rand() % ghost_spawns.size()]);
	}
}

void GameScene::update(double dt)
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Tab))
	{
		activeScene = menuScene;
	}
	for (auto& g : ghosts)
	{
		if (length(g->getPosition() - player->getPosition()) < 30.0f)
		{
			respawn();
		}
	}

	_ents.update(dt);
	Scene::update(dt);
}

void GameScene::render(sf::RenderWindow &window)
{
	ls::render(Renderer::getWindow());
	_ents.render(window);
}

