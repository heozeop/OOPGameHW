#ifndef PLAYER_CLASS_FOR_USER_AND_ENEMY
#define PLAYER_CLASS_FOR_USER_AND_ENEMY
#include <SFML/Graphics.hpp>

class Player
{
private:
	int money;
	int viewCard;
	bool isAll_In = false;

public:
	Player();
	~Player();
	bool loseMoney(int money);
	void earnMoney(int money);
	virtual void betting(int money);
	void setCardNumber(int viewCard);
	int getCardNumber();
};

#endif
