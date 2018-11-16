/*
* program name: Indian Poker Game
* program explanation: Implementing Indian PokerGame with SFML
*/

#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "Card.h"
using namespace sf;


int main(void) {
	const int videoSizeX = 1280;
	const int videoSizeY = 800;
	RenderWindow window(VideoMode(videoSizeX, videoSizeY), "The Indian PokerGame!");
	
	// Menu for user input
	const int emotionsIndex = 4;
	const int bettingIndex = 3;
	std::string emotions[emotionsIndex] = { "Well...", "Good!", "OMG","idiot" };
	std::string betting[bettingIndex] = { "+1", "+n", "All IN" };
	Menu menu(window.getSize().x, window.getSize().y, emotionsIndex, emotions);
	menu.setAlign(true); // true -> 가로정렬
	menu.move(0, menu.getBottonline());
	Menu bettingMenu(window.getSize().x, window.getSize().y, bettingIndex, betting);

	// Card class for manage card
	Card playDeck;



	Texture t1;
	t1.loadFromFile("Texture/Surprised-Baby.jpg");

	Texture board;
	board.loadFromFile("Texture/boardTexture.jpg");

	float lightSize = videoSizeY / 5;
	CircleShape tableLite(lightSize);
	tableLite.setFillColor(Color(255,255,255,20));
	tableLite.setPosition(Vector2f((videoSizeX - lightSize*2)/2,(videoSizeY - lightSize*2)/2));


	RectangleShape s1(Vector2f(150.f,200.f));

	bool isMove = false;
	float dx = 0, dy = 0;
	
	while (window.isOpen()) {

		Vector2i pos = Mouse::getPosition(window);

		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();

			if (event.type == Event::MouseButtonPressed) {
				if (event.mouseButton.button == Mouse::Left) {
					if (s1.getGlobalBounds().contains(pos.x, pos.y)) {
						isMove = true;
						dx = pos.x - s1.getPosition().x;
						dy = pos.y - s1.getPosition().y;
					}

				}
			}

			if (event.type == Event::MouseButtonReleased) {
				if (event.mouseButton.button == Mouse::Left)
					isMove = false;
			}
		}

		if (isMove) s1.setPosition(pos.x - dx, pos.y - dy);
		menu.highLight(pos);
		bettingMenu.highLight(pos);
		window.clear(Color(150,75,0));
		window.draw(tableLite);
		//menu.draw(window);
		//bettingMenu.draw(window);

		playDeck.showCard( s1, window);

		window.display();
	}
}