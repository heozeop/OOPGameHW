#ifndef GUI_CLASS_FOR_PLAYER_INPUT
#define GUI_CLASS_FOR_PLAYER_INPUT


#include "SFML/Graphics.hpp"
#include <iostream>
#include <string>

class Menu
{
	int numebrOfButtons;
	unsigned int width;
	unsigned int height;

	sf::Font font;
	sf::Text* buttons;
	sf::RectangleShape* buttonSquare;

public :
	Menu(unsigned int width, unsigned int height, int numebrOfButtons, std::string nameOfButtons[], int side);
	~Menu();
	
	void draw(sf::RenderWindow &windows);
	void highLight(sf::Vector2i mousePosition);
	int getClickedButton(sf::Vector2i mousePosition);
	void setButtonPosition(int offsetX, int offsetY, bool sortType);
};

#endif