#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "Bubble.h"
#include "Canon.h"
#include <vector>
#include "Bubble.h"
#include "Arena.h"
#include "Player.h"
#define BUBBLES_AREA_START_X 5
#define BUBBLES_AREA_START_Y 5
#define BUBBLES_HEIGHT 40
#define BUBBLES_WIDTH 50
#define MAX_BUBBLES 120
#define ROW_BUBBLES 3
#define COLUMN_BUBBLES 12

#include "Level1.h"
#include "Level2.h"
#include <iterator>
class Arena
{
private:
	sf::RectangleShape grid;
	Canon* canon;
	std::vector<Bubble*> bubbles;
	Level level;
	void initBubbles(int n);
	Player player;

	//affichage nbr de tirs
	sf::CircleShape ovale;
	sf::Text NombreTirs;
	sf::Font font;

	//gameover && win
	sf::Sprite winLose;
	sf::Texture winLoseTexture;
	bool youWin;
	bool scoreWinUpdate;

	

public:
	Arena();
	void lancerNextLevel();
	~Arena();
	void incrimenterScore();
	void initNombreTirs();
	void winDetection();
	void loseDetection();
	int existe(int i, vector <int>& v);
	void restartGame();
	Canon getCanon();
	bool isWin();
	void detecter_groupe_couleur(int i, vector <int>& v);
	bool detecter_vide(int i);
	bool updateCollision();
	void update(sf::RenderTarget* target,Player*);
	Bubble* couleur_tir_restante();
	void render(sf::RenderTarget* target);
	
	
};