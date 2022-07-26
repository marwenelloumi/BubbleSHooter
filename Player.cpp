#include "Player.h"

int Player::initHighscore()
{
	string line;
	ifstream myfile("highscore.txt");
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			cout << line << '\n';
		}
		myfile.close();
	}
	else cout << "Unable to open file";
	return stoi(line);

}

Player::Player()
{
	
	this->Highscore = this->initHighscore();
	this->score = 0;
}

Player::~Player()
{
}

string Player::getNom()
{
	return this->nom;
}

void Player::setNom(string nom)
{
	this->nom = nom;
}


int Player::getScore()
{
	return this->score;
}

void Player::setScore(int s)
{
	this->score = s;
}

int Player::calculeScoreFinal(int i )
{
	return this->score + i;
}


int Player::getHighScore()
{
	return this->Highscore;
}

void Player::setHighScore(int H)
{
	this->Highscore = H;
}
