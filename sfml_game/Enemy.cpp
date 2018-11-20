#include "Enemy.h"
#include <algorithm>

float Enemy::counting() {
	usedCard[viewCard] = false;
	
	int numberOfCardThatLargerThanViewCard = 0;
	for (int i = 0; i < viewCard%10; i++) {
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
	this->emotions = new std::string[numberOfEmotions];

	for (int i = 0; i < numberOfEmotions; i++) 
		this->emotions[i] = emotions[i];
	

	std::fill_n(usedCard, 20, true);
	std::srand(std::time(NULL));
}


Enemy::~Enemy()
{
	delete[] emotionsWeight;
	delete[] emotionsType;
}

int Enemy::betting(int money) {
	int bettingMoney = 0;

	//무조건 이기거나 비김.
	if (viewCard == 1) {
		bettingMoney = money * 3;
		if (this->loseMoney(bettingMoney)) { // All in 여부 판단
			bettingMoney = this->money;
			isAll_In = true;
			this->money = 0;
		}
		return money * 3;
	}

	if (winRate > 90) 
		bettingMoney = money;
	
	if (winRate > 80) 
		bettingMoney = money * 3;
	
	if (winRate > 70)
		bettingMoney = money * 2;
	if (winRate > 50)
		bettingMoney = money;

	winRate -= 10;

	if (this->loseMoney(bettingMoney)) { // All in 여부 판단
		bettingMoney = this->money;
		isAll_In = true;
		this->money = 0;
	}
	
	return bettingMoney;
}

void Enemy::setEmotion(int emotionType) {
	emotionsType[emotionType]++;
}

void Enemy::updateWhanTurnStart() {
	winRate = counting();
	for (int i = 0; i < numberOfEmotions; i++)
		winRate -= emotionsWeight[i];
}

void Enemy::updateWhenTurnEnd(bool win, int enemyCardNumber) {
	int type;
	if (win)
		type = 1;
	else
		type = -1;

	for (int i = 0; i < numberOfEmotions; i++) 
		emotionsWeight[i] += emotionsType[i] * type;

	usedCard[enemyCardNumber] = false;

	numberOfUsedCard += 2;
}

std::string Enemy::getEmotion() {

	
	return emotions[rand()%numberOfEmotions];
}

void Enemy::resetCard() {
	for (int i = 0; i < 20; i++) {
		usedCard[i] = true;
	}
}