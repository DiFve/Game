#define _CRT_SECURE_NO_WARNINGS
#include <SFML/Graphics.hpp>
#include <iostream>
#include<string>
#include<stdio.h>
#include<algorithm>
#include<utility>
#include<vector>
#include<Windows.h>
#include"Player.h" 
#include"Platform.h"
#include"Item.h"
#include"Enemies.h"
#include"Bullet.h"
#include "BombEffect.h"
using namespace std;
void showHighScore(int x,int y,string word, sf::RenderWindow& window, sf::Font* font);
void createEnemy(vector<Enemies>& enemy, int randSpawn, sf::Texture* Enemies1Texture);
void updateEnemy(vector<Enemies>& enemy, float deltaTime, float playerPosX, float playerPosY, sf::Texture* dieAnimation, sf::Texture* ItemTexture, vector<Item>& item);
void drawEnemy(vector<Enemies>& enemy, sf::RenderWindow& window);
void bulletCollider(vector<Bullet>& vect, vector<Platform>& wall, vector<Enemies>& enemy);
void enemyCollider(vector<Enemies>& enemy, vector<Platform>& wall);
void createBullet(vector<Bullet>& bullet, float playerPosX, float playerPosY, int direction, sf::Texture* bulletTexture);
void updateBullet(vector<Bullet>& vect, float deltaTime);
void drawBullet(vector<Bullet>& vect, sf::RenderWindow& window);
void drawItem(vector<Item>& vect, sf::RenderWindow& window);
void updateItem(vector<Item>& item, float deltaTime);
void itemCollider(vector<Item>& item, Player& player, vector<Enemies>& enemy, sf::Texture* bombItemAnimation);
void createBombEffect1(vector <BombEffect>& effect, sf::Texture* bombItemAnimation);
void createBombEffect2(vector <BombEffect>& effect, sf::Texture* bombItemAnimation);
void createBombEffect3(vector <BombEffect>& effect, sf::Texture* bombItemAnimation);
void updateBombEffect(vector <BombEffect>& effect, float deltaTime);
void drawBombEffect(vector <BombEffect>& effect, sf::RenderWindow& window);

int bulletDelayCount=450;
bool allDirItemOff = true;
bool shotGunItemOff = true;
int enemySpawnDelay = 1000;
bool effect1On = false;
bool effect2On = false;
bool effect3On = false;
int main()
{
	srand(time(NULL));
	sf::Font font;
	sf::Clock enemySpawnClock;
	sf::Clock bulletClock;
	vector <Enemies> enemies1;
	sf::RenderWindow window(sf::VideoMode(1080, 720), "Game Test!", sf::Style::Close | sf::Style::Resize);
	sf::Texture RightSide;
	sf::Texture Enemies1Texture;
	sf::Texture BG1;
	sf::Texture bulletTexture;
	sf::Texture enemyDieAnimation;
	sf::Texture ItemTexture;
	sf::Texture  bombItemAnimation;
	//------------HIGHSCORE------------------
	font.loadFromFile("Blockbusted.ttf");
	string nameTest="dd";
	int scoreTest=1;
	//cin >> nameTest >> scoreTest;
	
	vector <pair<int, string>> userScore;
	char temp[255];
	int score[6];
	string name[6];
	FILE* fp;
	fp = fopen("./Score.txt", "r");
	for (int i = 0; i < 5; i++)
	{
		fscanf(fp, "%s", temp);
		name[i] = temp;
		fscanf(fp, "%d", &score[i]);
		userScore.push_back(make_pair(score[i], name[i]));
	}
	name[5] = nameTest;
	score[5] = scoreTest;
	userScore.push_back(make_pair(score[5], name[5]));
	sort(userScore.begin(), userScore.end());
	fclose(fp);
	fopen("./Score.txt", "w");
	for (int i = 5; i >= 1; i--)
	{
		strcpy(temp,userScore[i].second.c_str());
		fprintf(fp, "%s %d\n",temp, userScore[i].first);
		//cout << userScore[i].second << " " << userScore[i].first << "\n";
	}
	fclose(fp);
	
	//------------HIGHSCORE------------------
	ItemTexture.loadFromFile("res/img/Item.png");
	BG1.loadFromFile("res/img/BG1.png");
	bombItemAnimation.loadFromFile("res/img/BombEffect.png");
	sf::RectangleShape BackGround(sf::Vector2f(640.0f, 640.0f));
	BackGround.setOrigin(320.0f,320.0f);
	BackGround.setPosition(540.0f, 360.0f);
	BackGround.setTexture(&BG1);
	if (!RightSide.loadFromFile("res/img/player.png")) 
	{
		cout << "Load failed" << endl;
	}

	Player player(&RightSide, sf::Vector2u(4,4),0.3f,85.0f);   
	enemyDieAnimation.loadFromFile("res/img/EnemyDieAnimation.png");
	Enemies1Texture.loadFromFile("res/img/Enemies1_15px.png");
	vector <Bullet> bullet;
	vector <Item> itemDrop;
	vector <BombEffect> effect1;
	vector <BombEffect> effect2;
	vector <BombEffect> effect3;
	createBombEffect1(effect1,&bombItemAnimation);
	createBombEffect2(effect2, &bombItemAnimation);
	createBombEffect3(effect3, &bombItemAnimation);
	bulletTexture.loadFromFile("res/img/bullet.png");
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
	float deltaTime = 0.0f;
	sf::Clock clock;
	sf::Clock clockenemyMove;
	
	while (window.isOpen())
	{
		if (deltaTime > 1.0f / 150.0f)
		{
			deltaTime = 1.0f / 150.0f;
		}
		int enemyMove = clockenemyMove.getElapsedTime().asMilliseconds();
		float enemySpawnTime = enemySpawnClock.getElapsedTime().asMilliseconds();
		float bulletDelay = bulletClock.getElapsedTime().asMilliseconds();
		
		if (enemySpawnTime>enemySpawnDelay)
		{
			for (int i=0;i<2;i++)
			{
				int randEnemy = rand();
				createEnemy(enemies1,randEnemy,&Enemies1Texture);
			}
				
			
			enemySpawnDelay = 1000;
			enemySpawnClock.restart();
		}
		deltaTime = clock.restart().asSeconds();
		sf::Event evnt;
		
		while (window.pollEvent(evnt))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				window.close();
			}
			if (evnt.type == evnt.Closed)
			{
				window.close();
			}
		}
		
		if (bulletDelay>bulletDelayCount && allDirItemOff && shotGunItemOff)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)&& sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				createBullet(bullet, player.Getposition().x, player.Getposition().y, 4, &bulletTexture);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				createBullet(bullet, player.Getposition().x, player.Getposition().y, 5, &bulletTexture);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				createBullet(bullet, player.Getposition().x, player.Getposition().y, 6, &bulletTexture);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				createBullet(bullet, player.Getposition().x, player.Getposition().y, 7, &bulletTexture);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				createBullet(bullet, player.Getposition().x, player.Getposition().y,0,&bulletTexture);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				createBullet(bullet, player.Getposition().x, player.Getposition().y, 1, &bulletTexture);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				createBullet(bullet, player.Getposition().x, player.Getposition().y, 2, &bulletTexture);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				createBullet(bullet, player.Getposition().x, player.Getposition().y, 3, &bulletTexture);
			}
			
			bulletClock.restart();
		}
		if (bulletDelay > bulletDelayCount && allDirItemOff==false)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
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
		if (bulletDelay > bulletDelayCount && shotGunItemOff == false)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				createBullet(bullet, player.Getposition().x, player.Getposition().y, 5, &bulletTexture);
				createBullet(bullet, player.Getposition().x, player.Getposition().y, 10, &bulletTexture);
				createBullet(bullet, player.Getposition().x, player.Getposition().y, 11, &bulletTexture);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				createBullet(bullet, player.Getposition().x, player.Getposition().y, 4, &bulletTexture);
				createBullet(bullet, player.Getposition().x, player.Getposition().y, 22, &bulletTexture);
				createBullet(bullet, player.Getposition().x, player.Getposition().y, 23, &bulletTexture);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				createBullet(bullet, player.Getposition().x, player.Getposition().y, 7, &bulletTexture);
				createBullet(bullet, player.Getposition().x, player.Getposition().y, 18, &bulletTexture);
				createBullet(bullet, player.Getposition().x, player.Getposition().y, 19, &bulletTexture);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				createBullet(bullet, player.Getposition().x, player.Getposition().y, 6, &bulletTexture);
				createBullet(bullet, player.Getposition().x, player.Getposition().y, 14, &bulletTexture);
				createBullet(bullet, player.Getposition().x, player.Getposition().y, 15, &bulletTexture);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				createBullet(bullet, player.Getposition().x, player.Getposition().y, 2, &bulletTexture);
				createBullet(bullet, player.Getposition().x, player.Getposition().y, 8, &bulletTexture);
				createBullet(bullet, player.Getposition().x, player.Getposition().y, 9, &bulletTexture);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				createBullet(bullet, player.Getposition().x, player.Getposition().y, 1, &bulletTexture);
				createBullet(bullet, player.Getposition().x, player.Getposition().y, 12, &bulletTexture);
				createBullet(bullet, player.Getposition().x, player.Getposition().y, 13, &bulletTexture);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				createBullet(bullet, player.Getposition().x, player.Getposition().y, 0, &bulletTexture);
				createBullet(bullet, player.Getposition().x, player.Getposition().y, 20, &bulletTexture);
				createBullet(bullet, player.Getposition().x, player.Getposition().y, 21, &bulletTexture);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				createBullet(bullet, player.Getposition().x, player.Getposition().y, 3, &bulletTexture);
				createBullet(bullet, player.Getposition().x, player.Getposition().y, 16, &bulletTexture);
				createBullet(bullet, player.Getposition().x, player.Getposition().y, 17, &bulletTexture);
			}

			bulletClock.restart();
		}
		updateBullet(bullet, deltaTime);
		player.Update(deltaTime);
	
		updateEnemy(enemies1, deltaTime, player.Getposition().x, player.Getposition().y,&enemyDieAnimation,&ItemTexture,itemDrop);
		updateItem(itemDrop,deltaTime);
		updateBombEffect(effect1, deltaTime);
		updateBombEffect(effect2, deltaTime);
		updateBombEffect(effect3,deltaTime);

		Collider playerCollison = player.GetCollider();
		for (int i=0;i<wall.size();i++)
		{
			wall[i].GetCollider().CheckCollider(playerCollison);
		}

		enemyCollider(enemies1,wall);
		bulletCollider(bullet,wall,enemies1);
		itemCollider(itemDrop,player,enemies1,&bombItemAnimation);

		window.clear();
		window.draw(BackGround);
		//---------------SHOWHIGHSCORE-------------
		
		showHighScore(10, 10,"HIGHSCORE", window,&font);
		showHighScore(10, 40, userScore[5].second, window, &font);
		showHighScore(10, 70, userScore[4].second, window, &font);
		showHighScore(10, 100, userScore[3].second, window, &font);
		showHighScore(10, 130, userScore[2].second, window, &font);
		showHighScore(10, 160, userScore[1].second, window, &font);
		showHighScore(100, 40, to_string(userScore[5].first), window, &font);
		showHighScore(100, 70, to_string(userScore[4].first), window, &font);
		showHighScore(100, 100, to_string(userScore[3].first), window, &font);
		showHighScore(100, 130, to_string(userScore[2].first), window, &font);
		showHighScore(100, 160, to_string(userScore[1].first), window,&font);
		
		//---------------SHOWHIGHSCORE-------------
		drawBullet(bullet,window);
		drawEnemy(enemies1,window);
		drawItem(itemDrop,window);
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
		player.Draw(window);
		window.display();
		
	}
	
	return 0;
}
sf::Clock coffeeClock;
sf::Clock rapidFireClock;
sf::Clock allDirectionsFireClock;
sf::Clock shotGunFireClock;
sf::Clock bombEffectClock;
int effectRand=-1;
void enemyCollider(vector<Enemies> &enemy,vector<Platform> &wall)
{
	for (Enemies& enemy : enemy)
	{
		Collider enemy1Collision = enemy.GetCollider();
		for (Platform& wall : wall)
		{
			wall.GetCollider().CheckCollider(enemy1Collision);
		}
	}
}
void createEnemy(vector<Enemies> &enemy,int randSpawn,sf::Texture *Enemies1Texture)
{
	int itemDropRate = rand();
	switch (randSpawn%12)
	{
		case(0):
		{
			enemy.push_back(Enemies(Enemies1Texture, sf::Vector2u(2, 1), 0.3f, 40.0f, 241.85, 337.2,2,(itemDropRate*randSpawn)));
			break;
		}
		case(1):
		{
			enemy.push_back(Enemies(Enemies1Texture, sf::Vector2u(2, 1), 0.3f, 40.0f, 241.85, 374.458, 2, (itemDropRate * randSpawn)));
			break;
		}
		case(2):
		{
			enemy.push_back(Enemies(Enemies1Texture, sf::Vector2u(2, 1), 0.3f, 40.0f, 241.285, 422.5, 2, (itemDropRate * randSpawn)));
			break;
		}
		case(3):
		{
			enemy.push_back(Enemies(Enemies1Texture, sf::Vector2u(2, 1), 0.3f, 40.0f, 517.608, 58, 2, (itemDropRate * randSpawn)));
			break;
		}
		case(4):
		{
			enemy.push_back(Enemies(Enemies1Texture, sf::Vector2u(2, 1), 0.3f, 40.0f, 559.379, 58, 2, (itemDropRate * randSpawn)));
			break;
		}
		case(5):
		{
			enemy.push_back(Enemies(Enemies1Texture, sf::Vector2u(2, 1), 0.3f, 40.0f, 602.5, 58, 2, (itemDropRate * randSpawn)));
			break;
		}
		case(6):
		{
			enemy.push_back(Enemies(Enemies1Texture, sf::Vector2u(2, 1), 0.3f, 40.0f, 842, 337.5, 2, (itemDropRate * randSpawn)));
			break;
		}
		case(7):
		{
			enemy.push_back(Enemies(Enemies1Texture, sf::Vector2u(2, 1), 0.3f, 40.0f, 842, 374.147, 2, (itemDropRate * randSpawn)));
			break;
		}
		case(8):
		{
			enemy.push_back(Enemies(Enemies1Texture, sf::Vector2u(2, 1), 0.3f, 40.0f, 842, 422.5, 2, (itemDropRate * randSpawn)));
			break;
		}
		case(9):
		{
			enemy.push_back(Enemies(Enemies1Texture, sf::Vector2u(2, 1), 0.3f, 40.0f, 602.5, 663, 1, (itemDropRate * randSpawn)));
			break;
		}
		case(10):
		{
			enemy.push_back(Enemies(Enemies1Texture, sf::Vector2u(2, 1), 0.3f, 40.0f, 554.865, 663, 1, (itemDropRate * randSpawn)));
			break;
		}
		case(11):
		{
			enemy.push_back(Enemies(Enemies1Texture, sf::Vector2u(2, 1), 0.3f, 40.0f, 517.5, 663, 1, (itemDropRate * randSpawn)));
			break;
		}
	}
	

}
void updateItem(vector<Item> &item,float deltaTime)
{
	for (Item& item : item)
	{
		item.Update(deltaTime);
	}
}
void updateEnemy(vector<Enemies>& vect,float deltaTime, float playerPosX, float playerPosY,sf::Texture* dieAnimation,sf::Texture* ItemTexture,vector<Item>& item)
{	
	for (int i=0;i<vect.size();i++)
	{
		
		vect[i].Update(deltaTime,playerPosX,playerPosY);
		if (vect[i].getHp()<=0)
		{
			vect[i].dieAnimation(dieAnimation,false,sf::Vector2u(6,1));
			if (vect[i].dieComplete())
			{
				int dieItemRate = rand();
				int itemDropRate = vect[i].randItemRate()+dieItemRate;
				itemDropRate %= 200;
				//cout << itemDropRate <<endl;
				switch (itemDropRate)
				{
				case 0: case 10: case 115: case 127:
					item.push_back(Item(ItemTexture, sf::Vector2u(1, 7), 0.3f, vect[i].GetPositionX(), vect[i].GetPositionY(), 0)); //Shoot 8 directions
					break;
				case 1:case 14: case 118: case 124:
					item.push_back(Item(ItemTexture, sf::Vector2u(1, 7), 0.3f, vect[i].GetPositionX(), vect[i].GetPositionY(), 1)); //Shoot rapidly
					break;
				case 2:case 18: case 132: case 135:
					item.push_back(Item(ItemTexture, sf::Vector2u(1, 7), 0.3f, vect[i].GetPositionX(), vect[i].GetPositionY(), 2)); //Clear all monster
					break;
				case 3:case 22: case 125: case 147:
					item.push_back(Item(ItemTexture, sf::Vector2u(1, 7), 0.3f, vect[i].GetPositionX(), vect[i].GetPositionY(), 3)); //Speed Boost
					break;
				case 4:case 34: case 199: case 170:
					item.push_back(Item(ItemTexture, sf::Vector2u(1, 7), 0.3f, vect[i].GetPositionX(), vect[i].GetPositionY(), 4)); //Shoot 3 directions
					break;
				case 5:
					item.push_back(Item(ItemTexture, sf::Vector2u(1, 7), 0.3f, vect[i].GetPositionX(), vect[i].GetPositionY(), 5)); //Life up
					break;
				case 99:
					item.push_back(Item(ItemTexture, sf::Vector2u(1, 7), 0.3f, vect[i].GetPositionX(), vect[i].GetPositionY(), 6)); //All in one
					break;
				}
				vect.erase(vect.begin()+i);
			}
		}
	}
}
void drawItem(vector<Item>& vect,sf::RenderWindow& window)
{
	for (int i=0;i<vect.size();i++)
	{
		vect[i].Draw(window);
	}
}
void itemCollider(vector<Item> &item,Player &player, vector<Enemies> &enemy, sf::Texture* bombItemAnimation)
{
	for (int i=0;i<item.size();i++)
	{
		if (item[i].isTimeExcess())
		{
			item.erase(item.begin() + i);
			continue;
		}
		Collider playerCollision = player.GetCollider();
		if (item[i].GetCollider().itemColliderCheck(playerCollision))
		{
			//cout << item[i].whatRow() << endl;
			switch (item[i].whatRow())
			{
			case 0:			//ยิง8ทิศ
				allDirItemOff = false;
				allDirectionsFireClock.restart();
				break;
			case 1:			//ปืนกล
				bulletDelayCount = 145;
				rapidFireClock.restart();
				break;
			case 2:			//Clear all	
				enemy.erase(enemy.begin(),enemy.end());
				bombEffectClock.restart();
				enemySpawnDelay = 2500;
				effectRand = rand();
				break;
			case 3:			//กาแฟ
				player.setPlayerSpeed(120.0f);
				coffeeClock.restart();
				break;
			case 4:			//Shotgun
				shotGunItemOff = false;
				shotGunFireClock.restart();
				break;
			case 6:		//All in one
				bulletDelayCount = 145;
				rapidFireClock.restart();
				player.setPlayerSpeed(120.0f);
				coffeeClock.restart();
				shotGunItemOff = false;
				shotGunFireClock.restart();
				break;
			}
			item.erase(item.begin() + i);
		}
	}
	if (coffeeClock.getElapsedTime().asSeconds() > 12)
	{
		player.setPlayerSpeed(85.0f);
	}
	if (rapidFireClock.getElapsedTime().asSeconds()>12)
	{
		bulletDelayCount = 450;
	}
	if (shotGunFireClock.getElapsedTime().asSeconds() > 12)
	{
		shotGunItemOff = true;
	}
	if (allDirectionsFireClock.getElapsedTime().asSeconds() > 7)
	{
		allDirItemOff = true;
	}
	if (bombEffectClock.getElapsedTime().asMilliseconds() < 550)
	{
		switch (effectRand%3)
		{
		case 0:
			effect1On = true;
			cout << "1" << endl;
			break;
		case 1:
			effect2On = true;
			cout << "2" << endl;
			break;
		case 2:
			effect3On = true;
			cout << "3" << endl;
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
void drawEnemy(vector<Enemies>& enemy,sf::RenderWindow& window)
{
	for(Enemies &enemy1 : enemy)
	{
		enemy1.Draw(window);
	}
}
void showHighScore(int x,int y,string word, sf::RenderWindow& window,sf::Font* font)
{
	sf::Text text;
	text.setFont(*font);
	text.setPosition(x, y);
	text.setString(word);
	text.setCharacterSize(32);
	window.draw(text);
}
void createBullet(vector<Bullet>& bullet,float playerPosX, float playerPosY, int direction,sf::Texture *bulletTexture)
{
	switch (direction)
	{
		case(0):
		{
			bullet.push_back(Bullet(bulletTexture, sf::Vector2u(1, 4),0.3f,250.0f,0,playerPosX,playerPosY));
			break;
		}
		case(1):
		{
			bullet.push_back(Bullet(bulletTexture, sf::Vector2u(1, 4), 0.3f, 250.0f, 1,playerPosX, playerPosY));
			break;
		}
		case(2):
		{
			bullet.push_back(Bullet(bulletTexture, sf::Vector2u(1, 4), 0.3f, 250.0f, 2,playerPosX, playerPosY));
			break;
		}
		case(3):
		{
			bullet.push_back(Bullet(bulletTexture, sf::Vector2u(1, 4), 0.3f, 250.0f, 3,playerPosX, playerPosY));
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
void updateBullet(vector<Bullet>& vect,float deltaTime)
{
	for (Bullet& bullet : vect)
	{

		bullet.Update(deltaTime);
	}
}
void drawBullet(vector<Bullet>& vect,sf::RenderWindow& window)
{
	for (Bullet& bullet : vect)
	{
		bullet.Draw(window);
	}
}
void bulletCollider(vector<Bullet>& vect, vector<Platform>& wall,vector<Enemies>& enemy)
{
	for (int i=0;i<vect.size();i++)
	{
		Collider bulletCollision = vect[i].GetCollider();
		for (Platform& wall : wall)
		{
			if (wall.GetCollider().CheckCollider(bulletCollision))
			{
				vect[i].bulletCheck(true);
			}
		}
	
		for (Enemies& enemy : enemy)
		{		
			if (enemy.GetCollider().itemColliderCheck(bulletCollision) && enemy.isThisAlive())
			{
				vect[i].bulletCheck(true);
				enemy.setHp(enemy.getHp()-1);
				
			}
		}
		if (vect[i].isDestroy())
		{
			vect.erase(vect.begin()+i);
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