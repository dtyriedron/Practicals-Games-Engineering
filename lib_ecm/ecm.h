#pragma once
#include "math.h"
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <memory>
#include <typeindex>
#include <vector>

class Component; //forward declare

class Entity
{
protected:
	std::vector<std::shared_ptr<Component>> _components;
	sf::Vector2f _position;
	float _rotation;
	bool _alive;   //should be updated
	bool _visable;  //should be rendered
	bool _fordeletion;  //should be deleted
public:
	Entity();
	virtual ~Entity() = default;

	virtual void update(double dt);
	virtual void render();

	const sf::Vector2f &getPosition() const;
	void setPosition(const sf::Vector2f &pos);
	bool is_fordeletion() const;
	float getRotation() const;
	void setRotation(float &rot);
	bool isAlive() const;
	void setAlive(bool &alive);
	void setfordelete(bool &del);
	bool isVisable() const;
	void setVisable(bool &vis);
	
	template <typename T, typename... Targs>
	std::shared_ptr<T> addComponent(Targs... params)
	{
		static_assert(std::is_base_of<Component, T>::value, "must be a component");
		std::shared_ptr<T> sp(std::make_shared<T>(this, params ...));
		_components.push_back(sp);
		return sp;
	}
};

struct EntityManager
{
	std::vector<std::shared_ptr<Entity>> list;
	void update(double dt);
	void render(sf::RenderWindow &window);
};

class Component
{
protected:
	Entity * _parent;
	bool _fordeletion;  //should be removed
	explicit Component(Entity *p);
public:
	Component() = delete;
	bool is_fordeletion() const;
	virtual void update(double dt) = 0;
	virtual void render() = 0;
	virtual ~Component();
};