#ifndef CARD_CALSS_FOR_INDIAN_POKER_GAME
#define CARD_CALSS_FOR_INDIAN_POKER_GAME

#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <algorithm>


#define	NUMBER_OF_TOTAL_CARD 20
#define TYPE_OF_CARDS 11

int GetRandomNumebr(int from, int to) {
	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution(from, to);
	int generatedRandomNumber = distribution(generator);

	return generatedRandomNumber;
}

class Card {
private:
	bool usedCard[NUMBER_OF_TOTAL_CARD];//getting used card

	sf::Texture cardImage;//gett card set Image
	sf::Vector2u cardSize;// get each card size
	sf::Vector2u gridCardPosition[TYPE_OF_CARDS]; // to get the cardImage, Image Dependent

public:
	Card();
	int getCard();
	void showCard(int number, sf::RectangleShape shape, sf::RenderWindow& window);
};


#endif // !CARD_CALSS_FOR_INDIAN_POKER_GAME
