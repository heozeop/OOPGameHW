#include "Menu.h"


Menu::Menu(unsigned int width, unsigned int height, int numebrOfButtons, std::string nameOfButtons[], int side){
	if (numebrOfButtons <= 0) {
		std::cout << "Button must be more than 1" << std::endl;
		system("pause");
	}
	
	buttons = new sf::Text[numebrOfButtons];
	buttonSquare = new sf::RectangleShape[numebrOfButtons];
	
	if (side <= 0)
		side = 1;
	this->width = width / 3;
	this->height = height / (numebrOfButtons + 1)/2;

	if (!font.loadFromFile("Font/NanumGothic.ttf")) {
		std::cout << "Can't get the font file" << std::endl;
		system("pause");
	}

	sf::Vector2f offset(10.f,0.f);

	for (int i = 0; i < numebrOfButtons; i++) {
		sf::Vector2f temp(this->width * (side - 1), (this->height+10.f)*i+height/2);
		buttons[i].setFont(font);
		buttons[i].setPosition(temp + sf::Vector2f(50.f, this->height/2 - buttons[i].getCharacterSize()/2-5) + offset);
		buttons[i].setString(nameOfButtons[i]);

		buttonSquare[i].setSize(sf::Vector2f(200, this->height));
		buttonSquare[i].setPosition(temp + offset);
	}

	this->numebrOfButtons = numebrOfButtons;
}


Menu::~Menu()
{
	delete[] buttons;
	delete[] buttonSquare;
}

void Menu::highLight(sf::Vector2i mousePosition) {

	for (int i = 0; i < numebrOfButtons; i++) {
		if (buttonSquare[i].getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
			buttons[i].setFillColor(sf::Color::Black);
			buttonSquare[i].setFillColor(sf::Color::White);
		}
		else {
			buttons[i].setFillColor(sf::Color::White);
			buttonSquare[i].setFillColor(sf::Color::Black);
		}
	}
}

void Menu::draw(sf::RenderWindow &windows) {
	for (int i = 0; i < numebrOfButtons; i++) {
		windows.draw(buttonSquare[i]);
		windows.draw(buttons[i]);
	}
}

int Menu::getClickedButton(sf::Vector2i mousePosition) {
	for (int i = 0; i < numebrOfButtons; i++) {
		if (buttonSquare[i].getGlobalBounds().contains(mousePosition.x, mousePosition.y))
			return i;
	}
}

void Menu::setButtonPosition(int offsetX, int offsetY, bool sortType) {
	for (int i = 0; i < numebrOfButtons; i++) {
	}
}