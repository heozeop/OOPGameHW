#include "Enemy.h"
#include <algorithm>

float Enemy::counting() {
	usedCard[viewCard] = false;
	
	int numberOfCardThatLargerThanViewCard = 0;
	for (int i = 0; i < viewCard; i++) {
		if (usedCard[i])
			numberOfCardThatLargerThanViewCard++;

		if (usedCard[i + 10])
			numberOfCardThatLargerThanViewCard++;
	}

	return (float)numberOfCardThatLargerThanViewCard /(20-numberOfUsedCard) * 100; // 같거나 큰 카드 수 / 남은 카드수
}

Enemy::Enemy(std::string emotions[], int numberOfEmotions)
{
	this->numberOfEmotions = numberOfEmotions;

	emotionsWeight = new int[numberOfEmotions];
	emotionsType = new int[numberOfEmotions];
	emotions = new std::string[numberOfEmotions];

	for (int i = 0; i < numberOfEmotions; i++) 
		this->emotions[i] = emotions[i];
	

	std::fill_n(usedCard, 20, true);
}


Enemy::~Enemy()
{
	delete[] emotionsWeight;
	delete[] emotionsType;
}

int Enemy::betting(int money) {
	if (money > this->money)
		return 0;
	
	if (winRate > 90)
		return 4;
	if (winRate > 80)
		return 3;
	if (winRate > 70)
		return 2;
	if (winRate > 50)
		return 1;
	
	return 0;
}

void Enemy::setEmotion(int emotionType) {
	emotionsType[emotionType]++;
}

void Enemy::updateWhanTurnStart() {
	winRate = counting();
	for (int i = 0; i < numberOfEmotions; i++)
		winRate -= emotionsWeight[i];
}

void Enemy::updateWhenTurnEnd(bool win) {
	int type;
	if (win)
		type = 1;
	else
		type = -1;

	for (int i = 0; i < numberOfEmotions; i++) 
		emotionsWeight[i] += emotionsType[i] * type;

	numberOfUsedCard += 2;
}

std::string Enemy::getEmotion() {
	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution(0, numberOfEmotions);

	return emotions[distribution(generator)];
}