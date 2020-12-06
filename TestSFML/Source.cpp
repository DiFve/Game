#define _CRT_SECURE_NO_WARNINGS
#define MENU 123
#define HIGHSCORE 124
#define CLOSE_HIGHSCORE 125
#define INGAME 456
#define ENDGAME 789
#define EXIT -1
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include<string>
#include<stdio.h>
#include<algorithm>
#include<utility>
#include<vector>
#include<math.h> 
#include<Windows.h>
#include"Player.h" 
#include"Platform.h"
#include"Item.h"
#include"Enemies.h"
#include"Bullet.h"
#include"BombEffect.h"
#include"Button.h"
#include"Decoration.h"
#include"Textbox.h"
#include"DecorationMove.h"
using namespace std;
int stateGame = MENU;
void showText(int x, int y, string word, sf::RenderWindow& window, sf::Font* font, int charSize);
void createEnemy(vector<Enemies>& enemy, int randSpawn, sf::Texture* Enemies1Texture, int hp, int type);
void updateEnemy(vector<Enemies>& enemy, float deltaTime, float playerPosX, float playerPosY, sf::Texture* dieAnimation, sf::Texture* ItemTexture, vector<Item>& item, sf::Sound& enemiesDied1SF, sf::Sound& enemiesDied2SF);
void drawEnemy(vector<Enemies>& enemy, sf::RenderWindow& window);
void bulletCollider(vector<Bullet>& vect, vector<Platform>& wall, vector<Enemies>& enemy, vector<Platform>& extraWalls);
void enemyCollider(vector<Enemies>& enemy, vector<Platform>& wall, vector<Platform>& extraWalls, float deltaTime);
void createBullet(vector<Bullet>& bullet, float playerPosX, float playerPosY, int direction, sf::Texture* bulletTexture);
void updateBullet(vector<Bullet>& vect, float deltaTime);
void drawBullet(vector<Bullet>& vect, sf::RenderWindow& window);
void drawItem(vector<Item>& vect, sf::RenderWindow& window);
void updateItem(vector<Item>& item, float deltaTime);
void itemCollider(vector<Item>& item, Player& player, vector<Enemies>& enemy, sf::Texture* bombItemAnimation, sf::Sound& itemCollectSF, sf::Sound& coffeeCollectSF, sf::Sound& coinCollectSF, sf::Sound& BombSoundEffectSF);
void createBombEffect1(vector <BombEffect>& effect, sf::Texture* bombItemAnimation);
void createBombEffect2(vector <BombEffect>& effect, sf::Texture* bombItemAnimation);
void createBombEffect3(vector <BombEffect>& effect, sf::Texture* bombItemAnimation);
void updateBombEffect(vector <BombEffect>& effect, float deltaTime);
void drawBombEffect(vector <BombEffect>& effect, sf::RenderWindow& window);
void playerCollisionWithEnemies(vector<Enemies>& enemy, Player& player, sf::Texture* playerDiedTexture, vector<Bullet>& bullet, vector<Item>& item, int& min, sf::Sound& diedSF);
void drawExtraWalls(vector<Platform>& extraWalls, sf::RenderWindow& window);
void restartAll(Player& player, vector<Enemies>& enemy, vector<Platform>& extraWalls, vector<Item>& item, vector<Bullet>& bullet);
void customShowText(float x, float y, string word, sf::RenderWindow& window, sf::Font* font, int charSize, sf::Color textColor, sf::Color outLineColor, int thickness);
int bulletDelayCount = 450;
bool allDirItemOff = true;
bool shotGunItemOff = true;
int enemySpawnDelay = 1000;
bool effect1On = false;
bool effect2On = false;
int lifeLeft = 3;
bool effect3On = false;
int scoreIngame = 0;
int timeLeftMin = 150;
int enemyLeft = 0;
float opacityArrow = 0;
bool opacityChange = false;
sf::Clock coffeeClock;
sf::Clock rapidFireClock;
sf::Clock allDirectionsFireClock;
sf::Clock shotGunFireClock;
sf::Clock bombEffectClock;
sf::Clock enemySpawnClock;
sf::Clock clockenemyMove;
sf::Clock bulletClock;
bool changeMap = false;
bool deleteExtraWalls = false;
bool createExtraWalls = false;
bool realDelete = false;
int currentLevel = 1;
bool isShowHighScore = false;
vector <DecorationMove> moveDec;
int main()
{

	srand(time(NULL));
	sf::Font font;
	sf::Font menuFont;
	sf::Clock changeMapDelay;
	sf::Clock timeLeft;
	sf::Clock delayMapChange;
	vector <Enemies> enemies1;
	sf::RenderWindow window(sf::VideoMode(1080, 720), "Adventure of the Prairie King!", sf::Style::Close);
	sf::Texture RightSide;
	sf::Texture Enemies1Texture;
	sf::Texture BGTexture;
	sf::Texture arrowTexture;
	sf::Texture bulletTexture;
	sf::Texture enemyDieAnimation;
	sf::Texture ItemTexture;
	sf::Texture bombItemAnimation;
	sf::Texture lifeLeftTexture;
	sf::Texture playerDiedAnimation;
	sf::Texture fence;
	sf::Texture Enemies2Texture;
	sf::Texture menuBG;
	sf::Texture tree;
	sf::Texture dance;
	sf::Texture how2play;
	sf::Texture borderTexture;
	sf::Texture Enemies3Texture;
	sf::Texture endgameTexture;
	font.loadFromFile("Blockbusted.ttf");
	menuFont.loadFromFile("Minecrafter.Reg.ttf");

	ItemTexture.loadFromFile("res/img/Item.png");
	BGTexture.loadFromFile("res/img/BG1.png");
	menuBG.loadFromFile("res/img/MenuTest.png");
	tree.loadFromFile("res/img/treeDec.png");
	dance.loadFromFile("res/img/menuDec.png");
	how2play.loadFromFile("res/img/howtoplay.png");
	borderTexture.loadFromFile("res/img/border.png");
	endgameTexture.loadFromFile("res/img/EndgameScreen.png");

	vector <Decoration> Dec;
	Dec.push_back(Decoration(&tree, sf::Vector2u(2, 1), 0.5f, sf::Vector2f(32.0f, 32.0f), sf::Vector2f(420.0f, 470.0f)));
	Dec.push_back(Decoration(&dance, sf::Vector2u(4, 1), 0.5f, sf::Vector2f(32.0f, 32.0f), sf::Vector2f(400.0f, 620.0f)));
	Dec.push_back(Decoration(&tree, sf::Vector2u(2, 1), 0.5f, sf::Vector2f(32.0f, 32.0f), sf::Vector2f(260.0f, 570.0f)));
	Dec.push_back(Decoration(&tree, sf::Vector2u(2, 1), 0.5f, sf::Vector2f(32.0f, 32.0f), sf::Vector2f(450.0f, 660.0f)));
	Dec.push_back(Decoration(&tree, sf::Vector2u(2, 1), 0.5f, sf::Vector2f(32.0f, 32.0f), sf::Vector2f(260.0f, 255.0f)));
	Dec.push_back(Decoration(&tree, sf::Vector2u(2, 1), 0.5f, sf::Vector2f(32.0f, 32.0f), sf::Vector2f(830.0f, 340.0f)));
	bombItemAnimation.loadFromFile("res/img/BombEffect.png");
	sf::RectangleShape BackGround(sf::Vector2f(640.0f, 640.0f));
	sf::RectangleShape menuBackGround(sf::Vector2f(640.0f, 640.0f));
	sf::RectangleShape howtoplay(sf::Vector2f(160.0f, 72.0f));
	sf::RectangleShape border(sf::Vector2f(280.0f, 355.0f));
	sf::RectangleShape borderEndgame(sf::Vector2f(400.0f, 300.0f));
	Decoration endGameBackground(&endgameTexture, sf::Vector2u(2, 1), 0.5f, sf::Vector2f(640.0f, 640.0f), sf::Vector2f(530.0f, 340.0f));

	RightSide.loadFromFile("res/img/player.png");
	Enemies1Texture.loadFromFile("res/img/Enemies1_15px.png");
	Enemies2Texture.loadFromFile("res/img/Enemies2.png");
	Enemies3Texture.loadFromFile("res/img/Enemies3.png");
	moveDec.push_back(DecorationMove(&Enemies3Texture, sf::Vector2u(2, 1), 0.3f, 100.0f, sf::Vector2f(70.0f, 300.0f), 2, sf::Vector2f(30.0f, 30.0f)));
	moveDec.push_back(DecorationMove(&Enemies2Texture, sf::Vector2u(2, 1), 0.3f, 100.0f, sf::Vector2f(110.0f, 300.0f), 2, sf::Vector2f(30.0f, 30.0f)));
	moveDec.push_back(DecorationMove(&Enemies1Texture, sf::Vector2u(2, 1), 0.3f, 100.0f, sf::Vector2f(150.0f, 300.0f), 2, sf::Vector2f(30.0f, 30.0f)));
	moveDec.push_back(DecorationMove(&RightSide, sf::Vector2u(4, 4), 0.3f, 99.7f, sf::Vector2f(230.0f, 300.0f), 1, sf::Vector2f(35.0f, 35.0f)));
	BackGround.setOrigin(320.0f, 320.0f);
	BackGround.setPosition(540.0f, 360.0f);
	menuBackGround.setOrigin(320.0f, 320.0f);
	menuBackGround.setPosition(540.0f, 360.0f);
	vector <Platform> invisWall;
	invisWall.push_back(Platform(nullptr, sf::Vector2f(200.0f, 200.0f), sf::Vector2f(120.0f, 250.0f)));
	invisWall.push_back(Platform(nullptr, sf::Vector2f(70.0f, 200.0f), sf::Vector2f(10.0f, 250.0f)));
	invisWall.push_back(Platform(nullptr, sf::Vector2f(300.0f, 200.0f), sf::Vector2f(1010.0f, 250.0f)));
	invisWall.push_back(Platform(nullptr, sf::Vector2f(70.0f, 200.0f), sf::Vector2f(1170.0f, 250.0f)));
	invisWall[0].setFillColor(sf::Color::Black);
	invisWall[1].setFillColor(sf::Color::Black);
	invisWall[2].setFillColor(sf::Color::Black);
	invisWall[3].setFillColor(sf::Color::Black);
	howtoplay.setPosition(600.0f, 580.0f);
	border.setPosition(250.0f, 290.0f);
	border.setOutlineColor(sf::Color::Black);
	border.setOutlineThickness(4);
	border.setTexture(&borderTexture);

	borderEndgame.setPosition(340.0f, 200.0f);
	borderEndgame.setOutlineColor(sf::Color::Black);
	borderEndgame.setOutlineThickness(4);
	borderEndgame.setTexture(&borderTexture);

	howtoplay.setTexture(&how2play);
	menuBackGround.setTexture(&menuBG);
	BackGround.setTexture(&BGTexture);

	sf::SoundBuffer buttonClickBuffer;
	buttonClickBuffer.loadFromFile("res/soundEffect/ButtonClickSoundEffect.wav");


	vector <Button> button;
	button.push_back(Button(sf::Vector2f(600.0f, 400.0f), 30, &menuFont, INGAME, "PLAY", buttonClickBuffer));
	button.push_back(Button(sf::Vector2f(600.0f, 460.0f), 30, &menuFont, HIGHSCORE, "HIGHSCORE", buttonClickBuffer));
	button.push_back(Button(sf::Vector2f(600.0f, 520.0f), 30, &menuFont, EXIT, "EXIT", buttonClickBuffer));
	Button closeButton(sf::Vector2f(500.0f, 300.0f), 16, &menuFont, CLOSE_HIGHSCORE, "X", buttonClickBuffer);
	Button continueButton(sf::Vector2f(460.0f, 435.0f), 30, &menuFont, MENU, "Continue", buttonClickBuffer);
	Player player(&RightSide, sf::Vector2u(4, 4), 0.3f, 85.0f);
	enemyDieAnimation.loadFromFile("res/img/EnemyDieAnimation.png");

	lifeLeftTexture.loadFromFile("res/img/Life.png");
	sf::RectangleShape Life(sf::Vector2f(32.0f, 32.0f));
	Life.setPosition(110.0f, 40.0f);
	Life.setTexture(&lifeLeftTexture);
	vector <Bullet> bullet;
	vector <Item> itemDrop;
	vector <BombEffect> effect1;
	vector <BombEffect> effect2;
	vector <BombEffect> effect3;
	createBombEffect1(effect1, &bombItemAnimation);
	createBombEffect2(effect2, &bombItemAnimation);
	createBombEffect3(effect3, &bombItemAnimation);
	bulletTexture.loadFromFile("res/img/bullet.png");
	playerDiedAnimation.loadFromFile("res/img/PlayerDiedAnimation.png");
	fence.loadFromFile("res/img/fence.png");
	vector <Platform> wall;
	wall.push_back(Platform(nullptr, sf::Vector2f(640.0f, 5.0f), sf::Vector2f(540.0f, 38.0f)));
	wall.push_back(Platform(nullptr, sf::Vector2f(5.0f, 640.0f), sf::Vector2f(218.0f, 360.0f)));
	wall.push_back(Platform(nullptr, sf::Vector2f(5.0f, 640.0f), sf::Vector2f(862.0f, 360.0f)));
	wall.push_back(Platform(nullptr, sf::Vector2f(640.0f, 5.0f), sf::Vector2f(540.0f, 683.0f)));
	wall.push_back(Platform(nullptr, sf::Vector2f(280.0f, 40.0f), sf::Vector2f(360.0f, 661.0f)));
	wall.push_back(Platform(nullptr, sf::Vector2f(280.0f, 40.0f), sf::Vector2f(360.0f, 60.0f)));
	wall.push_back(Platform(nullptr, sf::Vector2f(240.0f, 40.0f), sf::Vector2f(740.0f, 60.0f)));
	wall.push_back(Platform(nullptr, sf::Vector2f(240.0f, 40.0f), sf::Vector2f(740.0f, 661.0f)));
	wall.push_back(Platform(nullptr, sf::Vector2f(40.0f, 280.0f), sf::Vector2f(240.0f, 180.0f)));
	wall.push_back(Platform(nullptr, sf::Vector2f(40.0f, 280.0f), sf::Vector2f(840.0f, 180.0f)));
	wall.push_back(Platform(nullptr, sf::Vector2f(40.0f, 240.0f), sf::Vector2f(240.0f, 560.0f)));
	wall.push_back(Platform(nullptr, sf::Vector2f(40.0f, 240.0f), sf::Vector2f(840.0f, 560.0f)));
	vector <Platform> extraWalls;
	float deltaTime = 0.0f;
	sf::Clock clock;
	Textbox textbox1(24, sf::Color(120, 120, 120, 80), false, font, sf::Vector2f(600.0f, 340.0f));

	string nameInGame = "NONAME";
	vector <pair<int, string>> userScore;
	char temp[255];
	int score[6];
	string name[6];
	continueButton.isClick = true;

	//Sound
	sf::Music menuMusic;
	menuMusic.openFromFile("res/soundEffect/MenuSong.wav");
	menuMusic.setVolume(25);
	menuMusic.setLoop(true);
	bool playMenuMusic = false;

	sf::Music inGameMusic;
	inGameMusic.openFromFile("res/soundEffect/IngameSong.wav");
	inGameMusic.setVolume(25);
	inGameMusic.setLoop(true);
	bool playInGameMusic = false;

	sf::SoundBuffer playerShootBuffer;
	sf::Sound playerShootSF;
	playerShootBuffer.loadFromFile("res/soundEffect/Shoot.wav");
	playerShootSF.setBuffer(playerShootBuffer);
	playerShootSF.setVolume(100);

	sf::SoundBuffer enemiesDied1Buffer;
	sf::Sound enemiesDied1SF;
	enemiesDied1Buffer.loadFromFile("res/soundEffect/EnemiesDied1.wav");
	enemiesDied1SF.setBuffer(enemiesDied1Buffer);
	enemiesDied1SF.setVolume(50);

	sf::SoundBuffer enemiesDied2Buffer;
	sf::Sound enemiesDied2SF;
	enemiesDied2Buffer.loadFromFile("res/soundEffect/EnemiesDied2.wav");
	enemiesDied2SF.setBuffer(enemiesDied2Buffer);
	enemiesDied2SF.setVolume(50);

	sf::SoundBuffer itemCollectBuffer;
	sf::Sound itemCollectSF;
	itemCollectBuffer.loadFromFile("res/soundEffect/ItemCollect.wav");
	itemCollectSF.setBuffer(itemCollectBuffer);
	itemCollectSF.setVolume(100);

	sf::SoundBuffer coffeeCollectBuffer;
	sf::Sound coffeeCollectSF;
	coffeeCollectBuffer.loadFromFile("res/soundEffect/CoffeCollect.wav");
	coffeeCollectSF.setBuffer(coffeeCollectBuffer);
	coffeeCollectSF.setVolume(100);

	sf::SoundBuffer coinCollectBuffer;
	sf::Sound coinCollectSF;
	coinCollectBuffer.loadFromFile("res/soundEffect/Coincollect.wav");
	coinCollectSF.setBuffer(coinCollectBuffer);
	coinCollectSF.setVolume(50);

	sf::SoundBuffer BombSoundEffectBuffer;
	sf::Sound BombSoundEffectSF;
	BombSoundEffectBuffer.loadFromFile("res/soundEffect/BombSoundEffect.wav");
	BombSoundEffectSF.setBuffer(BombSoundEffectBuffer);
	BombSoundEffectSF.setVolume(50);

	sf::SoundBuffer diedBuffer;
	sf::Sound diedSF;
	diedBuffer.loadFromFile("res/soundEffect/Died.wav");
	diedSF.setBuffer(diedBuffer);
	diedSF.setVolume(100);



	while (window.isOpen())
	{
		if (deltaTime > 1.0f / 150.0f)
		{
			deltaTime = 1.0f / 150.0f;
		}
		sf::Event evnt;
		while (window.pollEvent(evnt))
		{
			if (stateGame == EXIT)
			{
				window.close();
			}
			if (evnt.type == evnt.Closed)
			{
				window.close();
			}
			if (evnt.type == evnt.TextEntered)
			{
				textbox1.typedOn(evnt);
			}
		}
		window.clear();
		if (stateGame == MENU)
		{
			if (!playMenuMusic)
			{
				menuMusic.play();
				playMenuMusic = true;
				inGameMusic.stop();
				playInGameMusic = false;
			}
			deltaTime = clock.restart().asSeconds();
			restartAll(player, enemies1, extraWalls, itemDrop, bullet);
			if (continueButton.isClick)
			{
				//------------HIGHSCORE------------------
				userScore.erase(userScore.begin(), userScore.end());
				FILE* fp;
				fp = fopen("./Score.txt", "r");
				for (int i = 0; i < 5; i++)
				{
					fscanf(fp, "%s", temp);
					name[i] = temp;
					fscanf(fp, "%d", &score[i]);
					userScore.push_back(make_pair(score[i], name[i]));
				}
				name[5] = nameInGame;
				score[5] = scoreIngame;
				userScore.push_back(make_pair(score[5], name[5]));
				sort(userScore.begin(), userScore.end());
				fclose(fp);
				fp = fopen("./Score.txt", "w");
				for (int i = 5; i >= 1; i--)
				{
					strcpy(temp, userScore[i].second.c_str());
					fprintf(fp, "%s %d\n", temp, userScore[i].first);
				}
				fclose(fp);

				//------------HIGHSCORE------------------
				isShowHighScore = false;
				moveDec[0].setPosition(sf::Vector2f(230.0f, 300.0f));
				moveDec[1].setPosition(sf::Vector2f(190.0f, 300.0f));
				moveDec[2].setPosition(sf::Vector2f(150.0f, 300.0f));
				moveDec[3].setPosition(sf::Vector2f(70.0f, 300.0f));
				for (int i = 0; i < moveDec.size(); i++)
				{
					moveDec[i].isCollider = false;
				}
				textbox1.resetString();
				continueButton.isClick = false;
				scoreIngame = 0;
				nameInGame = "NONAME";
			}
			for (int i = 0; i < button.size(); i++)
			{
				button[i].Update(sf::Mouse::getPosition(window), stateGame, isShowHighScore);
			}

			for (int i = 0; i < Dec.size(); i++)
			{
				Dec[i].Update(deltaTime);
			}
			for (int i = 0; i < moveDec.size(); i++)
			{
				moveDec[i].Update(deltaTime);
			}
			window.draw(menuBackGround);
			for (int i = 0; i < button.size(); i++)
			{
				button[i].Draw(window);
			}
			textbox1.Update(sf::Mouse::getPosition(window));
			customShowText(345, 90, "adventure", window, &menuFont, 35, sf::Color(96, 57, 19), sf::Color(255, 255, 255), 2);
			customShowText(575, 90, "Of", window, &menuFont, 35, sf::Color(96, 57, 19), sf::Color(255, 255, 255), 2);
			customShowText(645, 90, "the", window, &menuFont, 35, sf::Color(96, 57, 19), sf::Color(255, 255, 255), 2);
			customShowText(320, 135, "Prairie King", window, &menuFont, 60, sf::Color(255, 255, 255), sf::Color(96, 57, 19), 5);

			for (int i = 0; i < Dec.size(); i++)
			{
				Dec[i].Draw(window);
			}


			window.draw(howtoplay);


			for (int i = 0; i < moveDec.size(); i++)
			{
				if ((i == 0 || i == 1) && !moveDec[i].isCollider)
					continue;
				moveDec[i].Draw(window);
			}
			for (int i = 0; i < invisWall.size(); i++)
			{
				invisWall[i].Draw(window);
			}
			if (isShowHighScore)
			{
				closeButton.Update(sf::Mouse::getPosition(window), stateGame, isShowHighScore);
				window.draw(border);
				customShowText(295, 315, "HIGHSCORE", window, &menuFont, 32, sf::Color(96, 57, 19), sf::Color(255, 255, 255), 2);
				customShowText(270, 365, userScore[5].second, window, &menuFont, 20, sf::Color(255, 255, 255), sf::Color(96, 57, 19), 2);
				customShowText(270, 415, userScore[4].second, window, &menuFont, 20, sf::Color(255, 255, 255), sf::Color(96, 57, 19), 2);
				customShowText(270, 460, userScore[3].second, window, &menuFont, 20, sf::Color(255, 255, 255), sf::Color(96, 57, 19), 2);
				customShowText(270, 515, userScore[2].second, window, &menuFont, 20, sf::Color(255, 255, 255), sf::Color(96, 57, 19), 2);
				customShowText(270, 565, userScore[1].second, window, &menuFont, 20, sf::Color(255, 255, 255), sf::Color(96, 57, 19), 2);
				customShowText(430, 365, to_string(userScore[5].first), window, &menuFont, 20, sf::Color(255, 255, 255), sf::Color(96, 57, 19), 2);
				customShowText(430, 415, to_string(userScore[4].first), window, &menuFont, 20, sf::Color(255, 255, 255), sf::Color(96, 57, 19), 2);
				customShowText(430, 460, to_string(userScore[3].first), window, &menuFont, 20, sf::Color(255, 255, 255), sf::Color(96, 57, 19), 2);
				customShowText(430, 515, to_string(userScore[2].first), window, &menuFont, 20, sf::Color(255, 255, 255), sf::Color(96, 57, 19), 2);
				customShowText(430, 565, to_string(userScore[1].first), window, &menuFont, 20, sf::Color(255, 255, 255), sf::Color(96, 57, 19), 2);
				closeButton.Draw(window);
			}
			textbox1.Draw(window);
			customShowText(525, 657, "63010789 Manhermak Praditpong", window, &menuFont, 16, sf::Color::White, sf::Color::Black, 2);
			Collider wallcheck = invisWall[3].GetCollider();
			Collider wallCheckAgain = invisWall[1].GetCollider();

			if (moveDec[0].GetCollider().CheckCollider(wallcheck) || moveDec[0].GetCollider().CheckCollider(wallCheckAgain))
			{
				moveDec[0].isCollider = !moveDec[0].isCollider;
				moveDec[1].isCollider = !moveDec[1].isCollider;
				moveDec[2].isCollider = !moveDec[2].isCollider;
				moveDec[3].isCollider = !moveDec[3].isCollider;
			}
		}
		if (stateGame == INGAME)
		{
			if (!playInGameMusic && player.isAlive)
			{
				menuMusic.stop();
				playMenuMusic = false;
				inGameMusic.play();
				playInGameMusic = true;
			}
			else if (!player.isAlive)
			{
				inGameMusic.stop();
				playInGameMusic = false;
			}
			nameInGame = textbox1.getName();
			if (textbox1.getName() == "")
			{
				nameInGame = "NONAME";
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				stateGame = ENDGAME;
			}
			int enemyMove = clockenemyMove.getElapsedTime().asMilliseconds();
			float enemySpawnTime = enemySpawnClock.getElapsedTime().asMilliseconds();
			float bulletDelay = bulletClock.getElapsedTime().asMilliseconds();
			if (currentLevel == 5 || lifeLeft < 0)
			{
				stateGame = ENDGAME;
			}
			int enemySpawnMap[12];
			for (int i = 0; i < 12; i++)
			{
				enemySpawnMap[i] = 0;
			}
			if (enemySpawnTime > enemySpawnDelay && timeLeftMin > 0)
			{
				for (int i = 0; i < currentLevel+2; i++)
				{
					int randEnemy = rand();
					if (currentLevel > 2 && enemyLeft > 30)
					{
						createEnemy(enemies1, randEnemy, &Enemies3Texture, 1, 3);
						enemySpawnMap[randEnemy % 12] = 1;
					}
					else if (enemySpawnMap[randEnemy % 12] == 0)
					{
						createEnemy(enemies1, randEnemy, &Enemies1Texture, 1, 1);
						enemySpawnMap[randEnemy % 12] = 1;
					}
					
				}
				for (int i = 0; i < currentLevel - 1; i++)
				{
					int randBigEnemy = rand();
					int randEnemy = rand();
					switch (randBigEnemy % 5)
					{
					case 2:
						if (enemySpawnMap[randEnemy % 12] == 0)
						{
							createEnemy(enemies1, randEnemy, &Enemies2Texture, 3, 2);
							enemySpawnMap[randEnemy % 12] = 1;
						}	
						break;
					}
				}
				for (int i = 0; i < currentLevel - 2; i++)
				{
					int randBigEnemy = rand();
					int randEnemy = rand();
					switch (randBigEnemy % 5)
					{
					case 1: case 5:
						createEnemy(enemies1, randEnemy, &Enemies3Texture, 1, 3);
						enemySpawnMap[randEnemy % 12] = 1;
						break;
					}
				}
				enemySpawnDelay = 2500;
				enemySpawnClock.restart();
			}
			if (timeLeftMin <= 0 && enemyLeft == 0)
			{
				changeMap = true;
			}
			if (changeMap)
			{
				currentLevel++;
				deleteExtraWalls = true;
				enemyLeft = -1;
				changeMap = false;

				timeLeftMin = 160;
			}
			if (deleteExtraWalls)
			{
				changeMapDelay.restart();
				extraWalls.erase(extraWalls.begin(), extraWalls.end());
				deleteExtraWalls = false;
				createExtraWalls = true;
			}
			if (createExtraWalls)
			{
				enemySpawnClock.restart();
				enemySpawnDelay = 8000;
				if (currentLevel == 2)
				{
					extraWalls.push_back(Platform(&fence, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(400.0f, 220.0f)));
					extraWalls.push_back(Platform(&fence, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(440.0f, 220.0f)));
					extraWalls.push_back(Platform(&fence, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(680.0f, 220.0f)));
					extraWalls.push_back(Platform(&fence, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(720.0f, 220.0f)));
					extraWalls.push_back(Platform(&fence, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(400.0f, 540.0f)));
					extraWalls.push_back(Platform(&fence, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(440.0f, 540.0f)));
					extraWalls.push_back(Platform(&fence, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(680.0f, 540.0f)));
					extraWalls.push_back(Platform(&fence, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(720.0f, 540.0f)));
					extraWalls.push_back(Platform(&fence, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(400.0f, 260.0f)));
					extraWalls.push_back(Platform(&fence, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(720.0f, 260.0f)));
					extraWalls.push_back(Platform(&fence, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(400.0f, 500.0f)));
					extraWalls.push_back(Platform(&fence, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(720.0f, 500.0f)));
				}
				if (currentLevel == 3)
				{
					extraWalls.push_back(Platform(&fence, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(400.0f, 380.0f)));
					extraWalls.push_back(Platform(&fence, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(560.0f, 220.0f)));
					extraWalls.push_back(Platform(&fence, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(720.0f, 377.0f)));
					extraWalls.push_back(Platform(&fence, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(560.0f, 540.0f)));
				}
				if (currentLevel == 4)
				{
					extraWalls.push_back(Platform(&fence, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(440.0f, 260.0f)));
					extraWalls.push_back(Platform(&fence, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(480.0f, 260.0f)));
					extraWalls.push_back(Platform(&fence, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(520.0f, 260.0f)));
					extraWalls.push_back(Platform(&fence, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(440.0f, 300.0f)));
					extraWalls.push_back(Platform(&fence, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(440.0f, 340.0f)));
					extraWalls.push_back(Platform(&fence, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(680.0f, 260.0f)));
					extraWalls.push_back(Platform(&fence, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(640.0f, 260.0f)));
					extraWalls.push_back(Platform(&fence, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(600.0f, 260.0f)));
					extraWalls.push_back(Platform(&fence, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(680.0f, 300.0f)));
					extraWalls.push_back(Platform(&fence, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(680.0f, 340.0f)));
					extraWalls.push_back(Platform(&fence, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(440.0f, 500.0f)));
					extraWalls.push_back(Platform(&fence, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(480.0f, 500.0f)));
					extraWalls.push_back(Platform(&fence, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(520.0f, 500.0f)));
					extraWalls.push_back(Platform(&fence, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(440.0f, 460.0f)));
					extraWalls.push_back(Platform(&fence, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(440.0f, 420.0f)));
					extraWalls.push_back(Platform(&fence, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(680.0f, 500.0f)));
					extraWalls.push_back(Platform(&fence, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(640.0f, 500.0f)));
					extraWalls.push_back(Platform(&fence, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(600.0f, 500.0f)));
					extraWalls.push_back(Platform(&fence, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(680.0f, 460.0f)));
					extraWalls.push_back(Platform(&fence, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(680.0f, 420.0f)));
				}
				for (int i = 0; i < extraWalls.size(); i++)
				{
					extraWalls[i].setFillColor(sf::Color(255, 255, 255, 255));
				}
				createExtraWalls = false;
				enemyLeft = 0;
			}
			deltaTime = clock.restart().asSeconds();

			if (bulletDelay > bulletDelayCount && allDirItemOff && shotGunItemOff && player.isAliveReturn())
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				{
					playerShootSF.play();
					createBullet(bullet, player.Getposition().x, player.Getposition().y, 4, &bulletTexture);
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				{
					playerShootSF.play();
					createBullet(bullet, player.Getposition().x, player.Getposition().y, 5, &bulletTexture);
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				{
					playerShootSF.play();
					createBullet(bullet, player.Getposition().x, player.Getposition().y, 6, &bulletTexture);
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				{
					playerShootSF.play();
					createBullet(bullet, player.Getposition().x, player.Getposition().y, 7, &bulletTexture);
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				{
					playerShootSF.play();
					createBullet(bullet, player.Getposition().x, player.Getposition().y, 0, &bulletTexture);
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				{
					playerShootSF.play();
					createBullet(bullet, player.Getposition().x, player.Getposition().y, 1, &bulletTexture);
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				{
					playerShootSF.play();
					createBullet(bullet, player.Getposition().x, player.Getposition().y, 2, &bulletTexture);
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				{
					playerShootSF.play();
					createBullet(bullet, player.Getposition().x, player.Getposition().y, 3, &bulletTexture);
				}

				bulletClock.restart();
			}
			if (bulletDelay > bulletDelayCount && !allDirItemOff && player.isAliveReturn())
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				{
					playerShootSF.play();
					createBullet(bullet, player.Getposition().x, player.Getposition().y, 0, &bulletTexture);
					createBullet(bullet, player.Getposition().x, player.Getposition().y, 1, &bulletTexture);
					createBullet(bullet, player.Getposition().x, player.Getposition().y, 2, &bulletTexture);
					createBullet(bullet, player.Getposition().x, player.Getposition().y, 3, &bulletTexture);
					createBullet(bullet, player.Getposition().x, player.Getposition().y, 4, &bulletTexture);
					createBullet(bullet, player.Getposition().x, player.Getposition().y, 5, &bulletTexture);
					createBullet(bullet, player.Getposition().x, player.Getposition().y, 6, &bulletTexture);
					createBullet(bullet, player.Getposition().x, player.Getposition().y, 7, &bulletTexture);
					bulletClock.restart();

				}
			}
			if (bulletDelay > bulletDelayCount && !shotGunItemOff && player.isAliveReturn())
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				{
					playerShootSF.play();
					createBullet(bullet, player.Getposition().x, player.Getposition().y, 5, &bulletTexture);
					createBullet(bullet, player.Getposition().x, player.Getposition().y, 10, &bulletTexture);
					createBullet(bullet, player.Getposition().x, player.Getposition().y, 11, &bulletTexture);
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				{
					playerShootSF.play();
					createBullet(bullet, player.Getposition().x, player.Getposition().y, 4, &bulletTexture);
					createBullet(bullet, player.Getposition().x, player.Getposition().y, 22, &bulletTexture);
					createBullet(bullet, player.Getposition().x, player.Getposition().y, 23, &bulletTexture);
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				{
					playerShootSF.play();
					createBullet(bullet, player.Getposition().x, player.Getposition().y, 7, &bulletTexture);
					createBullet(bullet, player.Getposition().x, player.Getposition().y, 18, &bulletTexture);
					createBullet(bullet, player.Getposition().x, player.Getposition().y, 19, &bulletTexture);
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				{
					playerShootSF.play();
					createBullet(bullet, player.Getposition().x, player.Getposition().y, 6, &bulletTexture);
					createBullet(bullet, player.Getposition().x, player.Getposition().y, 14, &bulletTexture);
					createBullet(bullet, player.Getposition().x, player.Getposition().y, 15, &bulletTexture);
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				{
					playerShootSF.play();
					createBullet(bullet, player.Getposition().x, player.Getposition().y, 2, &bulletTexture);
					createBullet(bullet, player.Getposition().x, player.Getposition().y, 8, &bulletTexture);
					createBullet(bullet, player.Getposition().x, player.Getposition().y, 9, &bulletTexture);
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				{
					playerShootSF.play();
					createBullet(bullet, player.Getposition().x, player.Getposition().y, 1, &bulletTexture);
					createBullet(bullet, player.Getposition().x, player.Getposition().y, 12, &bulletTexture);
					createBullet(bullet, player.Getposition().x, player.Getposition().y, 13, &bulletTexture);
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				{
					playerShootSF.play();
					createBullet(bullet, player.Getposition().x, player.Getposition().y, 0, &bulletTexture);
					createBullet(bullet, player.Getposition().x, player.Getposition().y, 20, &bulletTexture);
					createBullet(bullet, player.Getposition().x, player.Getposition().y, 21, &bulletTexture);
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				{
					playerShootSF.play();
					createBullet(bullet, player.Getposition().x, player.Getposition().y, 3, &bulletTexture);
					createBullet(bullet, player.Getposition().x, player.Getposition().y, 16, &bulletTexture);
					createBullet(bullet, player.Getposition().x, player.Getposition().y, 17, &bulletTexture);
				}

				bulletClock.restart();
			}
			updateBullet(bullet, deltaTime);
			player.Update(deltaTime);
			enemyCollider(enemies1, wall, extraWalls, deltaTime);
			updateEnemy(enemies1, deltaTime, player.Getposition().x, player.Getposition().y, &enemyDieAnimation, &ItemTexture, itemDrop, enemiesDied1SF, enemiesDied2SF);
			updateItem(itemDrop, deltaTime);
			updateBombEffect(effect1, deltaTime);
			updateBombEffect(effect2, deltaTime);
			updateBombEffect(effect3, deltaTime);
			Collider playerCollison = player.GetCollider();
			for (int i = 0; i < wall.size(); i++)
			{
				wall[i].GetCollider().CheckCollider(playerCollison);
			}
			for (int i = 0; i < extraWalls.size(); i++)
			{
				extraWalls[i].GetCollider().CheckCollider(playerCollison);
			}

			bulletCollider(bullet, wall, enemies1, extraWalls);
			itemCollider(itemDrop, player, enemies1, &bombItemAnimation, itemCollectSF, coffeeCollectSF, coinCollectSF, BombSoundEffectSF);
			playerCollisionWithEnemies(enemies1, player, &playerDiedAnimation, bullet, itemDrop, timeLeftMin, diedSF);


			window.draw(BackGround);

			if (player.isAliveReturn() && (timeLeft.getElapsedTime().asSeconds() > 1) && (timeLeftMin > 0))
			{
				timeLeft.restart();
				timeLeftMin--;
			}
			string timeLeftSec = "0";
			if (timeLeftMin % 60 >= 10)
			{
				timeLeftSec = to_string(timeLeftMin % 60);
			}
			else
			{
				timeLeftSec += to_string(timeLeftMin % 60);
			}
			window.draw(Life);
			showText(930, 50, "LEVEL :", window, &font, 32);
			showText(1030, 50, to_string(currentLevel), window, &font, 32);
			showText(150, 50, "x", window, &font, 12);
			showText(930, 130, "SCORE", window, &font, 32);
			showText(930, 180, to_string(scoreIngame), window, &font, 32);
			showText(60, 150, "Time Left", window, &font, 32);
			showText(80, 200, to_string(timeLeftMin / 60), window, &font, 32);
			showText(100, 200, ":", window, &font, 32);
			showText(120, 200, timeLeftSec, window, &font, 32);
			showText(170, 40, to_string(lifeLeft), window, &font, 24);
			drawExtraWalls(extraWalls, window);
			drawItem(itemDrop, window);
			drawBullet(bullet, window);
			drawEnemy(enemies1, window);
			if (effect1On)
			{
				drawBombEffect(effect1, window);
			}
			else if (effect2On)
			{
				drawBombEffect(effect2, window);
			}
			else if (effect3On)
			{
				drawBombEffect(effect3, window);
			}
			if (changeMapDelay.getElapsedTime().asMilliseconds() < 500)
			{
				for (int i = 0; i < extraWalls.size(); i++)
				{
					extraWalls[i].setFillColor(sf::Color(255, 255, 255, 0));
				}
			}
			else if (changeMapDelay.getElapsedTime().asMilliseconds() < 1000)
			{
				for (int i = 0; i < extraWalls.size(); i++)
				{
					extraWalls[i].setFillColor(sf::Color(255, 255, 255, 255));
				}
			}
			else if (changeMapDelay.getElapsedTime().asMilliseconds() < 1500)
			{
				for (int i = 0; i < extraWalls.size(); i++)
				{
					extraWalls[i].setFillColor(sf::Color(255, 255, 255, 0));
				}
			}
			else if (changeMapDelay.getElapsedTime().asMilliseconds() < 2000)
			{
				for (int i = 0; i < extraWalls.size(); i++)
				{
					extraWalls[i].setFillColor(sf::Color(255, 255, 255, 255));
				}
			}
			else if (changeMapDelay.getElapsedTime().asMilliseconds() < 2500)
			{
				for (int i = 0; i < extraWalls.size(); i++)
				{
					extraWalls[i].setFillColor(sf::Color(255, 255, 255, 0));
				}
			}
			else if (changeMapDelay.getElapsedTime().asMilliseconds() < 3000)
			{
				for (int i = 0; i < extraWalls.size(); i++)
				{
					extraWalls[i].setFillColor(sf::Color(255, 255, 255, 255));
				}
			}
			else if (changeMapDelay.getElapsedTime().asMilliseconds() < 3500)
			{
				for (int i = 0; i < extraWalls.size(); i++)
				{
					extraWalls[i].setFillColor(sf::Color(255, 255, 255, 0));
				}
			}
			else if (changeMapDelay.getElapsedTime().asMilliseconds() < 4000)
			{
				for (int i = 0; i < extraWalls.size(); i++)
				{
					extraWalls[i].setFillColor(sf::Color(255, 255, 255, 255));
				}
			}
			
			player.Draw(window);
		}
		if (stateGame == ENDGAME)
		{
			inGameMusic.stop();
			playInGameMusic = false;
			deltaTime = clock.restart().asSeconds();
			endGameBackground.Update(deltaTime);
			endGameBackground.Draw(window);
			window.draw(borderEndgame);
			continueButton.Update(sf::Mouse::getPosition(window), stateGame, isShowHighScore);
			continueButton.Draw(window);
			customShowText(427, 230, "Your Score", window, &menuFont, 35, sf::Color(255, 255, 255), sf::Color(96, 57, 19), 2);
			customShowText(540 - (20.0f * (to_string(scoreIngame).size())), 305, to_string(scoreIngame), window, &menuFont, 68, sf::Color(96, 57, 19), sf::Color(255, 255, 255), 2);
		}

		window.display();
	}

	return 0;
}

int effectRand = -1;
void restartAll(Player& player, vector<Enemies>& enemy, vector<Platform>& extraWalls, vector<Item>& item, vector<Bullet>& bullet)
{
	clockenemyMove.restart();
	enemySpawnClock.restart();
	bulletClock.restart();
	changeMap = false;
	deleteExtraWalls = false;
	createExtraWalls = false;
	realDelete = false;
	currentLevel = 1;
	enemyLeft = 0;
	timeLeftMin = 150;
	allDirItemOff = true;
	shotGunItemOff = true;
	player.setPlayerSpeed(85.0f);
	bulletDelayCount = 450;
	if (enemy.size() != 0)
	{
		enemy.erase(enemy.begin(), enemy.end());
	}
	if (extraWalls.size() != 0)
	{
		extraWalls.erase(extraWalls.begin(), extraWalls.end());
	}
	if (item.size() != 0)
	{
		item.erase(item.begin(), item.end());
	}
	if (bullet.size() != 0)
	{
		bullet.erase(bullet.begin(), bullet.end());
	}
	lifeLeft = 3;
	player.setPosition(540.0f, 360.0f);
	player.dieFrame = -801;
}
void drawExtraWalls(vector<Platform>& extraWalls, sf::RenderWindow& window)
{
	for (int i = 0; i < extraWalls.size(); i++)
	{
		extraWalls[i].Draw(window);
	}
}
void enemyCollider(vector<Enemies>& enemy, vector<Platform>& wall, vector<Platform>& extraWalls, float deltaTime)
{
	for (Enemies& enemy : enemy)
	{
		Collider enemy1Collision = enemy.GetCollider();
		for (Platform& wall : wall)
		{
			if (enemy.type != 3)
				wall.GetCollider().CheckCollider(enemy1Collision);
		}
		for (Platform& extraWalls : extraWalls)
		{
			if(enemy.type != 3)
				extraWalls.GetCollider().CheckCollider(enemy1Collision);
		}
	}
}
void playerCollisionWithEnemies(vector<Enemies>& enemy, Player& player, sf::Texture* playerDiedTexture, vector<Bullet>& bullet, vector<Item>& item, int& min, sf::Sound& diedSF)
{
	for (int i = 0; i < enemy.size(); i++)
	{
		Collider enemy1Colilision = enemy[i].GetCollider();
		if (player.GetCollider().itemColliderCheck(enemy1Colilision) && enemy[i].isThisAlive())
		{
			if (min > 130)	min = 150;
			else
			{
				min += 20;
				if ((min % 10) != 0)
				{
					min += (10 - (min % 10));
				}
			}
			enemySpawnClock.restart();
			lifeLeft--;
			enemySpawnDelay = 6000;
			enemy.erase(enemy.begin(), enemy.end());
			bullet.erase(bullet.begin(), bullet.end());
			item.erase(item.begin(), item.end());
			player.dieAnimation(playerDiedTexture, false, sf::Vector2u(5, 1));
			enemyLeft = 0;
			diedSF.play();
			break;
		}
	}

}
void createEnemy(vector<Enemies>& enemy, int randSpawn, sf::Texture* Enemies1Texture, int hp, int type)
{
	int itemDropRate = rand();
	switch (randSpawn % 12)
	{
	case(0):
	{
		enemy.push_back(Enemies(Enemies1Texture, sf::Vector2u(2, 1), 0.3f, 40.0f, 241.85, 337.2, hp, (itemDropRate * randSpawn), type));
		break;
	}
	case(1):
	{
		enemy.push_back(Enemies(Enemies1Texture, sf::Vector2u(2, 1), 0.3f, 40.0f, 241.85, 374.458, hp, (itemDropRate * randSpawn), type));
		break;
	}
	case(2):
	{
		enemy.push_back(Enemies(Enemies1Texture, sf::Vector2u(2, 1), 0.3f, 40.0f, 241.285, 422.5, hp, (itemDropRate * randSpawn), type));
		break;
	}
	case(3):
	{
		enemy.push_back(Enemies(Enemies1Texture, sf::Vector2u(2, 1), 0.3f, 40.0f, 517.608, 58, hp, (itemDropRate * randSpawn), type));
		break;
	}
	case(4):
	{
		enemy.push_back(Enemies(Enemies1Texture, sf::Vector2u(2, 1), 0.3f, 40.0f, 559.379, 58, hp, (itemDropRate * randSpawn), type));
		break;
	}
	case(5):
	{
		enemy.push_back(Enemies(Enemies1Texture, sf::Vector2u(2, 1), 0.3f, 40.0f, 602.5, 58, hp, (itemDropRate * randSpawn), type));
		break;
	}
	case(6):
	{
		enemy.push_back(Enemies(Enemies1Texture, sf::Vector2u(2, 1), 0.3f, 40.0f, 842, 337.5, hp, (itemDropRate * randSpawn), type));
		break;
	}
	case(7):
	{
		enemy.push_back(Enemies(Enemies1Texture, sf::Vector2u(2, 1), 0.3f, 40.0f, 842, 374.147, hp, (itemDropRate * randSpawn), type));
		break;
	}
	case(8):
	{
		enemy.push_back(Enemies(Enemies1Texture, sf::Vector2u(2, 1), 0.3f, 40.0f, 842, 422.5, hp, (itemDropRate * randSpawn), type));
		break;
	}
	case(9):
	{
		enemy.push_back(Enemies(Enemies1Texture, sf::Vector2u(2, 1), 0.3f, 40.0f, 602.5, 663, hp, (itemDropRate * randSpawn), type));
		break;
	}
	case(10):
	{
		enemy.push_back(Enemies(Enemies1Texture, sf::Vector2u(2, 1), 0.3f, 40.0f, 554.865, 663, hp, (itemDropRate * randSpawn), type));
		break;
	}
	case(11):
	{
		enemy.push_back(Enemies(Enemies1Texture, sf::Vector2u(2, 1), 0.3f, 40.0f, 517.5, 663, hp, (itemDropRate * randSpawn), type));
		break;
	}

	}

	enemyLeft++;

}
void updateItem(vector<Item>& item, float deltaTime)
{
	for (Item& item : item)
	{
		item.Update(deltaTime);
	}
}
void updateEnemy(vector<Enemies>& vect, float deltaTime, float playerPosX, float playerPosY, sf::Texture* dieAnimation, sf::Texture* ItemTexture, vector<Item>& item, sf::Sound& enemiesDied1SF, sf::Sound& enemiesDied2SF)
{
	for (int i = 0; i < vect.size(); i++)
	{
		for (int j = 0; j < vect.size(); j++)
		{
			if (i != j && vect[j].type != 3)
				vect[j].setSpeed(vect[i].GetPositionX(), vect[i].GetPositionY());
		}
	}

	for (int i = 0; i < vect.size(); i++)
	{
		vect[i].Update(deltaTime, playerPosX, playerPosY);
		if (vect[i].getHp() <= 0)
		{
			vect[i].dieAnimation(dieAnimation, false, sf::Vector2u(6, 1));
			if (vect[i].dieComplete())
			{
				int dieItemRate = rand();
				switch (dieItemRate % 2)
				{
				case 0:
					enemiesDied1SF.play();
					break;
				case 1:
					enemiesDied2SF.play();
					break;
				}
				int itemDropRate = vect[i].randItemRate() + dieItemRate;
				itemDropRate %= 300;
				switch (itemDropRate)
				{
				case 0: case 10: case 115: case 127:
					item.push_back(Item(ItemTexture, sf::Vector2u(1, 9), 0.3f, vect[i].GetPositionX(), vect[i].GetPositionY(), 0)); //Shoot 8 directions
					break;
				case 1:case 14: case 118: case 124:
					item.push_back(Item(ItemTexture, sf::Vector2u(1, 9), 0.3f, vect[i].GetPositionX(), vect[i].GetPositionY(), 1)); //Shoot rapidly
					break;
				case 2:case 18:
					item.push_back(Item(ItemTexture, sf::Vector2u(1, 9), 0.3f, vect[i].GetPositionX(), vect[i].GetPositionY(), 2)); //Clear all monster
					break;
				case 3:case 22: case 125: case 147:
					item.push_back(Item(ItemTexture, sf::Vector2u(1, 9), 0.3f, vect[i].GetPositionX(), vect[i].GetPositionY(), 3)); //Speed Boost
					break;
				case 4:case 34: case 199: case 170:
					item.push_back(Item(ItemTexture, sf::Vector2u(1, 9), 0.3f, vect[i].GetPositionX(), vect[i].GetPositionY(), 4)); //Shoot 3 directions
					break;
				case 5:
					item.push_back(Item(ItemTexture, sf::Vector2u(1, 9), 0.3f, vect[i].GetPositionX(), vect[i].GetPositionY(), 5)); //Life up
					break;
				case 99:
					item.push_back(Item(ItemTexture, sf::Vector2u(1, 9), 0.3f, vect[i].GetPositionX(), vect[i].GetPositionY(), 6)); //All in one
					break;
				case 111: case 11:
					item.push_back(Item(ItemTexture, sf::Vector2u(1, 9), 0.3f, vect[i].GetPositionX(), vect[i].GetPositionY(), 7)); //1 Gold Coin
					break;
				case 55:
					item.push_back(Item(ItemTexture, sf::Vector2u(1, 9), 0.3f, vect[i].GetPositionX(), vect[i].GetPositionY(), 8)); //5 Gold Coin
					break;
				}
				if (vect[i].type == 1)
				{
					scoreIngame += 50;
				}
				if (vect[i].type == 2)
				{
					scoreIngame += 70;
				}
				if (vect[i].type == 3)
				{
					scoreIngame += 45;
				}
				vect.erase(vect.begin() + i);
				enemyLeft--;
			}
		}
	}
}
void drawItem(vector<Item>& vect, sf::RenderWindow& window)
{
	for (int i = 0; i < vect.size(); i++)
	{
		vect[i].Draw(window);
	}
}
void itemCollider(vector<Item>& item, Player& player, vector<Enemies>& enemy, sf::Texture* bombItemAnimation, sf::Sound& itemCollectSF, sf::Sound& coffeeCollectSF, sf::Sound& coinCollectSF, sf::Sound& BombSoundEffectSF)
{
	if (!player.isAliveReturn())
	{
		player.setPlayerSpeed(85.0f);
		bulletDelayCount = 450;
		shotGunItemOff = true;
		allDirItemOff = true;
		effect1On = false;
		effect2On = false;
		effect3On = false;
	}
	for (int i = 0; i < item.size(); i++)
	{
		if (item[i].isTimeExcess())
		{
			item.erase(item.begin() + i);
			continue;
		}
		Collider playerCollision = player.GetCollider();
		if (item[i].GetCollider().itemColliderCheck(playerCollision) && player.isAliveReturn())
		{
			switch (item[i].whatRow())
			{
			case 0:			//ยิง8ทิศ
				allDirItemOff = false;
				allDirectionsFireClock.restart();
				itemCollectSF.play();
				break;
			case 1:			//ปืนกล
				bulletDelayCount = 145;
				rapidFireClock.restart();
				itemCollectSF.play();
				break;
			case 2:			//Clear all	
				enemy.erase(enemy.begin(), enemy.end());
				enemyLeft = 0;
				bombEffectClock.restart();
				enemySpawnDelay = 2500;
				effectRand = rand();
				BombSoundEffectSF.play();
				break;
			case 3:			//กาแฟ
				player.setPlayerSpeed(120.0f);
				coffeeClock.restart();
				coffeeCollectSF.play();
				break;
			case 4:			//Shotgun
				shotGunItemOff = false;
				shotGunFireClock.restart();
				itemCollectSF.play();
				break;
			case 5:			//Life-Up
				lifeLeft++;
				coffeeCollectSF.play();
				break;
			case 6:		//All in one
				bulletDelayCount = 145;
				rapidFireClock.restart();
				player.setPlayerSpeed(120.0f);
				coffeeClock.restart();
				shotGunItemOff = false;
				shotGunFireClock.restart();
				scoreIngame += 99;
				coffeeCollectSF.play();
				break;
			case 7:
				scoreIngame += 111;
				coinCollectSF.play();
				break;
			case 8:
				scoreIngame += 555;
				coinCollectSF.play();
				break;
			}
			item.erase(item.begin() + i);
		}
	}
	if (coffeeClock.getElapsedTime().asSeconds() > 7)
	{
		player.setPlayerSpeed(85.0f);
	}
	if (rapidFireClock.getElapsedTime().asSeconds() > 7)
	{
		bulletDelayCount = 450;
	}
	if (shotGunFireClock.getElapsedTime().asSeconds() > 7)
	{
		shotGunItemOff = true;
	}
	if (allDirectionsFireClock.getElapsedTime().asSeconds() > 7)
	{
		allDirItemOff = true;
	}
	if (bombEffectClock.getElapsedTime().asMilliseconds() < 550)
	{
		switch (effectRand % 3)
		{
		case 0:
			effect1On = true;
			break;
		case 1:
			effect2On = true;
			break;
		case 2:
			effect3On = true;
			break;
		}
	}
	else
	{
		effect1On = false;
		effect2On = false;
		effect3On = false;
	}
}
void drawEnemy(vector<Enemies>& enemy, sf::RenderWindow& window)
{
	for (Enemies& enemy1 : enemy)
	{
		enemy1.Draw(window);
	}
}
void showText(int x, int y, string word, sf::RenderWindow& window, sf::Font* font, int charSize)
{
	sf::Text text;
	text.setFont(*font);
	text.setPosition(x, y);
	text.setString(word);
	text.setCharacterSize(charSize);
	window.draw(text);
}
void customShowText(float x, float y, string word, sf::RenderWindow& window, sf::Font* font, int charSize, sf::Color textColor, sf::Color outLineColor, int thickness)
{
	sf::Text text;
	text.setFont(*font);
	text.setPosition(x, y);
	text.setFillColor(textColor);
	text.setOutlineColor(outLineColor);
	text.setOutlineThickness(thickness);
	text.setString(word);
	text.setCharacterSize(charSize);
	window.draw(text);
}
void createBullet(vector<Bullet>& bullet, float playerPosX, float playerPosY, int direction, sf::Texture* bulletTexture)
{
	switch (direction)
	{
	case(0):
	{
		bullet.push_back(Bullet(bulletTexture, sf::Vector2u(1, 4), 0.3f, 250.0f, 0, playerPosX, playerPosY));
		break;
	}
	case(1):
	{
		bullet.push_back(Bullet(bulletTexture, sf::Vector2u(1, 4), 0.3f, 250.0f, 1, playerPosX, playerPosY));
		break;
	}
	case(2):
	{
		bullet.push_back(Bullet(bulletTexture, sf::Vector2u(1, 4), 0.3f, 250.0f, 2, playerPosX, playerPosY));
		break;
	}
	case(3):
	{
		bullet.push_back(Bullet(bulletTexture, sf::Vector2u(1, 4), 0.3f, 250.0f, 3, playerPosX, playerPosY));
		break;
	}
	case(4):
	{
		bullet.push_back(Bullet(bulletTexture, sf::Vector2u(1, 4), 0.3f, 250.0f, 4, playerPosX, playerPosY));
		break;
	}
	case(5):
	{
		bullet.push_back(Bullet(bulletTexture, sf::Vector2u(1, 4), 0.3f, 250.0f, 5, playerPosX, playerPosY));
		break;
	}
	case(6):
	{
		bullet.push_back(Bullet(bulletTexture, sf::Vector2u(1, 4), 0.3f, 250.0f, 6, playerPosX, playerPosY));
		break;
	}
	case(7):
	{
		bullet.push_back(Bullet(bulletTexture, sf::Vector2u(1, 4), 0.3f, 250.0f, 7, playerPosX, playerPosY));
		break;
	}
	case(8):
	{
		bullet.push_back(Bullet(bulletTexture, sf::Vector2u(1, 4), 0.3f, 250.0f, 8, playerPosX, playerPosY));
		break;
	}
	case(9):
	{
		bullet.push_back(Bullet(bulletTexture, sf::Vector2u(1, 4), 0.3f, 250.0f, 9, playerPosX, playerPosY));
		break;
	}
	case(10):
	{
		bullet.push_back(Bullet(bulletTexture, sf::Vector2u(1, 4), 0.3f, 250.0f, 10, playerPosX, playerPosY));
		break;
	}
	case(11):
	{
		bullet.push_back(Bullet(bulletTexture, sf::Vector2u(1, 4), 0.3f, 250.0f, 11, playerPosX, playerPosY));
		break;
	}
	case(12):
	{
		bullet.push_back(Bullet(bulletTexture, sf::Vector2u(1, 4), 0.3f, 250.0f, 12, playerPosX, playerPosY));
		break;
	}
	case(13):
	{
		bullet.push_back(Bullet(bulletTexture, sf::Vector2u(1, 4), 0.3f, 250.0f, 13, playerPosX, playerPosY));
		break;
	}
	case(14):
	{
		bullet.push_back(Bullet(bulletTexture, sf::Vector2u(1, 4), 0.3f, 250.0f, 14, playerPosX, playerPosY));
		break;
	}
	case(15):
	{
		bullet.push_back(Bullet(bulletTexture, sf::Vector2u(1, 4), 0.3f, 250.0f, 15, playerPosX, playerPosY));
		break;
	}
	case(16):
	{
		bullet.push_back(Bullet(bulletTexture, sf::Vector2u(1, 4), 0.3f, 250.0f, 16, playerPosX, playerPosY));
		break;
	}
	case(17):
	{
		bullet.push_back(Bullet(bulletTexture, sf::Vector2u(1, 4), 0.3f, 250.0f, 17, playerPosX, playerPosY));
		break;
	}
	case(18):
	{
		bullet.push_back(Bullet(bulletTexture, sf::Vector2u(1, 4), 0.3f, 250.0f, 18, playerPosX, playerPosY));
		break;
	}
	case(19):
	{
		bullet.push_back(Bullet(bulletTexture, sf::Vector2u(1, 4), 0.3f, 250.0f, 19, playerPosX, playerPosY));
		break;
	}
	case(20):
	{
		bullet.push_back(Bullet(bulletTexture, sf::Vector2u(1, 4), 0.3f, 250.0f, 20, playerPosX, playerPosY));
		break;
	}
	case(21):
	{
		bullet.push_back(Bullet(bulletTexture, sf::Vector2u(1, 4), 0.3f, 250.0f, 21, playerPosX, playerPosY));
		break;
	}
	case(22):
	{
		bullet.push_back(Bullet(bulletTexture, sf::Vector2u(1, 4), 0.3f, 250.0f, 22, playerPosX, playerPosY));
		break;
	}
	case(23):
	{
		bullet.push_back(Bullet(bulletTexture, sf::Vector2u(1, 4), 0.3f, 250.0f, 23, playerPosX, playerPosY));
		break;
	}
	}
}
void updateBullet(vector<Bullet>& vect, float deltaTime)
{
	for (Bullet& bullet : vect)
	{

		bullet.Update(deltaTime);
	}
}
void drawBullet(vector<Bullet>& vect, sf::RenderWindow& window)
{
	for (Bullet& bullet : vect)
	{
		bullet.Draw(window);
	}
}
void bulletCollider(vector<Bullet>& vect, vector<Platform>& wall, vector<Enemies>& enemy, vector<Platform>& extraWalls)
{
	for (int i = 0; i < vect.size(); i++)
	{
		Collider bulletCollision = vect[i].GetCollider();
		for (Platform& wall : wall)
		{
			if (wall.GetCollider().CheckCollider(bulletCollision))
			{
				vect[i].bulletCheck(true);
			}
		}
		for (Platform& extraWalls : extraWalls)
		{
			if (extraWalls.GetCollider().CheckCollider(bulletCollision))
			{
				vect[i].bulletCheck(true);
			}
		}

		for (Enemies& enemy : enemy)
		{
			if (enemy.GetCollider().itemColliderCheck(bulletCollision) && enemy.isThisAlive())
			{
				vect[i].bulletCheck(true);
				enemy.setHp(enemy.getHp() - 1);

			}
		}
		if (vect[i].isDestroy())
		{
			vect.erase(vect.begin() + i);
		}
	}

}
void createBombEffect1(vector <BombEffect>& effect, sf::Texture* bombItemAnimation)
{
	effect.push_back(BombEffect(bombItemAnimation, sf::Vector2u(5, 1), 555, 80));
	effect.push_back(BombEffect(bombItemAnimation, sf::Vector2u(5, 1), 375, 389));
	effect.push_back(BombEffect(bombItemAnimation, sf::Vector2u(5, 1), 669, 400));
	effect.push_back(BombEffect(bombItemAnimation, sf::Vector2u(5, 1), 469, 300));
	effect.push_back(BombEffect(bombItemAnimation, sf::Vector2u(5, 1), 299, 600));
	effect.push_back(BombEffect(bombItemAnimation, sf::Vector2u(5, 1), 500, 545));
	effect.push_back(BombEffect(bombItemAnimation, sf::Vector2u(5, 1), 319, 109));
	effect.push_back(BombEffect(bombItemAnimation, sf::Vector2u(5, 1), 699, 150));
	effect.push_back(BombEffect(bombItemAnimation, sf::Vector2u(5, 1), 769, 620));
	effect.push_back(BombEffect(bombItemAnimation, sf::Vector2u(5, 1), 750, 256));
}
void createBombEffect2(vector <BombEffect>& effect, sf::Texture* bombItemAnimation)
{
	effect.push_back(BombEffect(bombItemAnimation, sf::Vector2u(5, 1), 379, 201));
	effect.push_back(BombEffect(bombItemAnimation, sf::Vector2u(5, 1), 460, 130));
	effect.push_back(BombEffect(bombItemAnimation, sf::Vector2u(5, 1), 712, 209));
	effect.push_back(BombEffect(bombItemAnimation, sf::Vector2u(5, 1), 673, 383));
	effect.push_back(BombEffect(bombItemAnimation, sf::Vector2u(5, 1), 748, 538));
	effect.push_back(BombEffect(bombItemAnimation, sf::Vector2u(5, 1), 500, 545));
	effect.push_back(BombEffect(bombItemAnimation, sf::Vector2u(5, 1), 322, 610));
	effect.push_back(BombEffect(bombItemAnimation, sf::Vector2u(5, 1), 445, 450));
	effect.push_back(BombEffect(bombItemAnimation, sf::Vector2u(5, 1), 444, 333));
	effect.push_back(BombEffect(bombItemAnimation, sf::Vector2u(5, 1), 604, 298));
}
void createBombEffect3(vector <BombEffect>& effect, sf::Texture* bombItemAnimation)
{
	effect.push_back(BombEffect(bombItemAnimation, sf::Vector2u(5, 1), 370, 291));
	effect.push_back(BombEffect(bombItemAnimation, sf::Vector2u(5, 1), 267, 386));
	effect.push_back(BombEffect(bombItemAnimation, sf::Vector2u(5, 1), 593, 622));
	effect.push_back(BombEffect(bombItemAnimation, sf::Vector2u(5, 1), 774, 468));
	effect.push_back(BombEffect(bombItemAnimation, sf::Vector2u(5, 1), 770, 351));
	effect.push_back(BombEffect(bombItemAnimation, sf::Vector2u(5, 1), 619, 423));
	effect.push_back(BombEffect(bombItemAnimation, sf::Vector2u(5, 1), 764, 240));
	effect.push_back(BombEffect(bombItemAnimation, sf::Vector2u(5, 1), 470, 208));
	effect.push_back(BombEffect(bombItemAnimation, sf::Vector2u(5, 1), 577, 126));
	effect.push_back(BombEffect(bombItemAnimation, sf::Vector2u(5, 1), 472, 380));
}
void updateBombEffect(vector <BombEffect>& effect, float deltaTime)
{
	for (BombEffect& effect : effect)
	{
		effect.Update(deltaTime);
	}
}
void drawBombEffect(vector <BombEffect>& effect, sf::RenderWindow& window)
{
	for (BombEffect& effect : effect)
	{
		effect.Draw(window);
	}
}