#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

const Keyboard::Key controls[4] = 
{
	Keyboard::W, //player1 up
	Keyboard::S, //player1 down
	Keyboard::P, //player2 up
	Keyboard::L //player2 down
};
const Vector2f paddleSize(25.f, 100.f);
const float ballRadius = 10.f;
const int gameWidth = 800;
const int gameHeight = 600;
const float paddleSpeed = 300.f;
Vector2f ballVelocity;
bool server = false;
Font font;
Text text;
int player1score = 0;
int player2score = 0;

CircleShape ball;
RectangleShape paddles[2];

void Reset()
{
	//reset paddle pos
	paddles[0].setPosition(10 + paddleSize.x / 2, gameHeight / 2);
	paddles[1].setPosition(gameWidth - 10 - paddleSize.x / 2, gameHeight / 2);
	//reset Ball pos
	ball.setPosition(gameWidth / 2 + paddleSize.x / 2, gameHeight / 2);
	ballVelocity = { server ? 100.0f : -100.0f, 60.0f };
	//update score text
	text.setString(to_string(player1score) + " : " + to_string(player2score));
}

void Load()
{
	//set the size and origin of the paddles
	for (auto &p : paddles)
	{
		p.setSize(paddleSize - Vector2f(3, 3));
		p.setOrigin(paddleSize / 2.f);
	}
	//set the size and origin of the ball
	ball.setRadius(ballRadius - 3);
	ball.setOrigin(ballRadius / 2, ballRadius / 2);
	//load font-face from the res dir
	if (!font.loadFromFile("res/font1.ttf"))
	{
		cout << "gay";
	}
	
	//set text element to use font
	text.setFont(font);
	//set the character size to 24 pixels
	text.setCharacterSize(24);
	text.setColor(Color::Green);
	Reset();
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

	//check for ball collision
	const float bx = ball.getPosition().x;
	const float by = ball.getPosition().y;
	//handle paddle movement
	float direction = 0.0f;
	float direction2 = 0.0f;
	if (Keyboard::isKeyPressed(controls[0]))
	{
		direction--;
	}
	if (Keyboard::isKeyPressed(controls[1]))
	{
		direction++;
	}
	if (by>paddles[1].getPosition().y)
	{
		direction2++;
	}
	else
	{
		direction2--;
	}
	paddles[0].move(0, direction*paddleSpeed*dt);
	paddles[1].move(0, direction2*paddleSpeed*dt);
	ball.move(ballVelocity*dt);

	if (by>gameHeight)
	{
		//bottom wall
		ballVelocity.x *= 1.1f;
		ballVelocity.y *= -1.1f;
		ball.move(0, -10);
	}
	else if(by<0)
	{
		//top wall
		ballVelocity.x *= 1.1f;
		ballVelocity.y *= -1.1f;
		ball.move(0, 10);
	}
	else if (bx > gameWidth)
	{
		//right wall
		player1score++;
		Reset();
	}
	else if (bx < 0)
	{
		//left wall
		player2score++;
		Reset();
	}
	else if (
		//ball is inline or behind paddle
		bx<paddleSize.x &&
		//AND ball is below top edge of paddle
		by > paddles[0].getPosition().y - (paddleSize.y * 0.5) &&
		//AND ball is above bottom edge of paddle
		by < paddles[0].getPosition().y + (paddleSize.y * 0.5)
		)
	{
		//bounce off left paddle
		ballVelocity.x *= -1.1f;
		ballVelocity.y *= 1.1f;
		ball.move(10,0);
	}
	else if (
		//ball is inline or behind paddle
		bx>paddles[1].getPosition().x &&
		//AND ball is below top edge of paddle
		by > paddles[1].getPosition().y - (paddleSize.y *0.5) &&
		//AND ball is above bottem edge of paddle
		by < paddles[1].getPosition().y + (paddleSize.y *0.5)
		)
	{
		//bounce off right paddle
		ballVelocity.x *= -1.1f;
		ballVelocity.y *= 1.1f;
		ball.move(-10, 0);
	}
	//dont let the paddles go higher than the gamewindow/ off screen
	if (paddles[0].getPosition().y - paddleSize.y / 2<0)
	{
		paddles[0].move(0, -direction*paddleSpeed*dt);
	}
	if (paddles[1].getPosition().y - paddleSize.y / 2<0)
	{
		paddles[1].move(0, -direction*paddleSpeed*dt);
	}
	if (paddles[0].getPosition().y + paddleSize.y / 2 > gameHeight)
	{
		paddles[0].move(0, -direction * paddleSpeed*dt);
	}
	if (paddles[1].getPosition().y + paddleSize.y / 2 > gameHeight)
	{
		paddles[1].move(0, -direction * paddleSpeed*dt);
	}
}

void Render(RenderWindow &window)
{
	//draw everything
	window.draw(paddles[0]);
	window.draw(paddles[1]);
	window.draw(ball);
	window.draw(text);
}

int main()
{
	RenderWindow window(VideoMode(gameWidth, gameHeight), "PONG");
	Load();
	while (window.isOpen())
	{
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}
	return 0;
}