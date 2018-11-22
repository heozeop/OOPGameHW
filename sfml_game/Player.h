#ifndef PLAYER_CLASS_FOR_USER_AND_ENEMY
#define PLAYER_CLASS_FOR_USER_AND_ENEMY
#include <SFML/Graphics.hpp>

class Player
{
protected:
	int money = 20; // 돈은 20원만 가집니다.
	int viewCard = 0; // 보고 있는 카드로, 상대의 카드입니다.
	bool isAll_In = false; //올인 여부를 가립니다.

public:
	Player();
	~Player();
	int loseMoney(int money); // 배팅에서 올인인지 아닌지 판별을 위해 사용되어 bool타입 입니다.
	void earnMoney(int money); //돈을 더합니다.
	virtual int betting(int money); //배팅합니다.
	void setCardNumber(int viewCard); //자신이 보고있는 카드를 설정합니다.
	virtual void reset(); // 게임 다시 시작할 때 초기화합니다.
	int getCardNumber(); // 자신이 보고있는 카드를 반환합니다.
	int getLeftMoney(); // 자신이 현재 가지고 있는 돈을 반환합니다.
	bool isAllin(); //올인여부를 반환합니다.
};

#endif
