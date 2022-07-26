#pragma once
#include<iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Arena.h"
#include<sstream>
#include "Player.h"
#include "Level1.h"
#include "PushButton.h"

using namespace std;

class Game
{
private:
	//attributs
	//window
	sf::RenderWindow* window;
	sf::Event ev;
	sf::VideoMode videMode;

	sf::Font font;

	//Background
	sf::Sprite bg;
	sf::Texture bgTexture;

	//Arena
	Arena arena;

	// Player
	Player player;

	//Player Name
	PushButton* NameButton;
	




	Level1 level;

	PushButton* musicButton;
	sf::Texture tex;
	bool playMusic;
	sf::Music music;
	PushButton* musicButtonoff;
	sf::Texture tex2;

	//Restart 

	PushButton* restartButton;
	sf::Texture restartTEX;

	//Next Level 
	PushButton* nextLevel;
	sf::Texture nextLevelTex;


	//Score
	sf::Sprite score;
	sf::Texture scoreTexture;
	sf::Text scoreText;



	//HighScore
	sf::Sprite highScore;
	sf::Texture highScoreTexture;
	sf::Text highScoreText;




	//Methodes inaccessibles 
	void initVariables();
	void initWindow();




public:
	//Constructeur / Destructeur
	Game();
	virtual ~Game();


	//getters
	const bool running() const;

	//methodes
	void initFonts();
	void initText();
	void updateOptions(Player*);
	void pollEvents();
	void initButtons();

	void renderOptions(sf::RenderTarget* target);
	void update();
	void render();
};