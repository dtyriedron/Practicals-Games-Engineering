#include "entity.h"
using namespace std;
using namespace sf;

//gets and returns the position of the entity
const Vector2f Entity::getPosition() { return _position;}

//get and returns the colour of the entity
//const Color Entity::getColor() { return _colour; }

//sets the pos of the entity
void Entity::setPosition(const Vector2f &pos) { _position = pos;}

//sets the colour of the entity
//void Entity::setColour(const Color &col) { _colour = col; }

//moves the position of the entity 
void Entity::move(const Vector2f &pos) { _position += pos;}

//updates the game by dt using the pos of the entity
void Entity::update(const double dt){ _shape->setPosition(_position);}

//creates a shape s and allows it to move
Entity::Entity(unique_ptr<Shape> s) : _shape(std::move(s)) {}