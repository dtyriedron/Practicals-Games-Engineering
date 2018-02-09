#include "ghost.h"
#include <iostream>
//#include "player.h"

using namespace sf;
using namespace std;


/*
const Keyboard::Key controls[4] =
{
	Keyboard::W, //ghost up
	Keyboard::S, //player down
	Keyboard::A, //player left
	Keyboard::D, //player right
}; //replace with ai movement
*/

void Ghost::update(double dt)
{
	float xdirection = 0.2f; //randomise
	float ydirection = 0.2f;

	/*
	//move in for directions based on ai move
	if(Keyboard::isKeyPressed(controls[0]))
	{
		ydirection--;
		cout << "ai went up" << std::endl;
	}
	if(Keyboard::isKeyPressed(controls[1]))
	{
		ydirection++;
		cout << "ai went down" << std::endl;
	}
	if(Keyboard::isKeyPressed(controls[2]))
	{
		xdirection--;
		cout << "ai went left" << std::endl;
	}
	if(Keyboard::isKeyPressed(controls[3]))
	{
		xdirection++;
		cout << "ai went right" << std::endl;
	}
	
	*/
	//move the ghost
	move(Vector2f(xdirection*_speed*dt, ydirection*_speed*dt));
	//update the pos of the ghost
	Entity::update(dt);
}

//ghost constructor setting default values for every new ghost made of speed: 200 and a circle shape
Ghost::Ghost() : _speed(200.0f), Entity(make_unique<CircleShape>(25.f))
{
	srand(time(NULL));
	_shape->setOrigin(Vector2f(25.0f, 25.0f)); //rand() % 600, rand() % 800 50.f,50.f
	/*while (_shape->getOrigin() == player->getPosition())
	{
		_shape->setOrigin(Vector2f(rand() % 600, rand() % 800));
	}*/
	_shape->setFillColor(Color(Color::Red)); //set this to a random colour rand() % 255, rand() % 255, rand() % 255
	/*while(_shape->getFillColor() == player->getColor())
	{
		//set the shape settings
		_shape->setFillColor(Color(rand() % 255, rand() % 255, rand() % 255)); //set this to a random colour
	}*/
}

//render the ghost's drawings
void Ghost::render(sf::RenderWindow &window) const
{
	//draw the ghost shape which is taken from entity that was set in the ghost's constructor
	window.draw(*_shape);
}