#include "Menu.h"

// Menu 생성자. 생성한 창의 크기와 생성할 버튼의 개수, 버튼의 내용으로 버튼을 생성
// 버튼은 세로로 정렬되는 것이 default이다. 
Menu::Menu(unsigned int width, unsigned int height, int numebrOfButtons, std::string nameOfButtons[]){
	if (numebrOfButtons <= 0) { // 버튼을 안만들거면 에러띄우고 정지시킵니다.
		std::cout << "Button must be more than 1" << std::endl;
		system("pause");
	}

	sortType = false;// 세로 default
	
	buttons = new sf::Text[numebrOfButtons];
	buttonSquare = new sf::RectangleShape[numebrOfButtons];
	
	//화면을 분할합니다.
	gridOffsetX = width / minimumScail;
	gridOffsetY = height / minimumScail;
	
	this->width = width;
	this->height = height;


	if (!font.loadFromFile("Font/NanumGothic.ttf")) {
		std::cout << "Can't get the font file" << std::endl;
		system("pause");
	}

	int offsetX = width / gridOffsetX;
	int offsetY = height / (numebrOfButtons + 1) / 2; // 높이의 절반 아래쪽에 버튼을 생성합니다. 버튼 개수에 따라 크기가 달라져야 하므로 버튼의 개수 + 1개로 나누어 영역을 분리합니다.

	intervalForDesign.x = (width - width/numebrOfButtons * (numebrOfButtons - 1) - buttonSize)/2;


	for (int i = 0; i < numebrOfButtons; i++) {
		sf::Vector2f temp(10.f, (offsetY + 10.f)*i + height / 2);
		buttons[i].setFont(font);
		buttons[i].setPosition(temp + sf::Vector2f(50.f, buttons[i].getCharacterSize()/2-5) );
		buttons[i].setString(nameOfButtons[i]);

		buttonSquare[i].setSize(sf::Vector2f(buttonSize, offsetY));
		buttonSquare[i].setFillColor(sf::Color::Black);
		buttonSquare[i].setPosition(temp);
		buttonSquare[i].setOutlineColor(sf::Color::Green); // 나중에 선택가능할 때 표시함.
	}

	this->numebrOfButtons = numebrOfButtons;
}

Menu::~Menu()
{
	delete[] buttons;
	delete[] buttonSquare;
}

void Menu::highLight(sf::Vector2i mousePosition) {

	// 마우스가 버튼 위에 올라오면 색을 변환합니다.
	// 마우스가 범위 밖으로 나가면 원래대로 다시 변환합니다.
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

// 버튼들을 그립니다.
void Menu::draw(sf::RenderWindow &windows) {
	for (int i = 0; i < numebrOfButtons; i++) {
		windows.draw(buttonSquare[i]);
		windows.draw(buttons[i]);
	}
}

//클릭한 버튼을 얻습니다.
int Menu::getClickedButton(sf::Vector2i mousePosition) {
	for (int i = 0; i < numebrOfButtons; i++) {
		if (buttonSquare[i].getGlobalBounds().contains(mousePosition.x, mousePosition.y))
			return i;
	}
	return -1;
}

// 정렬을 다시 해주는 함수. 가로 세로 정렬중에 결정할 수 있다.
void Menu::setAlign(bool sortType) { // sortType == false => 세로/ true => 가로
	
	int offsetX = width / (numebrOfButtons);
	int offsetY = height/2 / (numebrOfButtons+1);
	sf::Vector2f temp(10.f, 10.f);

	for (int i = 0; i < numebrOfButtons; i++) {
		if (sortType)
			temp.x = offsetX * i + intervalForDesign.x;
		else
			temp.y = (offsetY + 10.f)*i + height / 2;

	
		buttons[i].setPosition(temp + sf::Vector2f(20.f,20.f));//+sf::Vector2f(50.f, offsetY / 2 - buttons[i].getCharacterSize() / 2 - 5));
		
		buttonSquare[i].setPosition(temp);
	}
}

//offset 지정을 위한 함수. 전체의 위치를 이동한다.
void Menu::move(int gridPositionX,int gridPositionY) {

	sf::Vector2f position;
	if (gridPositionY >= this->gridOffsetY) {
		std::cout << "can't not move" << std::endl;
		return;
	}
	position.y = height / this->gridOffsetY * gridPositionY;

	if (gridPositionX >= this->gridOffsetX) {
		std::cout << "can't not move" << std::endl;
		return;
	}
	position.x = width / gridOffsetX * gridPositionX;

	for (int i = 0; i < numebrOfButtons; i++) {
		buttons[i].setPosition(buttons[i].getPosition() + position);
		buttonSquare[i].setPosition(buttonSquare[i].getPosition() + position);
	}
}

void Menu::setButtonString(std::string name, int button) {
	buttons[button].setString(name);
}
