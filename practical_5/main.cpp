#include "Box2D/Box2D.h"
#include <SFML/Graphics.hpp>

using namespace sf;
b2World* world;

std::vector<b2Body*> bodies;
std::vector<RectangleShape*> sprites;

float physics_scale = 30.f;
float physics_scale_inv = 1.0f / physics_scale;
float gameWidth = 800;
float gameHeight = 600;

//convert from b2Vec2 to a vector2f
inline const Vector2f bv2_to_sv2(const b2Vec2& in)
{
	return Vector2f(in.x*physics_scale, (in.y*physics_scale));
}
//convert from Vcetor2f to b2Vec2
inline const b2Vec2 sv2_to_bv2(const Vector2f& in)
{
	return b2Vec2(in.x * physics_scale_inv, (in.y * physics_scale_inv));
}
//convert from screenspace.y to physics.y
inline const Vector2f invert_height(const Vector2f& in)
{
	return Vector2f(in.x, gameHeight - in.y);
}
b2Body* CreatePhysicsBox(b2World& World, const bool dynamic, const Vector2f& position, const Vector2f& size)
{
	b2BodyDef BodyDef;
	//is dynamic(moving), or static(Stationary)
	BodyDef.type = dynamic ? b2_dynamicBody : b2_staticBody;
	BodyDef.position = sv2_to_bv2(position);
	//create body
	b2Body* body = World.CreateBody(&BodyDef);

	//create the fixture shape
	b2PolygonShape Shape;
	Shape.SetAsBox(sv2_to_bv2(size).x *0.5f, sv2_to_bv2(size).y *0.5f);
	b2FixtureDef FixtureDef;
	//Fixture properties
	FixtureDef.density = dynamic ? 10.f : 0.f;
	FixtureDef.friction = dynamic ? 0.8f : 1.f;
	FixtureDef.restitution = 1.0;
	FixtureDef.shape = &Shape;
	//add to body
	body->CreateFixture(&FixtureDef);
	return body;
}

//create a b2d body with a box fixture, from a sfml::RectagleShape
b2Body* CreatePhysicsBox(b2World& world, const bool dynamic, const RectangleShape& rs)
{
	return CreatePhysicsBox(world, dynamic, rs.getPosition(), rs.getSize());
}

void init()
{
	const b2Vec2 gravity(0.0f, -9.8f);

	//construct a world which holds and simulates the physics bodies
	world = new b2World(gravity);

	//wall dimensions
	Vector2f walls[] = {
		//top
		Vector2f(gameWidth* .5f, 5.f), Vector2f(gameWidth, 10.f),
		//bottom
		Vector2f(gameWidth* .5f, gameHeight - 5.f), Vector2f(gameWidth, 10.f),
		//left
		Vector2f(5.f, gameHeight * .5f), Vector2f(10.f, gameHeight),
		//right
		Vector2f(gameWidth - 5.f, gameHeight * .5f) , Vector2f(10.f, gameHeight)
	};

	//build walls
	for (int i = 0; i < 7; i += 2)
	{
		//create SFML shapes for each wall
		auto wall = new RectangleShape();
		wall->setPosition(walls[i]);
		wall->setSize(walls[i+1]);
		wall->setOrigin(walls[i+1] / 2.0f);
		wall->setFillColor(Color::Green);
		sprites.push_back(wall);
		//create a static physics body for the wall
		auto b = CreatePhysicsBox(*world, false, *wall);
		bodies.push_back(b);
	}
	//create boxes
	for (int i = 1; i < 11; ++i)
	{
		//create SFML shapes for each box
		auto s = new RectangleShape();
		s->setPosition(Vector2f(i*(gameWidth / 12.f), gameHeight * .7f));
		s->setSize(Vector2f(50.f, 50.f));
		s->setOrigin(Vector2f(25.f, 25.f));
		s->setFillColor(Color::White);
		sprites.push_back(s);

		//create a dynamic physics body for the box
		auto b = CreatePhysicsBox(*world, true, *s);
		//give the box a spin
		b->ApplyAngularImpulse(5.f, true);
		bodies.push_back(b);
	}

}

void Update(RenderWindow &window)
{
	//reset clock, recalulate deltatime
	static Clock clock;
	float dt = clock.restart().asSeconds();
	//check and consume events
	Event event;
	while (window.pollEvent(event))
	{
		if (event.type == Event::Closed)
		{
			window.close();
			return;
		}
	}

	//quit via esc key
	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		window.close();
	}
	//step physics world by dt (non-fixed timestep)
	world->Step(dt, 8, 3);

	for (int i = 0; i < bodies.size(); ++i)
	{
		//sync sprites to physics position
		sprites[i]->setPosition(invert_height(bv2_to_sv2(bodies[i]->GetPosition())));
		//sync sprites to physics rotation
		sprites[i]->setRotation((180 / b2_pi)* bodies[i]->GetAngle());
	}
}

void Render(RenderWindow &window)
{
	//draw everything
	for (int i = 0; i < sprites.size(); ++i)
	{
		window.draw(*sprites[i]);
	}
}

int main()
{
	RenderWindow window(VideoMode(gameWidth, gameHeight), "physics");
	init();
	while (window.isOpen())
	{
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}
	return 0;
}