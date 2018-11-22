#ifndef CARD_CALSS_FOR_INDIAN_POKER_GAME
#define CARD_CALSS_FOR_INDIAN_POKER_GAME

#include <SFML/Graphics.hpp> // Texture, Vector2u
#include <iostream>// cout to give error on console
#include <cstdlib>// for random
#include <time.h>
#include <algorithm>// fill_n


#define	NUMBER_OF_TOTAL_CARD 20
#define TYPE_OF_CARDS 11

class Card {
private:
	bool usedCard[NUMBER_OF_TOTAL_CARD];//getting used card

	sf::Texture cardImage;//gett card set Image
	sf::Vector2u cardInterval; // get card Interval
	sf::Vector2u cardSize;// get each card size
	sf::Vector2u gridCardPosition[TYPE_OF_CARDS]; // to get the cardImage, Image Dependent

public:
	Card();
	int getCard(); // 0~19 사이의 숫자를 리턴합니다.
	void showCard( sf::RectangleShape shape, sf::RenderWindow& window, int number = 0); // 카드를 보여줍니다.
	bool checkUseAllAndThenReset();// 카드를 다 사용했으면 다시 사용할 수 있도록 합니다.
};


#endif // !CARD_CALSS_FOR_INDIAN_POKER_GAME
