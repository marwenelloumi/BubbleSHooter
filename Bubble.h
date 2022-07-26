#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <set>
#include <cstdlib>
using namespace std;

namespace couleur
{
	enum  Colors { blue, red, grey, purple, yellow, green, transparent };
}
class Bubble
{

private:
	sf::Texture texture;
	sf::Sprite shape;
	couleur::Colors bubbleColor;


	//variables de mouvement
	sf::Vector2f  currVelocity;
	float maxSpeed;
	bool shooted;
	void initvariables();
	void initColor();
	bool stopped;


public:

	Bubble(sf::Vector2f);
	Bubble();
	virtual ~Bubble();

	void setBubblePosition(sf::Vector2f);
	sf::Vector2f getBubblePosition() const;
	sf::Sprite getShape();
	sf::Vector2f getCurrVelocity();
	void normaliser(sf::RenderWindow*);

	void move(const sf::RenderTarget* target);
	void update(const sf::RenderTarget* target);
	void render(sf::RenderTarget* target);

	bool isStopped();
	void setStopped(bool);

	bool getShooted();
	void setShooted(bool);
	void setColor(couleur::Colors);
	couleur::Colors getBubbleColor();
	sf::Vector2f setCurrVel(float, float);




};