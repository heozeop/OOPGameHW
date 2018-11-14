/*
* program name: Indian Poker Game
* program explanation: Implementing Indian PokerGame with SFML
*/

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Menu.h"
using namespace sf;


void Card() {
	RenderWindow window(VideoMode(500.f, 700.f), "Card");
	
	RectangleShape card;
	card.setSize(Vector2f(500.f,700.f));

	
	Texture cardImage;

	if (!cardImage.loadFromFile("Texture/trumpCards.png")) {
		std::cout << "Couldn't find the card Imgae";
	}


	card.setTexture(&cardImage);

	Vector2u textureSize = cardImage.getSize();
	textureSize.x /= 9;
	textureSize.y /= 6;
	card.setTextureRect(IntRect(textureSize.x *2, textureSize.y*3, textureSize.x, textureSize.y));

	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
		}

		window.clear(Color::White);
		window.draw(card);
		window.display();
	}

}

int main(void) {
	RenderWindow window(VideoMode(1280, 720), "The Indian PokerGame!");
	
	const int emotionsIndex = 4;
	const int bettingIndex = 3;
	std::string emotions[emotionsIndex] = { "Well...", "Good!", "OMG","idiot" };
	std::string betting[bettingIndex] = { "+1", "+n", "All IN" };
	Menu menu(window.getSize().x, window.getSize().y, emotionsIndex, emotions, 2);
	Menu bettingMenu(window.getSize().x, window.getSize().y, bettingIndex, betting, 1);


	Thread thread(&Card);
	thread.launch();

	Texture t1;
	t1.loadFromFile("Texture/Surprised-Baby.jpg");

	Sprite s1;
	s1.setTexture(t1);
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
		window.draw(s1);
		menu.draw(window);
		bettingMenu.draw(window);
		window.display();
	}
}