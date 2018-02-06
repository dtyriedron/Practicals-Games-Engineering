#include "entity.h"
using namespace std;
using namespace sf;

//gets and returns the position of the entity
const Vector2f Entity::getPosition() { return _position;}

//sets the pos of the entity
void Entity::setPosition(const Vector2f &pos) { _position = pos;}

//moves the position of the entity 
void Entity::move(const Vector2f &pos) { _position += pos;}

//updates the game by dt using the pos of the entity
void Entity::update(const double dt){ _shape->setPosition(_position);}

//creates a shape s and allows it to move
Entity::Entity(unique_ptr<Shape> s) : _shape(std::move(s)) {}