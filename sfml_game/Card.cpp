#include "Card.h"

Card::Card() {
	// get cardset Image
	if (!cardImage.loadFromFile("Texture/turmpCardColorSet.png")) {
		std::cout << "Can't find the card Images" << std::endl;
		system("pause");
	}

	// get each of card size from card size.
	// this int values below are image dependent which means that according to image, the int values are diverse.
	cardSize = cardImage.getSize();
	cardSize.x /= 5;
	cardSize.y = cardSize.y/3;


	// get gridPosition of back of the card
	gridCardPosition[0] = sf::Vector2u(4, 2);

	// get gridPosition of each card(1~10)
	for (int y = 0, i = 1; y < 2; y++) {
		for (int x = 0; x < 5; x++) {
			gridCardPosition[i++] = sf::Vector2u(x, y);
		}
	}

	// set all card be usable;
	std::fill_n(usedCard, NUMBER_OF_TOTAL_CARD, true);

	// set random seed
	std::srand(std::time(NULL));
}

// 0~19사이의 숫자를 리턴하고 기록을 남깁니다.
int Card::getCard() {
	
	while (true) {
		int index = std::rand()%20;
		if (usedCard[index]) {
			usedCard[index] = false;
			return index;
		}
	}


	return -1;
}


// shape에 number에 해당하는 texture를 입혀 window에 띄워줍니다.
void Card::showCard( sf::RectangleShape shape, sf::RenderWindow& window, int number){
	if (number%11 > 10 || number < -1) {
		std::cout << "Out of array range" << std::endl;
		return;
	}

	int gridposition;
	if (number == -1)
		gridposition = 0;
	else
		gridposition = number % 10 + 1;

	shape.setTexture(&cardImage, true);
	shape.setTextureRect(sf::IntRect(gridCardPosition[gridposition].x * cardSize.x,  gridCardPosition[gridposition].y * cardSize.y, cardSize.x, cardSize.y));
	window.draw(shape);
}

//카드를 다 썼는 지 검사하고 다썼으면 다시 뽑을 수 있도록 만듭니다.
bool Card::checkUseAllAndThenReset() {
	for (int i = 0; i < NUMBER_OF_TOTAL_CARD; i++)
		if (usedCard[i]) return false;// 하나라도 카드있으면 리턴

	for (int i = 0; i < NUMBER_OF_TOTAL_CARD; i++) //다썼으면 원상태로 만듦.
		usedCard[i] = true;

	return true;
}