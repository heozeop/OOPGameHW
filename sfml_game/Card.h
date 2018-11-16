#ifndef CARD_CALSS_FOR_INDIAN_POKER_GAME
#define CARD_CALSS_FOR_INDIAN_POKER_GAME

#include <SFML/Graphics.hpp> // Texture, Vector2u
#include <iostream>// cout to give error on console
#include <random>// Ramdom class
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
	void showCard( sf::RectangleShape shape, sf::RenderWindow& window, int number = 0);
};


#endif // !CARD_CALSS_FOR_INDIAN_POKER_GAME
