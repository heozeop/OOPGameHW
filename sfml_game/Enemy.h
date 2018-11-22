#pragma once
#include "Player.h"
#include <string>
#include <cstdlib>

class Enemy : public Player
{
private:
	int* emotionsWeight; // 상대방이 고른 감정에 대한 가중치
	int* emotionsType; // 감정의 타입
	int numberOfEmotions; // 감정 선택지 수
	bool usedCard[20]; // true -> 안씀, false -> 씀
	int numberOfUsedCard = 0; // 사용한 카드
	float counting(); // 나온 숫자들을 가지고 이길 확률을 계산합니다.
	int winRate; // 이길 확률입니다.
	int chooseOne = 0; // 선택한 배팅의 종류를 반환합니다.

	std::string* emotions; // 감정의 종류입니다.

public:
	Enemy(std::string emotions[], int numberOfEmotions = 0);
	~Enemy();
	virtual int betting(int money) override;
	void setEmotion(int emotionType);
	void updateWhanTurnStart(); // 턴 시작할때 카드 숫자를 보고 이길 확률을 계산합니다.
	void updateWhenTurnEnd(bool win, int enemyCardNumber);// 턴 끝에 감정종류와 승패여부를 고려하여 계산을 합니다. 
	virtual void reset() override; // 게임이 다시 시작할때 초기화합니다.
	std::string getEmotion(); // 선택한 감정을 리턴합니다.
	void resetCard(); // 카운팅을 위한 카드를 reset합니다.
	std::string getChoosesString(); // 배팅한 종류에 따라 배팅 문구를 반환합니다.
	int getChooses() { // 배팅의 종류를 반환합니다.
		return chooseOne;
	}
};

