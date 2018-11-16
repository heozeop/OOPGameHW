#include "Card.h"

Card::Card() {

	// get cardset Image
	if (!cardImage.loadFromFile("Textrue/turmpCardColorSet.png")) {
		std::cout << "Can't find the card Images" << std::endl;
		system("pause");
	}

	// get each of card size from card size.
	// this int values below are image dependent which means that according to image, the int values are diverse.
	cardSize = cardImage.getSize();
	cardSize.x /= 5;
	cardSize.y /= 3;

	// get gridPosition of each card(1~10)
	for (int x = 0, int i; x < 2; x++) {
		for (int y = 0; y < 5; y++) {
			gridCardPosition[i].x = x;
			gridCardPosition[i++].y = y;
		}
	}
	// get gridPosition of back of the card
	gridCardPosition[10] = sf::Vector2u(2, 4) + cardSize;

	// set all card be usable;
	std::fill_n(usedCard, NUMBER_OF_TOTAL_CARD, true);
}


int Card::getCard() {
	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution(1, 10);
	int pickedCard = distribution(generator);

	return pickedCard;
}

void Card::showCard(int number, sf::RectangleShape shape, sf::RenderWindow& window) {
	shape.setTexture(&cardImage);
	shape.setTextureRect(sf::IntRect(cardSize.x * gridCardPosition[number].x, cardSize.y * gridCardPosition[number].y, gridCardPosition[number].x, gridCardPosition[number].y));

	window.draw(shape);
}