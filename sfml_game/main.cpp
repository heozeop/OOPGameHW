/*
* program name: Indian Poker Game
* program explanation: Implementing Indian PokerGame with SFML
*/

#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "Card.h"
#include "Player.h"
#include "Enemy.h"
using namespace sf;

// 게임이 끝났는지 확인합니다.
bool isGameEnd(int playerLeftMoney, int enemyLeftMoney, bool draw) {
	if ((playerLeftMoney == 0 || enemyLeftMoney == 0) && !draw)
		return true;

	return false;
}

int main(void) {
	// 플레이어 턴인지 확인 
	bool playerTurn = true;
	bool enemyTurn = false;
	
	//이긴거 확인
	bool playerWin;

	// 감정 고르는 시간
	bool emotionTime = true;

	// 게임 관리
	bool gameStart = false;
	bool gameOver = false;
	bool drew = false;

	// 턴 관리
	bool TurnOver = false;
	bool TurnStart = false;
	bool TurnProceed = false;

	// 판돈관리
	int bettedMoney = 0;
	int lastBettedMoney = 0;

	//윈도우 사이즈 관리
	const int videoSizeX = 1280;
	const int videoSizeY = 800;
	RenderWindow window(VideoMode(videoSizeX, videoSizeY), "The Indian PokerGame!");

	// 게임 시작시 메뉴
	Font font;
	font.loadFromFile("Font/NanumGothic.ttf");
	Text gameStartInfo; // 게임 제목 보여줌
	gameStartInfo.setFont(font);
	gameStartInfo.setString("1 vs 1\nIndian Poker");
	gameStartInfo.setCharacterSize(100);
	gameStartInfo.setPosition(300, 200 );
	Text whoWin;
	whoWin.setFont(font);
	whoWin.setString("Result: NoBody win");
	whoWin.setCharacterSize(50);
	whoWin.setPosition(400,450);
	std::string gameMenu[2] = { "Game\nStart", "Exit" };
	Menu gameStartMenu(window.getSize().x, window.getSize().y, 2, gameMenu);//게임 시작 또는 게임 종료 선택
	gameStartMenu.setAlign(false);
	gameStartMenu.move(gameStartMenu.getRightMostLine() - 2, 0);

	//게임 메뉴판
	std::string game[2] = { "Game\nStart", "Betted\nMoney" };
	Menu emotionAndBettingMoney(window.getSize().x, window.getSize().y, 2, game);
	emotionAndBettingMoney.setAlign(true);
	emotionAndBettingMoney.move(0, emotionAndBettingMoney.getBottonline() / 2);

	// 플레이어 선택지
	const int emotionsIndex = 4;
	const int bettingIndex = 5;
	std::string emotions[emotionsIndex] = { "Well...", "Good!", "OMG","idiot" };
	std::string betting[bettingIndex] = { "Die", "Call","Double", "Triple", "All IN" };
	Menu menu(window.getSize().x, window.getSize().y, emotionsIndex, emotions);
	menu.setAlign(true); // true -> 가로정렬
	menu.move(0, menu.getBottonline());
	Menu bettingMenu(window.getSize().x, window.getSize().y, bettingIndex, betting);
	bettingMenu.setAlign(true);
	bettingMenu.move(0, menu.getBottonline());

	//카드 보여주기 위한 도형
	Vector2f cardSize(150, 200);
	RectangleShape playerCard(cardSize);
	playerCard.setPosition((window.getSize().x - cardSize.x)/2, window.getSize().y * 3 / 5);
	RectangleShape enemyCard(cardSize);
	enemyCard.setPosition(window.getSize().x / 2 - cardSize.x/2, 50.f);

	//적과 플레이어 정보판
	std::string enemyMoneyAndEmotions[2] = { "Left\nMoney: ", "Emotion:\n" };
	Menu enemyPanel(window.getSize().x, window.getSize().y, 2, enemyMoneyAndEmotions);
	enemyPanel.setAlign(true);
	//상대의 이전 배팅 알려주는 문구.
	RectangleShape enemyChoose(Vector2f(200, 100));
	enemyChoose.setFillColor(Color::Black);
	enemyChoose.setPosition(window.getSize().x - 210, 10 );
	Text enemyChooseOne;
	enemyChooseOne.setFont(font);
	enemyChooseOne.setString("Bet Call:\nnothing");
	enemyChooseOne.setPosition(window.getSize().x - 200, 20 );

	//플레이어 정보판 - 남은 돈 표시
	RectangleShape playerMoney(Vector2f(200.f, 100.f));
	playerMoney.setFillColor(Color::Black);
	playerMoney.setPosition(window.getSize().x / 5, window.getSize().y * 3 / 4 - 30.f);
	Text text;
	text.setFont(font);// 게임 시작 메뉴에서 가져옴.
	text.setString("Left\nMoney : ");
	text.setPosition(window.getSize().x / 5 + text.getCharacterSize(), window.getSize().y * 3 / 4 - 20.f);

	// Card class for manage card
	Card playDeck;

	// 플레이어와 enemy 생성
	Player player;
	Enemy enemy(emotions, emotionsIndex);

	// 테이블 조명
	float lightSize = videoSizeY / 5;
	CircleShape tableLite(lightSize);
	tableLite.setFillColor(Color(255,255,255,20));
	tableLite.setPosition(Vector2f((videoSizeX - lightSize*2)/2,(videoSizeY - lightSize*2)/2));
		



	// window loop
	while (window.isOpen()) {

		Vector2i pos = Mouse::getPosition(window);// 마우스 위치는 매 반복횟수마다 확인을 해야합니다.


		if (TurnStart) { //턴 시작할때 값 초기화
			// draw card only when start game.
			TurnStart = false;

			//default betting
			if (!drew) { // 비겼을때는 초기화하지 않습니다.
				player.loseMoney(1); // 판돈
				enemy.loseMoney(1); // 판돈
				bettedMoney = 2; // betted money 초기화
				lastBettedMoney = 1; // lastbettedmoney 초기화
			}
			else
				drew = false;

			//get the card for player
			int card = playDeck.getCard();
			player.setCardNumber(card);

			//get the card for enemy
			card = playDeck.getCard();
			enemy.setCardNumber(card);

			if (playerTurn)
				emotionAndBettingMoney.setButtonString("Player\nTurn", 0);
			enemy.updateWhanTurnStart();

			// enemy정보 패널 초기화
			enemyPanel.setButtonString(enemyMoneyAndEmotions[1] + enemy.getEmotion(), 1);
		}

		// update panel
		text.setString("Left\nMoney: " + std::to_string(player.getLeftMoney()));
		enemyPanel.setButtonString(enemyMoneyAndEmotions[0] + std::to_string(enemy.getLeftMoney()), 0);

		Event event;

		if (player.isAllin()) { // 올인이면 입력 안받습니다.
			TurnOver = true;
		}
		else {
			while (window.pollEvent(event) && !player.isAllin()) { // playerinput 만 생각합니다. player가 올인했으면 입력 안받습니다.
				if (event.type == Event::Closed)
					window.close();
				if (event.type == Event::MouseButtonPressed) {
					if (event.mouseButton.button == Mouse::Left) {
						//game start
						if (!gameStart&&gameStartMenu.getClickedButton(pos) != -1) { // 게임 시작 또는 끝내기
							if (gameStartMenu.getClickedButton(pos) == 0) {
								TurnStart = true;
								gameStart = true;
							}
							else if (gameStartMenu.getClickedButton(pos) == 1)
								return 0;
						}
						if (gameStart) { // 게임이 시작되었으면 플레이어의 입력을 기다립니다.
							// player betting
							if (TurnProceed && playerTurn && !emotionTime) {
								playerTurn = false; // 턴교체

								switch (bettingMenu.getClickedButton(pos))
								{
								case 0:
									lastBettedMoney = 0;
									TurnOver = true;
									TurnProceed = false;
									break;
								case 1:
									TurnOver = true;
									TurnProceed = false;
									break;
								case 2:
									lastBettedMoney *= 2;
									break;
								case 3:
									lastBettedMoney *= 3;
									break;
								case 4:
									lastBettedMoney = player.getLeftMoney();
									break;
								default:
									break;
								}
								lastBettedMoney = player.betting(lastBettedMoney);
								bettedMoney += lastBettedMoney;
								emotionAndBettingMoney.setButtonString("Enemy\nTurn", 0);
							}

							// player emotion
							if (menu.getClickedButton(pos) != -1 && emotionTime && playerTurn) {
								enemy.setEmotion(menu.getClickedButton(pos));
								emotionTime = false;
								TurnProceed = true;
							}
						}
					}
				}
			}
		}


		if (enemyTurn) { // 상대턴입니다.
			enemyTurn = false;
			if (!enemy.isAllin()) {
				lastBettedMoney = enemy.betting(lastBettedMoney);
				emotionAndBettingMoney.setButtonString("Player\nTurn", 0);
				enemyChooseOne.setString("Bet Call:\n"+ enemy.getChoosesString());
				bettedMoney += lastBettedMoney;
				if (enemy.getChooses() == 0 || enemy.getChooses() == 1)
					TurnOver = true;
				sleep(Time(seconds(1))); // 상대의 선택이 진행중이라는 것을 알려주기 위해 잠시 스레드를 멈춥니다.
				playerTurn = true;
			}
			else {
				TurnOver = true;
				lastBettedMoney = -1;
			}
		}

		if (!playerTurn)//턴교체, 자신이 선택한 화면을 띄워주기 위해 필요합니다.
			enemyTurn = true;
	
		// panel update
		emotionAndBettingMoney.setButtonString(game[1] + " : " + std::to_string(bettedMoney), 1);
		text.setString("Left\nMoney: " + std::to_string(player.getLeftMoney()));
		enemyPanel.setButtonString(enemyMoneyAndEmotions[0] + std::to_string(enemy.getLeftMoney()), 0);
		

		if (TurnOver) { // 턴이 끝나면 다음턴을 준비합니다.
			TurnOver = false;
			TurnStart = true;
			emotionTime = true;
			playerWin = false;
			
			if (playDeck.checkUseAllAndThenReset())
				enemy.resetCard();

			if (player.getCardNumber()%10+1 == enemy.getCardNumber()%10+1) 
				drew = true;
			else if(player.getCardNumber()%10+1 > enemy.getCardNumber()%10+1)
				playerWin = false;// 번호 비교.(player가 보고 있는 카드가 상대의 카드이므로.
			else
				playerWin = true;

			// die 선택하면 무조건 지는 것이고 그럴때 lastbettedMoney가 0이다.
			if (lastBettedMoney == 0) {
				playerWin = playerTurn;// 플레이어 턴이 아니면 플레이어가 이긴겁니다.

				// 10인상태에서 die하면 진 사람이 이긴사람에게 10원을 추가로 주어야 한다.
				if (player.getCardNumber() % 10 + 1 == 10 && playerWin) { // 플레이어가 보고 있는 카드가 상대 카드이므로.
					enemy.loseMoney(10);
					bettedMoney += 10;
				}
				else if (enemy.getCardNumber() % 10 + 1 == 10 && !playerWin) {
					player.loseMoney(10);
					bettedMoney += 10;
				}
			}

			if(!drew)
				enemy.updateWhenTurnEnd(!playerWin, player.getCardNumber());// 승패와 본인의 카드의 수를 넘겨 받음. 플레이어 짐 = 상대 이김.
			emotionAndBettingMoney.setButtonString("Turn\nEnded", 0);

			if(drew) // 비기면 돈 안줌.
				emotionAndBettingMoney.setButtonString("Drew", 0);
			else if (playerWin)// 이긴 사람에게 돈줌.
				player.earnMoney(bettedMoney);
			else
				enemy.earnMoney(bettedMoney);

			playDeck.showCard(playerCard, window, enemy.getCardNumber());
			window.draw(enemyChoose);
			window.draw(enemyChooseOne);

			window.display(); // 본인 카드 확인 시켜줄라고 했습니다.
			sleep(Time(seconds(2)));

			if (isGameEnd(player.getLeftMoney(), enemy.getLeftMoney(), drew)) {// 게임이 끝났으면 누가 이겼는지와 함께 다시 시작할 것인지 확인하기 위한 화면을 띄웁니다.
				if (playerWin)
					whoWin.setString("Result: Player Win");
				else
					whoWin.setString("Result: Enemy Win");
				player.reset();
				enemy.reset();
				emotionTime = true;
				playerTurn = true;
				enemyTurn = false;
				gameStart = false;
				gameOver = false;
				drew = false;
				TurnOver = false;
				TurnStart = false;
				TurnProceed = false;

				enemyChooseOne.setString("Bet Call:\nnothing");
			}
		}

		if (!gameStart) { // 시작시 화면을 띄웁니다.
			window.clear(Color::Black);
			window.draw(gameStartInfo);
			window.draw(whoWin);
			gameStartMenu.draw(window);
			gameStartMenu.highLight(pos);
		}
		else {
			//뒷 배경
			window.clear(Color(150, 75, 0));
			window.draw(tableLite);

			//플레이어 메뉴 판
			if(emotionTime) // 먼저 감정 표현을 가져온다.
				menu.draw(window);
			else
				bettingMenu.draw(window);
			menu.highLight(pos);
			bettingMenu.highLight(pos);

			//게임 상황 및 상대 메뉴판
			emotionAndBettingMoney.draw(window);
			enemyPanel.draw(window);
			window.draw(enemyChoose);
			window.draw(enemyChooseOne);

			//플레이어 정보 판
			window.draw(playerMoney);
			window.draw(text);
			if(!TurnOver) // 뒷표지만을 보여줍니다.
				playDeck.showCard(playerCard, window, -1); // -1일때는 뒷표지 보여줌.
			
			playDeck.showCard(enemyCard, window, player.getCardNumber());
		}

		//게임을 화면에 띄웁니다.
		window.display();
	}
}