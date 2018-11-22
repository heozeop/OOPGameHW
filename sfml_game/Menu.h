#ifndef GUI_CLASS_FOR_PLAYER_INPUT
#define GUI_CLASS_FOR_PLAYER_INPUT


#include "SFML/Graphics.hpp"
#include <iostream> // 에러문구 띄우기 위한 헤더파일입니다.
#include <string>

class Menu
{
	const int buttonSize = 200; // 버튼의 크기를 설정합니다.
	const int minimumScail = 100; // 분할을 위한 가장 작은 크기를 정합니다.

	// 화면을 분할하기 위한 offset입니다.
	int gridOffsetX; 
	int gridOffsetY;
	// 버튼의 개수를 설정합니다.
	int numebrOfButtons;
	// 윈도우의 크기를 저장합니다.
	unsigned int width;
	unsigned int height;

	bool sortType; // true -> r가로, false -> 세로, 버튼들의 정렬 방식을 결정합니다.


	sf::Vector2f intervalForDesign; // 디자인을 위한 간격입니다.
	sf::Font font; // 폰트 값입니다.
	sf::Text* buttons; // 텍스트의 배열입니다.
	sf::RectangleShape* buttonSquare; // 상자의 배열입니다.

public :
	Menu(unsigned int width, unsigned int height, int numebrOfButtons, std::string nameOfButtons[]);
	~Menu();
	
	void draw(sf::RenderWindow &windows); // window에 버튼(상자+텍스트)를 그립니다.
	void highLight(sf::Vector2i mousePosition); // 마우스가 상자의 범위에 들어오면 상자와 텍스트의 색깔을 바꿉니다.
	int getClickedButton(sf::Vector2i mousePosition); // 클릭된 상자를 구분할 식별자를 반환합니다.
	void setAlign( bool sortType); // 정렬 방식에 따라 정렬합니다.
	void move(int gridPositionX, int gridPositionY); // direction은 상하(true)/좌우(false) 결정
	int getBottonline() { return gridOffsetY - 1; } // 허용하는 y축 최대 grid값을 반환합니다.
	int getRightMostLine() { return gridOffsetX - 1; } // 허용하는 x축 최대 grid값을 반환합니다.
	void setButtonString(std::string name, int button); // 선택된 버튼의 텍스트를 변화합니다.
};

#endif