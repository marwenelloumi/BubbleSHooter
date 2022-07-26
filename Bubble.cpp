#include "Bubble.h"
#define BUBBLES_AREA_START_X 5
#define BUBBLES_AREA_END_Y 405
#define ARENA_X 640
#define ARENA_Y 590
#include <math.h>

void Bubble::initvariables()
{
	this->currVelocity = sf::Vector2f(0.f, 0.f);
	this->maxSpeed = 18.f;
	this->shooted = false;
	this->stopped = false;
}

void Bubble::initColor()
{

	string imageSrc = "";
	int randomColorPostion = rand() % 6;


	switch (randomColorPostion)
	{
	case 0: this->bubbleColor = couleur::blue; imageSrc = "png/Bubble_blue.png"; break;
	case 1: this->bubbleColor = couleur::red; imageSrc = "png/Bubble_red.png"; break;
	case 2: this->bubbleColor = couleur::grey; imageSrc = "png/Bubble_grey.png"; break;
	case 3: this->bubbleColor = couleur::purple; imageSrc = "png/Bubble_purple.png"; break;
	case 4: this->bubbleColor = couleur::yellow; imageSrc = "png/Bubble_yellow.png"; break;
	case 5: this->bubbleColor = couleur::green; imageSrc = "png/Bubble_green.png"; break;
	}


	this->texture.loadFromFile(imageSrc);
	this->texture.setSmooth(true);




}
void Bubble::normaliser(sf::RenderWindow* w)
{

	float x_bulle = this->shape.getPosition().x;
	float y_bulle = this->shape.getPosition().y;
	float x_curseur = sf::Mouse::getPosition(*w).x ;
	float y_curseur = sf::Mouse::getPosition(*w).y ;
	float x = x_curseur - x_bulle;
	float y = y_curseur - y_bulle;
	float d = sqrtf(x * x + y * y);
	float costheta = x / d;
	float sintheta = y / d;
	sf::Vector2f x_v(1.f, 0.f);
	sf::Vector2f y_v(0.f, 1.f);
	sf::Vector2f aimDirNorm = costheta * x_v + sintheta * y_v;


	this->currVelocity = aimDirNorm * this->maxSpeed;
	this->shooted = true;


}

void Bubble::move(const sf::RenderTarget* target)
{
	/*this->normaliser();*/

	//Left
	if (this->shape.getGlobalBounds().left <= 0.f)
	{
		this->shape.setPosition(0.f, this->shape.getGlobalBounds().top);
		this->currVelocity.x = -this->currVelocity.x;
	}
	//Right
	if (this->shape.getGlobalBounds().left + this->shape.getGlobalBounds().width >= ARENA_X)
	{
		this->shape.setPosition(ARENA_X - this->shape.getGlobalBounds().width, this->shape.getGlobalBounds().top);
		this->currVelocity.x = -this->currVelocity.x;
	}

	//Top
	if (this->shape.getGlobalBounds().top <= 5.f)
	{
		this->shape.setPosition(this->shape.getGlobalBounds().left, ARENA_Y - this->shape.getGlobalBounds().height);
		this->currVelocity.y = -this->currVelocity.y;
	}


	//Bottom
	if (this->shape.getGlobalBounds().top + this->shape.getGlobalBounds().height >= ARENA_Y)
	{
		this->shape.setPosition(this->shape.getGlobalBounds().left, ARENA_Y - this->shape.getGlobalBounds().height);
		this->currVelocity.y = -this->currVelocity.y;
	}

	this->shape.move(this->currVelocity);

}

Bubble::Bubble(sf::Vector2f vel)
{
	this->currVelocity = vel;
	this->bubbleColor = couleur::transparent;
}

Bubble::Bubble()
{

	this->initvariables();
	this->initColor();
	this->shape.setPosition(0.f, 0.f);
	this->shape.setTexture(texture);


}





Bubble::~Bubble()
{
}
void Bubble::setBubblePosition(sf::Vector2f position)
{
	this->shape.setPosition(position);
}

sf::Vector2f Bubble::getBubblePosition() const
{
	return shape.getPosition();
}

sf::Sprite Bubble::getShape()
{
	return this->shape;
}

sf::Vector2f Bubble::getCurrVelocity()
{
	return this->currVelocity;
}







void Bubble::update(const sf::RenderTarget* target)
{
	this->move(target);
}


void Bubble::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}

bool Bubble::isStopped()
{
	return this->stopped;
}

void Bubble::setStopped(bool st)
{
	this->stopped = st;
}

bool Bubble::getShooted()
{
	return this->shooted;
}

void Bubble::setShooted(bool s)
{
	this->shooted = s;
}

void Bubble::setColor(couleur::Colors c)
{
	this->bubbleColor = c;
	string imageSrc = "";
	switch (c)
	{
	case couleur::blue:imageSrc = "png/Bubble_blue.png";
		break;
	case couleur::red:imageSrc = "png/Bubble_red.png";
		break;
	case couleur::grey:imageSrc = "png/Bubble_grey.png";
		break;
	case couleur::purple:imageSrc = "png/Bubble_purple.png";
		break;
	case couleur::yellow:imageSrc = "png/Bubble_yellow.png";
		break;
	case couleur::green:imageSrc = "png/Bubble_green.png";
		break;
	}
	this->texture.loadFromFile(imageSrc);
}

couleur::Colors Bubble::getBubbleColor()
{
	return this->bubbleColor;
}

sf::Vector2f Bubble::setCurrVel(float x, float y)
{
	return this->currVelocity = sf::Vector2f(x, y);
}