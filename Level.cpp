#include "Level.h"

 Level::Level()
{
	this->nbrShoot = 0;
	this->nbrLignes = 0;
}

Level::~Level()
{
	
}

int Level::getNbrShoot()
{
	return this->nbrShoot;
}
int Level::getNbrLignes()
{
	return this->nbrLignes;
}
void Level::setNbrShoot(int s)
{
	this->nbrShoot = s;
}
void Level::setNbrLignes(int s)
{
	this->nbrLignes = s;
}