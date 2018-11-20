#ifndef GUI_CLASS_FOR_PLAYER_INPUT
#define GUI_CLASS_FOR_PLAYER_INPUT


#include "SFML/Graphics.hpp"
#include <iostream>
#include <string>

class Menu
{
	const int buttonSize = 200;
	const int minimumScail = 100;

	int gridOffsetX;
	int gridOffsetY;
	int numebrOfButtons;
	unsigned int width;
	unsigned int height;

	bool sortType; // true -> r가로, false -> 세로


	sf::Vector2f intervalForDesign;
	sf::Font font;
	sf::Text* buttons;
	sf::RectangleShape* buttonSquare;

public :
	Menu(unsigned int width, unsigned int height, int numebrOfButtons, std::string nameOfButtons[]);
	~Menu();
	
	void draw(sf::RenderWindow &windows);
	void highLight(sf::Vector2i mousePosition);
	int getClickedButton(sf::Vector2i mousePosition);
	void setAlign( bool sortType);
	void move(int gridPositionX, int gridPositionY); // direction은 상하(true)/좌우(false) 결정
	int getBottonline() { return gridOffsetY - 1; }
	int getRightMostLine() { return gridOffsetX - 1; }
	void setButtonString(std::string name, int button);
	void setOutLineOfButton(int index, bool setOn);
	void setOnBlack(int index, bool setOn);
};

#endif