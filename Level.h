#pragma once
class Level
{
protected :
	int nbrShoot ;
	int nbrLignes;
public:
	Level();
	virtual ~Level();
	int getNbrShoot();
	int getNbrLignes();
	void setNbrShoot(int);
	void setNbrLignes(int);
};

