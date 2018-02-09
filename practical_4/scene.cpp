#include "scene.h"
#include "system_renderer.h"

void Scene::update(double dt)
{
	//put something in here
}

void Scene::render(sf::RenderWindow &window)
{
}

std::vector<std::shared_ptr<Entity>>& Scene::getEnts()
{
	// TODO: insert return statement here
	return _ents.list;
}
