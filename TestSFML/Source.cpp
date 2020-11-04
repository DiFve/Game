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
		
		int enemyMove = clockenemyMove.getElapsedTime().asMilliseconds();
		float enemySpawnTime = enemySpawnClock.getElapsedTime().asMilliseconds();
		float bulletDelay = bulletClock.getElapsedTime().asMilliseconds();
		int randEnemy = rand();
		if (enemySpawnTime>2500)
		{
			createEnemy(enemies1,randEnemy,&Enemies1Texture);
			enemySpawnClock.restart();
		}
		deltaTime = clock.restart().asSeconds();
		sf::Event evnt;
		/*if (deltaTime > 1.0f / 150.0f)
		{
			deltaTime = 1.0f / 150.0f;
		}*/
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
		
		if (bulletDelay>450)
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

		player.Update(deltaTime);
		updateBullet(bullet,deltaTime);
		
		//cout << player.Getposition().x << " "<<player.Getposition().y << "\n";
		updateEnemy(enemies1, deltaTime, player.Getposition().x, player.Getposition().y,&enemyDieAnimation,&ItemTexture,itemDrop);
		updateItem(itemDrop,deltaTime);
		Collider playerCollison = player.GetCollider();
		
		for (int i=0;i<wall.size();i++)
		{
			wall[i].GetCollider().CheckCollider(playerCollison);
		}

		enemyCollider(enemies1,wall);
		bulletCollider(bullet,wall,enemies1);

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
		player.Draw(window);
		window.display();
		
	}
	
	return 0;
}
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
	randSpawn %= 12;
	switch (randSpawn)
	{
		case(0):
		{
			enemy.push_back(Enemies(Enemies1Texture, sf::Vector2u(2, 1), 0.3f, 40.0f, 241.85, 337.2,2));
			break;
		}
		case(1):
		{
			enemy.push_back(Enemies(Enemies1Texture, sf::Vector2u(2, 1), 0.3f, 40.0f, 241.85, 374.458, 2));
			break;
		}
		case(2):
		{
			enemy.push_back(Enemies(Enemies1Texture, sf::Vector2u(2, 1), 0.3f, 40.0f, 241.285, 422.5, 2));
			break;
		}
		case(3):
		{
			enemy.push_back(Enemies(Enemies1Texture, sf::Vector2u(2, 1), 0.3f, 40.0f, 517.608, 58, 2));
			break;
		}
		case(4):
		{
			enemy.push_back(Enemies(Enemies1Texture, sf::Vector2u(2, 1), 0.3f, 40.0f, 559.379, 58, 2));
			break;
		}
		case(5):
		{
			enemy.push_back(Enemies(Enemies1Texture, sf::Vector2u(2, 1), 0.3f, 40.0f, 602.5, 58, 2));
			break;
		}
		case(6):
		{
			enemy.push_back(Enemies(Enemies1Texture, sf::Vector2u(2, 1), 0.3f, 40.0f, 842, 337.5, 2));
			break;
		}
		case(7):
		{
			enemy.push_back(Enemies(Enemies1Texture, sf::Vector2u(2, 1), 0.3f, 40.0f, 842, 374.147, 2));
			break;
		}
		case(8):
		{
			enemy.push_back(Enemies(Enemies1Texture, sf::Vector2u(2, 1), 0.3f, 40.0f, 842, 422.5, 2));
			break;
		}
		case(9):
		{
			enemy.push_back(Enemies(Enemies1Texture, sf::Vector2u(2, 1), 0.3f, 40.0f, 602.5, 663, 1));
			break;
		}
		case(10):
		{
			enemy.push_back(Enemies(Enemies1Texture, sf::Vector2u(2, 1), 0.3f, 40.0f, 554.865, 663, 1));
			break;
		}
		case(11):
		{
			enemy.push_back(Enemies(Enemies1Texture, sf::Vector2u(2, 1), 0.3f, 40.0f, 517.5, 663, 1));
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
			vect[i].dieAnimation(dieAnimation,false);
			if (vect[i].dieComplete())
			{
				int itemDropRate = rand();
				itemDropRate %= 100;
				cout << itemDropRate<<endl;
				switch (itemDropRate)
				{
				case 0: case 10:
					item.push_back(Item(ItemTexture, sf::Vector2u(1, 7), 0.3f, vect[i].GetPositionX(), vect[i].GetPositionY(), 0));
					break;
				case 1:case 14:
					item.push_back(Item(ItemTexture, sf::Vector2u(1, 7), 0.3f, vect[i].GetPositionX(), vect[i].GetPositionY(), 1));
					break;
				case 2:case 18:
					item.push_back(Item(ItemTexture, sf::Vector2u(1, 7), 0.3f, vect[i].GetPositionX(), vect[i].GetPositionY(), 2));
					break;
				case 3:case 22:
					item.push_back(Item(ItemTexture, sf::Vector2u(1, 7), 0.3f, vect[i].GetPositionX(), vect[i].GetPositionY(), 3));
					break;
				case 4:case 34:
					item.push_back(Item(ItemTexture, sf::Vector2u(1, 7), 0.3f, vect[i].GetPositionX(), vect[i].GetPositionY(), 4));
					break;
				case 5:case 46:
					item.push_back(Item(ItemTexture, sf::Vector2u(1, 7), 0.3f, vect[i].GetPositionX(), vect[i].GetPositionY(), 5));
					break;
				case 99:case 76:
					item.push_back(Item(ItemTexture, sf::Vector2u(1, 7), 0.3f, vect[i].GetPositionX(), vect[i].GetPositionY(), 6));
					break;
				}
				vect.erase(vect.begin()+i);
			}
		}
	}
}
void drawItem(vector<Item>& vect,sf::RenderWindow& window)
{
	for (Item& item : vect)
	{
		item.Draw(window);
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
			bullet.push_back(Bullet(bulletTexture, sf::Vector2u(1, 4),0.3f,200.0f,0,playerPosX,playerPosY));
			break;
		}
		case(1):
		{
			bullet.push_back(Bullet(bulletTexture, sf::Vector2u(1, 4), 0.3f, 200.0f, 1,playerPosX, playerPosY));
			break;
		}
		case(2):
		{
			bullet.push_back(Bullet(bulletTexture, sf::Vector2u(1, 4), 0.3f, 200.0f, 2,playerPosX, playerPosY));
			break;
		}
		case(3):
		{
			bullet.push_back(Bullet(bulletTexture, sf::Vector2u(1, 4), 0.3f, 200.0f, 3,playerPosX, playerPosY));
			break;
		}
		case(4):
		{
			bullet.push_back(Bullet(bulletTexture, sf::Vector2u(1, 4), 0.3f, 200.0f, 4, playerPosX, playerPosY));
			break;
		}
		case(5):
		{
			bullet.push_back(Bullet(bulletTexture, sf::Vector2u(1, 4), 0.3f, 200.0f, 5, playerPosX, playerPosY));
			break;
		}
		case(6):
		{
			bullet.push_back(Bullet(bulletTexture, sf::Vector2u(1, 4), 0.3f, 200.0f, 6, playerPosX, playerPosY));
			break;
		}
		case(7):
		{
			bullet.push_back(Bullet(bulletTexture, sf::Vector2u(1, 4), 0.3f, 200.0f, 7, playerPosX, playerPosY));
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
	for (Bullet& bullet : vect)
	{
		Collider bulletCollision = bullet.GetCollider();
		for (Platform& wall : wall)
		{
			if (wall.GetCollider().CheckCollider(bulletCollision))
			{
				bullet.bulletCheck(true);
			}
		}
	
		for (Enemies& enemy : enemy)
		{		
			if (enemy.GetCollider().CheckCollider(bulletCollision))
			{
				bullet.bulletCheck(true);
				enemy.setHp(enemy.getHp()-1);
				
			}
		}
		for (int i = 0; i < vect.size(); i++)
		{
			if (bullet.isDestroy())
			{
				vect.erase(vect.begin()+i);
			}
		}
	}
	
}