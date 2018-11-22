#include "Player.h"



Player::Player()
{
	
}


Player::~Player()
{
}

int Player::loseMoney(int money) {
	int returnMpney;
	if (this->money < money) { 
		returnMpney = this->money;
		this->money = 0;
		isAll_In = true;
		return returnMpney; // need All in
	}

	this->money -= money;
	return money;
}

void Player::earnMoney(int money) {
	this->money += money;
}

int Player::betting(int money) {
	return loseMoney(money);;
}

void Player::setCardNumber(int viewCard) {
	this->viewCard = viewCard;
}

int Player::getCardNumber() {
	return viewCard;
}

int Player::getLeftMoney() {
	return money;
}

bool Player::isAllin() {
	return isAll_In;
}

void Player::reset() {
	this->money = 20;
	this->viewCard = 0;
	this->isAll_In = false;
}