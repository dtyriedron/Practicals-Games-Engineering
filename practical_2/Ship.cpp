#include "ship.h"
#include "game.h"
#include "bullet.h"

using namespace sf;
using namespace std;

//set the direction and the speed of the invaders 
bool Invader::direction=true;
float Invader::speed=16.0f;

//empty constructor for the ship class
Ship::Ship(){};

//sprite constructor for the ship class
Ship::Ship(IntRect ir) : Sprite()
{
	//protected sprite variable set to the sprite defined in the calling of this method^^
	_sprite = ir;
	//tells the sys that the file is being loaded from an external spritesheet stored in this variable vv
	setTexture(spritesheet);
	//finds the specific rectangle within the spritesheet (with coords set)
	setTextureRect(_sprite);
};

//this will explode a ship when called
void Ship::Explode()
{
	//load in explode sprite
	setTextureRect(IntRect(128, 32, 32, 32));
	//set protected exploded variable to true
	_exploded = true;
}

//empty constructor that can be called for a ship
void Ship::Update(const float &dt) {}

//a getter to find if a ship has been exploded
bool Ship::is_exploded()
{
	return _exploded;
}

//destructor for the ship object
Ship::~Ship() = default;

//empty constructor for the invader class that inherits from the ship class
Invader::Invader() : Ship(){}

//another invader constructor to set the pos of every invader ship
Invader::Invader(sf::IntRect ir, sf::Vector2f pos) : Ship(ir)
{
	setOrigin(16, 16);
	setPosition(pos);
}

//update function for the invader ships
void Invader::Update(const float &dt)
{
	//overriding the ship update method
	Ship::Update(dt);
	
	//moving the ships at a set speed in the x axes only either to the right or left depending on the direction variables bool
	move(dt * (direction ? 1.0f : -1.0f) * speed, 0);

	//checks if the pos of the invaders are on the very right or very left of the screen
	if (((direction && getPosition().x > gameWidth - 16) ||
		(!direction && getPosition().x < 16) && !is_exploded()))
	{
		//change the direction of the invaders
		direction = !direction;
		//loops for all the ships
		for (int i = 0; i < ships.size(); ++i)
		{
			//checks if the ship isnt the players and so moves the inaver ships down 24 pixels
			if (ships[i] != player)
			{
				ships[i]->move(0, 24);
			}
			
		}
	}
	//set the firetime and the explode times for animation and delay of fire times
	static float firetime = 0.0f;
	static float explodetime = 0.0f;
	//decreases the float value every frame
	firetime -= dt;
	explodetime -= dt;

	//checks if the annimation time had finished and there was actually an explsion
	if(explodetime <=0 && is_exploded())
	{
		//sets the time of the explosion (annimation time)
		explodetime = 1.0f;
		//set the ship off the screen
		setPosition(-100, -100);
	}
	
	//checks if the fire time has been delayed and allows any random number that is divisable by 100
	if(firetime <= 0 && rand() % 100 == 0)
	{
		//fires the bullet down towards the player from the invader ship
		Bullet::Fire(getPosition(), true);
		//every 4 ticks a random ship fires down to the player 
		firetime = 4.0f + (rand() % 60);
	}
}

//constructor for the players sprite and pos
Player::Player() : Ship(IntRect(160, 32, 32, 32))
{
	setPosition({ gameHeight * .5f, gameHeight - 32.f });
}

//updates the player
void Player::Update(const float &dt)
{
	//overrides the ships class
	Ship::Update(dt);
	//sets the players speed and direction and the fire time delay for the player
	float direction = 0.0f;
	float playerSpeed = 100.0f;
	static float firetime = 0.0f;
	firetime -= dt;
	//move left
	if (Keyboard::isKeyPressed(Keyboard::A))
	{
		//changes the direction of the player
		direction--;
	}
	//move right
	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		//changes the direction of the player
		direction++;
	}
	//player fire button
	if (firetime <= 0 && Keyboard::isKeyPressed(Keyboard::M))
	{
		//fire a bullet at towards the invaders
		Bullet::Fire(getPosition(), false);
		//delay of firetime between bullets being fired
		firetime = 0.7f;
	}
	//actually moves the player along the x axes at a certain pace
	move(direction*playerSpeed*dt, 0);

	//sets the annimation time of the player
	static float explodetime = 0.0f;
	explodetime -= dt;

	//if the player has been exploded then animate
	if (explodetime <= 0 && player->is_exploded())
	{
		//annimation time of the players explosion
		explodetime = 1.0f;
		//set the ship off the screen
		setPosition(-100, -100);
	}
}

