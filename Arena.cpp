
#include "Arena.h"
#include <algorithm> 


void Arena::initBubbles(int r)
{
	for (int i = 0; i < MAX_BUBBLES; i++)
	{
		Bubble* b = new Bubble(sf::Vector2f(0, 0));
		this->bubbles.push_back(b);
	}
	for (int i = 0; i < r; i++)
	{
		for (int k = 0; k < COLUMN_BUBBLES; k++)
		{
			int j = i * COLUMN_BUBBLES + k;

			Bubble* b = new Bubble();
			this->bubbles[j] = b;

			//Setup the position of the bubble
			sf::Vector2f position(float(BUBBLES_AREA_START_X + (BUBBLES_WIDTH * k)),
				float(BUBBLES_AREA_START_Y + (BUBBLES_HEIGHT * (i))));

			this->bubbles[j]->setBubblePosition(position);
			if (i % 2 == 0)
			{
				float x = bubbles[j]->getBubblePosition().x + BUBBLES_WIDTH / 2;
				float y = bubbles[j]->getBubblePosition().y;
				bubbles[j]->setBubblePosition(sf::Vector2f(x, y));

			}



		}
	}
	this->initNombreTirs();


}

Arena::Arena()
{
	this->level = Level1();

	//initaliser grid
	this->grid.setSize(sf::Vector2f(630, 590));
	this->grid.setFillColor(sf::Color::Transparent);
	this->grid.setOutlineColor(sf::Color::White);
	this->grid.setOutlineThickness(5.f);
	this->grid.setPosition(5.f, 5.f);

	Canon* C = new Canon(this->level.getNbrShoot());
	this->canon = C;

	this->initBubbles(this->level.getNbrLignes());
	this->youWin = false;
	this->scoreWinUpdate = false;
}
void Arena::lancerNextLevel()
{
	this->level = Level2();
	this->restartGame();
}
void Arena::restartGame()
{

	Canon* C = new Canon(this->level.getNbrShoot());
	this->canon = C;

	this->youWin = false;
	this->scoreWinUpdate = false;

	for (int i = 0; i < MAX_BUBBLES; i++)
	{
		Bubble* b = new Bubble(sf::Vector2f(0, 0));
		this->bubbles[i] = b;
	}
	for (int i = 0; i < this->level.getNbrLignes(); i++)
	{
		for (int k = 0; k < COLUMN_BUBBLES; k++)
		{
			int j = i * COLUMN_BUBBLES + k;

			Bubble* b = new Bubble();
			this->bubbles[j] = b;

			//Setup the position of the bubble
			sf::Vector2f position(float(BUBBLES_AREA_START_X + (BUBBLES_WIDTH * k)),
				float(BUBBLES_AREA_START_Y + (BUBBLES_HEIGHT * (i))));

			this->bubbles[j]->setBubblePosition(position);
			if (i % 2 == 0)
			{
				float x = bubbles[j]->getBubblePosition().x + BUBBLES_WIDTH / 2;
				float y = bubbles[j]->getBubblePosition().y;
				bubbles[j]->setBubblePosition(sf::Vector2f(x, y));

			}
		}
	}
	this->initNombreTirs();
	this->player.setScore(0);

}



bool Arena::updateCollision()
{
	sf::FloatRect shape1 = this->canon->getBubbleToShoot()->getShape().getGlobalBounds();

	//Check the collision
	for (size_t i = 0; i < this->bubbles.size(); i++)
	{
		sf::FloatRect shape2 = this->bubbles[i]->getShape().getGlobalBounds();

		float dx = (this->canon->getBubbleToShoot()->getShape().getPosition().x + (shape1.width / 2)) - (this->bubbles[i]->getShape().getPosition().x + (shape2.width / 2));
		float dy = (this->canon->getBubbleToShoot()->getShape().getPosition().y + (shape1.height / 2)) - (this->bubbles[i]->getShape().getPosition().y + (shape2.height / 2));
		float distance = std::sqrt((dx * dx) + (dy * dy));

		if (distance <= (shape1.width / 2) + (shape2.width / 2))
		{
			
			this->canon->getBubbleToShoot()->setStopped(true);
			bool test = this->canon->getBubbleToShoot()->isStopped();
			float y, x;
			int j;

			std::cout << shape1.width << "\n";
			if (dy > shape1.width / 2) {
				y = this->bubbles[i]->getShape().getPosition().y + BUBBLES_HEIGHT;
			}
			else
			{
				y = this->bubbles[i]->getShape().getPosition().y;
			}
			if (this->bubbles[i]->getShape().getPosition().x == 580 )
			{
				x = this->bubbles[i]->getShape().getPosition().x - BUBBLES_WIDTH / 2;
			}
		else {
				
				if (dx < -shape1.width / 2 && y == this->bubbles[i]->getShape().getPosition().y)
				{
					x = this->bubbles[i]->getShape().getPosition().x - BUBBLES_WIDTH;
				}
				else if (dx <= 0)
				{
					x = this->bubbles[i]->getShape().getPosition().x - BUBBLES_WIDTH / 2;
				}
				else if (dx < shape1.width / 2)
				{
					x = this->bubbles[i]->getShape().getPosition().x + BUBBLES_WIDTH / 2;
				}
				else if (dx < shape1.width)
				{
					 x = this->bubbles[i]->getShape().getPosition().x + BUBBLES_WIDTH;
				}
			}

			int posTable_i = (y - BUBBLES_AREA_START_Y) / BUBBLES_HEIGHT;

			int posTable_k = (x - BUBBLES_AREA_START_X) / BUBBLES_WIDTH;

			j = posTable_i * COLUMN_BUBBLES + posTable_k;

			this->canon->getBubbleToShoot()->setBubblePosition(sf::Vector2f(x, y));



			this->bubbles[j] = this->canon->getBubbleToShoot();


			// détection couleur

			vector<int> v;

			detecter_groupe_couleur(j, v);
			if (v.size() >= 3)
			{
				for (int p = 0; p < v.size(); p++)
				{
					Bubble* bu = new Bubble(sf::Vector2f(0, 0));
					this->bubbles[v[p]] = bu;
					this->incrimenterScore();

				}
			}
			return test;
		}
	}

	return  this->canon->getBubbleToShoot()->isStopped();


}

Arena::~Arena()
{
}

void Arena::incrimenterScore()
{
	this->player.setScore(this->player.getScore() + 1);
}
void Arena::initNombreTirs()
{
	//initialiser Nombre TIRS

	this->ovale.setRadius(30);
	this->ovale.setScale(1.7, 1);
	this->ovale.setPosition(520.f, 520.f);
	this->ovale.setFillColor(sf::Color::Transparent);
	this->ovale.setOutlineThickness(4);
	this->ovale.setOutlineColor(sf::Color::White);

	//Nombre TIRS text init
	this->font.loadFromFile("Fonts/PixellettersFull.ttf");
	this->NombreTirs.setFont(this->font);
	this->NombreTirs.setFillColor(sf::Color::Black);
	this->NombreTirs.setStyle(sf::Text::Bold);
	this->NombreTirs.setCharacterSize(40);
	this->NombreTirs.setPosition(sf::Vector2f(555.f, 520.f));


}

int Arena::existe(int i, vector<int>& v)
{
	{
		for (size_t j = 0; j < v.size(); j++)
		{
			if (i == v[j])
				return 1;
		}
		return 0;
	}


}


Canon Arena::getCanon()
{
	return *this->canon;
}

bool Arena::isWin()
{
	return this->youWin;
}

void Arena::detecter_groupe_couleur(int i, vector <int>& v)
{
	int q = 0;
	if (this->existe(i, v) == 0)
	{
		//right

		if (i % 12 != 11)
		{
			if (this->bubbles[i]->getBubbleColor() == bubbles[i + 1]->getBubbleColor())
			{
				if (this->existe(i, v) == 0)
				{
					v.push_back(i);
				}
				detecter_groupe_couleur(i + 1, v);

			}
		}

		//left
		if (i % 12 != 0)
		{
			if (this->bubbles[i]->getBubbleColor() == bubbles[i - 1]->getBubbleColor())
			{
				if (this->existe(i, v) == 0)
				{
					v.push_back(i);
				}
				detecter_groupe_couleur(i - 1, v);

			}
		}

		//top 
		if (i > 12)
		{
			q = i / 12;
			if (q % 2 == 0)
			{
				//top right
				if (this->bubbles[i]->getBubbleColor() == bubbles[i - 11]->getBubbleColor())
				{
					if (this->existe(i, v) == 0)
					{
						v.push_back(i);
					}
					detecter_groupe_couleur(i - 11, v);
				}
				// top left

				if (this->bubbles[i]->getBubbleColor() == bubbles[i - 12]->getBubbleColor())
				{
					if (this->existe(i, v) == 0)
					{
						v.push_back(i);
					}
					detecter_groupe_couleur(i - 12, v);
				}

			}
			else
			{
				
					//top right
					if (this->bubbles[i]->getBubbleColor() == bubbles[i - 12]->getBubbleColor())
					{
						if (this->existe(i, v) == 0)
						{
							v.push_back(i);
						}
						detecter_groupe_couleur(i - 12, v);
					}
					// top left

					if (this->bubbles[i]->getBubbleColor() == bubbles[i - 13]->getBubbleColor())
					{
						if (this->existe(i, v) == 0)
						{
							v.push_back(i);
						}
						detecter_groupe_couleur(i - 13, v);
					}


			}
		}

		//bottom 
		if (i <= 108)
		{
			int q = i / 12;
			if (q % 2 == 0)
			{
				//Bootom right
				if (this->bubbles[i]->getBubbleColor() == bubbles[i + 13]->getBubbleColor())
				{
					if (this->existe(i, v) == 0)
					{
						v.push_back(i);
					}
					detecter_groupe_couleur(i + 13, v);
				}
				// Bottom left 

				if (this->bubbles[i]->getBubbleColor() == bubbles[i + 12]->getBubbleColor())
				{
					if (this->existe(i, v) == 0)
					{
						v.push_back(i);
					}
					detecter_groupe_couleur(i + 12, v);
				}

			}
			else
			{
				
					//bottom right
					if (this->bubbles[i]->getBubbleColor() == bubbles[i + 12]->getBubbleColor())
					{
						if (this->existe(i, v) == 0)
						{
							v.push_back(i);
						}
						detecter_groupe_couleur(i + 12, v);
					}
					// top left

					if (this->bubbles[i]->getBubbleColor() == bubbles[i + 11]->getBubbleColor())
					{
						if (this->existe(i, v) == 0)
						{
							v.push_back(i);
						}
						detecter_groupe_couleur(i + 11, v);
					}

				
			}

		}
		
	}
}

bool Arena::detecter_vide(int i)
{
	//right
	bool right = false;

	if (i % 12 != 11)
	{
		if ( bubbles[i + 1]->getBubbleColor()==couleur::transparent)
		{
			right = true;
		}
	}

	//left
	bool left = false;

	if (i % 12 != 0)
	{
		if ( bubbles[i - 1]->getBubbleColor()==couleur::transparent)
		{
			left = true;
		}
	}
	//top 
	bool top_right = false;
	bool top_left = false;

	if (i > 12)
	{
		int q = i / 12;
		if (q % 2 == 0)
		{
			//top right
			if (bubbles[i - 11]->getBubbleColor() == couleur::transparent)
			{
				top_right = true;
			}
			// top left

			if (bubbles[i - 12]->getBubbleColor() == couleur::transparent)
			{
				top_left = true;
			}

		}
		else
		{

			//top right
			if ( bubbles[i - 12]->getBubbleColor() == couleur::transparent)
			{
				top_right = true;
			}
			// top left

			if (bubbles[i - 13]->getBubbleColor() == couleur::transparent)
			{
				top_left = true;
			}


		}
	}
	
	//bottom
	bool bottom_left = false;
	bool bottom_right = false;
	if (i < 107)
	{
		int q = i / 12;
		if (q % 2 == 0)
		{
			//Bootom right
			if (bubbles[i + 13]->getBubbleColor() == couleur::transparent)
			{
				bottom_right = true;
			}
			// Bottom left 

			if (bubbles[i + 12]->getBubbleColor() == couleur::transparent)
			{
				bottom_left = true;
			}

		}
		else
		{

			//bottom right
			if ( bubbles[i + 12]->getBubbleColor() == couleur::transparent)
			{
				bottom_right = true;
			}
			// top left

			if (bubbles[i + 11]->getBubbleColor() == couleur::transparent)
			{
				bottom_left = true;
			}


		}

	}

	return right && left && top_left && top_right && bottom_right && bottom_left;
}
void Arena::loseDetection()
{
	if (this->getCanon().getGameOver() && !this->youWin)
	{
		for (size_t i = 0; i < MAX_BUBBLES; i++)
		{
			Bubble* b = new Bubble(sf::Vector2f(0, 0));
			this->bubbles[i] = b;
		}
		this->winLoseTexture.loadFromFile("png/you_lose.png");
		this->winLoseTexture.setSmooth(true);
		this->winLose.setTexture(this->winLoseTexture);
		this->winLose.setPosition(175.f, 180.f);
	}
}



void Arena::winDetection() {

	int position = 0;
	while (this->bubbles[position]->getBubbleColor() == couleur::Colors::transparent && position < 119 && !this->getCanon().getGameOver())
	{
		position++;
	}
	if (position == 119)
	{
		this->youWin = true;
		this->winLoseTexture.loadFromFile("png/you_win.png");
		this->winLoseTexture.setSmooth(true);
		this->winLose.setTexture(this->winLoseTexture);
		this->winLose.setPosition(175.f, 180.f);
		if (!this->scoreWinUpdate)
		{
			this->player.setScore(this->player.getScore() + this->canon->getNbrRest());
			this->scoreWinUpdate = true;
		}
	}


}



void Arena::update(sf::RenderTarget* target, Player* p )
{
	p->setScore(this->player.getScore()) ;
	Bubble* b = this->canon->update(target, this->updateCollision(),this->couleur_tir_restante());
	
	for (size_t i = 0; i < MAX_BUBBLES; i++)
	{
		if (detecter_vide(i)) 
		{
			Bubble* b = new Bubble(sf::Vector2f(0, 0));
			this->bubbles[i] = b;
		}	
	}

	//NombreTirs
	std::stringstream ss;
	ss << this->canon->getNbrRest() << "\n";
	this->NombreTirs.setString(ss.str());

	this->winDetection();
	this->loseDetection();
}

Bubble* Arena::couleur_tir_restante() 
{
	vector<Bubble*> v;
	for (int i = 0; i < this->bubbles.size(); i++)
	{

		if (bubbles[i]->getBubbleColor() != couleur::transparent)
		{
			v.push_back(bubbles[i]);
		}

	}
	int r;
	if (v.size() != 0)
	{
		r = rand() % v.size();
		return v[r];
	}
	else return nullptr;
}

void Arena::render(sf::RenderTarget* target)
{

	target->draw(this->grid);
	for (int i = 0; i < this->bubbles.size(); i++)
	{

		this->bubbles[i]->render(target);

	}
	this->canon->render(target);
	target->draw(this->ovale);
	target->draw(this->NombreTirs);
	if (this->getCanon().getGameOver())
	{   //bg_score
		target->draw(this->winLose);
	}
	if (this->youWin)
	{
		target->draw(this->winLose);
	}
}