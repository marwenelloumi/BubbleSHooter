#pragma once
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <set>
#include <cstdlib>
#include <iostream>
#include <fstream>

using namespace std;

class Player
{
private:
	string nom;
	int Highscore;
	int score;

	int initHighscore();


public:
	Player();
	~Player();

	//getters & setters

	string getNom();
	void setNom(string);

	int getHighScore();
	void setHighScore(int);

	int getScore();
	void setScore(int);
	int calculeScoreFinal(int);








};

