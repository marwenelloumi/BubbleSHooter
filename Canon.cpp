#include "Canon.h"

Canon::Canon()
{
	this->nbrRest = 0;
	this->texture.loadFromFile("png/canon.png");
	this->texture.setSmooth(true);
	this->shape.setTexture(this->texture);
	this->shape.setPosition(260.f, 440.f);

	//initialiser Bubbles
	//bubble to swipe position
	this->bubbleToSwip->setBubblePosition(sf::Vector2f(293.5, 516.f));

}

Canon::Canon(int n)
{
	this->nbrRest = 0;
	this->texture.loadFromFile("png/canon.png");
	this->texture.setSmooth(true);
	this->shape.setTexture(this->texture);
	this->shape.setPosition(260.f, 440.f);

	//initialiser Bubbles
	//bubble to swipe position
	this->bubbleToSwip = new Bubble();
	this->bubbleToSwip->setBubblePosition(sf::Vector2f(293.5, 516.f));

	this->nbrRest = n-1 ;
	this->gameOver = false;
	this->initBubblesShoot(n);

}

Canon::~Canon()
{
}

Bubble* Canon::getBubbleToShoot()
{
	return this->bubbleToShoot[this->nbrRest];
}

Bubble Canon::getBubbleToSwipe()
{
	return *this->bubbleToSwip;
}

void Canon::setBubbleToSwipe(Bubble& b)
{
	this->bubbleToSwip = &b;
}

void Canon::initBubblesShoot(int n)
{
	for (int i = 0; i < n; i++)
	{
		Bubble* b = new Bubble();
		this->bubbleToShoot.push_back(b);
		//bubble to shoot postion
		this->bubbleToShoot[i]->setBubblePosition(sf::Vector2f(293.5, 390.f));
	}
}

int Canon::getNbrRest()
{
	return this->nbrRest;
}

void Canon::setNbrRest(int n)
{
	this->nbrRest = n-1;
}

bool Canon::getGameOver()
{
	return this->gameOver;
}



void Canon::swipe()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right) &&
		(!this->bubbleToShoot[this->nbrRest]->getShooted()) &&
		(!this->bubbleToShoot[this->nbrRest]->isStopped()))
	{
		sf::Vector2f psh = this->bubbleToShoot[this->nbrRest]->getBubblePosition();
		sf::Vector2f psw = this->bubbleToSwip->getBubblePosition();
		Bubble* t = this->bubbleToShoot[this->nbrRest];
		this->bubbleToShoot[this->nbrRest] = this->bubbleToSwip;
		this->bubbleToSwip = t;

		this->bubbleToShoot[this->nbrRest]->setBubblePosition(psh);
		this->bubbleToSwip->setBubblePosition(psw);
	}
}

Bubble* Canon::shoot( sf::RenderTarget* target , bool test,Bubble* b)
{
	this->swipe();
	if(!test){
		sf::RenderWindow* r = dynamic_cast<sf::RenderWindow*> (target);
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && (!this->bubbleToShoot[this->nbrRest]->getShooted())
		&& (sf::Mouse::getPosition(*r).y<590 && sf::Mouse::getPosition(*r).y > 0 )
		&& (sf::Mouse::getPosition(*r).x < 630 && sf::Mouse::getPosition(*r).x > 0))
	{

		
		this->bubbleToShoot[this->nbrRest]->normaliser(r);
	}
	this->bubbleToShoot[this->nbrRest]->move(target);

	}


	if (this->nbrRest > 0 && this->bubbleToShoot[this->nbrRest]->isStopped())
	{
		this->nbrRest--;
		this->bubbleToShoot[nbrRest]->setColor( b->getBubbleColor());
		return this->bubbleToShoot[this->nbrRest +1 ];

	}
	else if (nbrRest == 0)
	{
		this->gameOver = true;
		return NULL;
	}
	
}

Bubble* Canon::update( sf::RenderTarget* target , bool test , Bubble* b)
{

		return this->shoot(target,test,b);
}

void Canon::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
	this->bubbleToShoot[nbrRest]->render(target);
	this->bubbleToSwip->render(target);

}