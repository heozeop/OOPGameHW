#pragma once
#include "Player.h"
#include <string>
#include <cstdlib>

class Enemy : public Player
{
private:
	int* emotionsWeight;
	int* emotionsType;
	int numberOfEmotions;
	bool usedCard[20];
	int numberOfUsedCard = 0;
	float counting();
	int winRate;

	std::string* emotions;

public:
	Enemy(std::string emotions[], int numberOfEmotions = 0);
	~Enemy();
	virtual int betting(int money) override;
	void setEmotion(int emotionType);
	void updateWhanTurnStart();
	void updateWhenTurnEnd(bool win, int enemyCardNumber);
	std::string getEmotion();
	void resetCard();
};

