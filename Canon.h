#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Bubble.h"
#include <vector>
#include<sstream>
#include<iostream>
class Canon
{
private:


	sf::Texture texture;
	sf::Sprite shape;
	Bubble* bubbleToSwip;
	std::vector <Bubble*> bubbleToShoot;
	int nbrRest;
	bool gameOver;
	bool win;


public:
	Canon();
	Canon(int);// int: nbr de bulles à tirer de level
	virtual ~Canon();
	Bubble* getBubbleToShoot();
	Bubble getBubbleToSwipe();
	void setBubbleToSwipe(Bubble& b);
	void initBubblesShoot(int);
	int getNbrRest();
	void setNbrRest(int n);
	bool getGameOver();
	//void move(const sf::RenderTarget* target);
	void swipe();
	Bubble* shoot( sf::RenderTarget* target, bool,Bubble* );
	Bubble* update( sf::RenderTarget* target, bool,Bubble*);
	void render(sf::RenderTarget* target);
	


};
