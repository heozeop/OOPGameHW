#include "Player.h"



Player::Player()
{
}


Player::~Player()
{
}

bool Player::loseMoney(int money) {

	if (this->money < money) return true; // failed

	this->money -= money;
	return false;
}

void Player::earnMoney(int money) {
	this->money += money;
}

void Player::betting(int money) {
	if (loseMoney(money)) {
		isAll_In = true;
		return;
	}
}

void Player::setCardNumber(int viewCard) {
	this->viewCard = viewCard;
}

int Player::getCardNumber() {
	return viewCard;
}