#include "Player.h"



Player::Player()
{
	
}


Player::~Player()
{
}

bool Player::loseMoney(int money) {

	if (this->money < money) { 
		return true; // need All in
	}

	this->money -= money;
	return false;
}

void Player::earnMoney(int money) {
	this->money += money;
}

int Player::betting(int money) {
	int answer = money;
	if (loseMoney(money)) {//all in 여부 판단
		isAll_In = true;
		answer = this->money;
		this->money = 0;
	}

	return answer;
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
