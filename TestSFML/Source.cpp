#define _CRT_SECURE_NO_WARNINGS
#include <SFML/Graphics.hpp>
#include <iostream>
#include<string>
#include<stdio.h>
#include<algorithm>
#include<utility>
#include<vector>
#include"Player.h" 
#include<Windows.h>
#include"Platform.h"
#include"Enemies.h"
using namespace std;
void showHighScore(int x,int y,string word, sf::RenderWindow& window);
void createEnemy(vector<Enemies>& enemy, int randSpawn, sf::Texture* Enemies1Texture);
void updateEnemy(vector<Enemies>& enemy, float deltaTime, float playerPosX, float playerPosY);
void drawEnemy(vector<Enemies>& enemy, sf::RenderWindow& window);
void enemyCollider(vector<Enemies>& enemy, Platform& platform1, Platform& platform2, Platform& platform3, Platform& platform4, Platform& platform5, Platform& platform6, Platform& platform7, Platform& platform8, Platform& platform9, Platform& platform10, Platform& platform11, Platform& platform12);
sf::Font font;
int main()
{
	srand(time(NULL));
	sf::Clock enemySpawnClock;
	vector <Enemies> enemies1;
	sf::RenderWindow window(sf::VideoMode(1080, 720), "Game Test!", sf::Style::Close | sf::Style::Resize);
	sf::Texture RightSide;
	sf::Texture Enemies1Texture;
	sf::Texture BG1;


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
	}
	fclose(fp);
	//------------HIGHSCORE------------------

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
	
	Enemies1Texture.loadFromFile("res/img/Enemies1_15px.png");
	Platform platform1(nullptr, sf::Vector2f(640.0f, 5.0f), sf::Vector2f(540.0f, 38.0f));
	Platform platform2(nullptr, sf::Vector2f(5.0f, 640.0f), sf::Vector2f(218.0f, 360.0f));
	Platform platform3(nullptr, sf::Vector2f(5.0f, 640.0f), sf::Vector2f(862.0f, 360.0f));
	Platform platform4(nullptr, sf::Vector2f(640.0f, 5.0f), sf::Vector2f(540.0f, 683.0f));
	Platform platform5(nullptr, sf::Vector2f(280.0f, 40.0f), sf::Vector2f(360.0f, 661.0f));
	Platform platform6(nullptr, sf::Vector2f(280.0f, 40.0f), sf::Vector2f(360.0f, 60.0f));
	Platform platform7(nullptr, sf::Vector2f(240.0f, 40.0f), sf::Vector2f(740.0f, 60.0f));
	Platform platform8(nullptr, sf::Vector2f(240.0f, 40.0f), sf::Vector2f(740.0f, 661.0f));
	Platform platform9(nullptr, sf::Vector2f(40.0f, 280.0f), sf::Vector2f(240.0f, 180.0f));
	Platform platform10(nullptr, sf::Vector2f(40.0f, 280.0f), sf::Vector2f(840.0f, 180.0f));
	Platform platform11(nullptr, sf::Vector2f(40.0f, 240.0f), sf::Vector2f(240.0f, 560.0f));
	Platform platform12(nullptr, sf::Vector2f(40.0f, 240.0f), sf::Vector2f(840.0f, 560.0f));
	float deltaTime = 0.0f;
	sf::Clock clock;
	sf::Clock clockenemyMove;

	while (window.isOpen())
	{
		int enemyMove = clockenemyMove.getElapsedTime().asMilliseconds();
		float enemySpawnTime = enemySpawnClock.getElapsedTime().asMilliseconds();
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
		
		player.Update(deltaTime);
		cout << player.Getposition().x << " "<<player.Getposition().y << "\n";
		updateEnemy(enemies1, deltaTime, player.Getposition().x, player.Getposition().y);
		Collider playerCollison = player.GetCollider();
		
		platform1.GetCollider().CheckCollider(playerCollison, 1.0f);
		platform2.GetCollider().CheckCollider(playerCollison, 1.0f);
		platform3.GetCollider().CheckCollider(playerCollison, 1.0f);
		platform4.GetCollider().CheckCollider(playerCollison, 1.0f);
		platform5.GetCollider().CheckCollider(playerCollison, 1.0f);
		platform6.GetCollider().CheckCollider(playerCollison, 1.0f);
		platform7.GetCollider().CheckCollider(playerCollison, 1.0f);
		platform8.GetCollider().CheckCollider(playerCollison, 1.0f);
		platform9.GetCollider().CheckCollider(playerCollison, 1.0f);
		platform10.GetCollider().CheckCollider(playerCollison, 1.0f);
		platform11.GetCollider().CheckCollider(playerCollison, 1.0f);
		platform12.GetCollider().CheckCollider(playerCollison, 1.0f);

		
		enemyCollider(enemies1, platform1, platform2, platform3, platform4, platform5, platform6, platform7, platform8, platform9, platform10, platform11, platform12);


		window.clear();
		window.draw(BackGround);
		//cout << nub;
		//---------------SHOWHIGHSCORE-------------
		
		showHighScore(10, 10,"HIGHSCORE", window);
		showHighScore(10, 40, userScore[5].second, window);
		showHighScore(10, 70, userScore[4].second, window);
		showHighScore(10, 100, userScore[3].second, window);
		showHighScore(10, 130, userScore[2].second, window);
		showHighScore(10, 160, userScore[1].second, window);
		showHighScore(100, 40, to_string(userScore[5].first), window);
		showHighScore(100, 70, to_string(userScore[4].first), window);
		showHighScore(100, 100, to_string(userScore[3].first), window);
		showHighScore(100, 130, to_string(userScore[2].first), window);
		showHighScore(100, 160, to_string(userScore[1].first), window);
		
		//---------------SHOWHIGHSCORE-------------
		
		/*platform1.Draw(window);
		platform2.Draw(window);
		platform3.Draw(window);
		platform4.Draw(window);
		platform5.Draw(window);
		platform6.Draw(window);
		platform7.Draw(window);
		platform8.Draw(window);
		platform9.Draw(window);
		platform10.Draw(window);
		platform11.Draw(window);
		platform12.Draw(window);*/
		drawEnemy(enemies1,window);
		player.Draw(window);
		window.display();
		
	}
	
	return 0;
}
void enemyCollider(vector<Enemies> &enemy, Platform &platform1, Platform& platform2, Platform& platform3, Platform& platform4, Platform& platform5, Platform& platform6, Platform& platform7, Platform& platform8, Platform& platform9, Platform& platform10, Platform& platform11, Platform& platform12)
{
	for (Enemies& enemy : enemy)
	{
		Collider enemy1Collision = enemy.GetCollider();
		platform1.GetCollider().CheckCollider(enemy1Collision, 1.0f);
		platform2.GetCollider().CheckCollider(enemy1Collision, 1.0f);
		platform3.GetCollider().CheckCollider(enemy1Collision, 1.0f);
		platform4.GetCollider().CheckCollider(enemy1Collision, 1.0f);
		platform5.GetCollider().CheckCollider(enemy1Collision, 1.0f);
		platform6.GetCollider().CheckCollider(enemy1Collision, 1.0f);
		platform7.GetCollider().CheckCollider(enemy1Collision, 1.0f);
		platform8.GetCollider().CheckCollider(enemy1Collision, 1.0f);
		platform9.GetCollider().CheckCollider(enemy1Collision, 1.0f);
		platform10.GetCollider().CheckCollider(enemy1Collision, 1.0f);
		platform11.GetCollider().CheckCollider(enemy1Collision, 1.0f);
		platform12.GetCollider().CheckCollider(enemy1Collision, 1.0f);
	}
	
}
void createEnemy(vector<Enemies> &enemy,int randSpawn,sf::Texture *Enemies1Texture)
{
	randSpawn %= 12;
	switch (randSpawn)
	{
		case(0):
		{
			enemy.push_back(Enemies(Enemies1Texture, sf::Vector2u(2, 1), 0.3f, 40.0f, 241.85, 337.2));
			break;
		}
		case(1):
		{
			enemy.push_back(Enemies(Enemies1Texture, sf::Vector2u(2, 1), 0.3f, 40.0f, 241.85, 374.458));
			break;
		}
		case(2):
		{
			enemy.push_back(Enemies(Enemies1Texture, sf::Vector2u(2, 1), 0.3f, 40.0f, 241.285, 422.5));
			break;
		}
		case(3):
		{
			enemy.push_back(Enemies(Enemies1Texture, sf::Vector2u(2, 1), 0.3f, 40.0f, 517.608, 58));
			break;
		}
		case(4):
		{
			enemy.push_back(Enemies(Enemies1Texture, sf::Vector2u(2, 1), 0.3f, 40.0f, 559.379, 58));
			break;
		}
		case(5):
		{
			enemy.push_back(Enemies(Enemies1Texture, sf::Vector2u(2, 1), 0.3f, 40.0f, 602.5, 58));
			break;
		}
		case(6):
		{
			enemy.push_back(Enemies(Enemies1Texture, sf::Vector2u(2, 1), 0.3f, 40.0f, 842, 337.5));
			break;
		}
		case(7):
		{
			enemy.push_back(Enemies(Enemies1Texture, sf::Vector2u(2, 1), 0.3f, 40.0f, 842, 374.147));
			break;
		}
		case(8):
		{
			enemy.push_back(Enemies(Enemies1Texture, sf::Vector2u(2, 1), 0.3f, 40.0f, 842, 422.5));
			break;
		}
		case(9):
		{
			enemy.push_back(Enemies(Enemies1Texture, sf::Vector2u(2, 1), 0.3f, 40.0f, 602.5, 663));
			break;
		}
		case(10):
		{
			enemy.push_back(Enemies(Enemies1Texture, sf::Vector2u(2, 1), 0.3f, 40.0f, 554.865, 663));
			break;
		}
		case(11):
		{
			enemy.push_back(Enemies(Enemies1Texture, sf::Vector2u(2, 1), 0.3f, 40.0f, 517.5, 663));
			break;
		}
	}
	

}
void updateEnemy(vector<Enemies>& enemy,float deltaTime, float playerPosX, float playerPosY)
{
	for (Enemies& enemy1 : enemy)
	{
		enemy1.Update(deltaTime,playerPosX,playerPosY);
	}
}
void drawEnemy(vector<Enemies>& enemy,sf::RenderWindow& window)
{
	for(Enemies &enemy1 : enemy)
	{
		enemy1.Draw(window);
	}
}
void showHighScore(int x,int y,string word, sf::RenderWindow& window)
{
	sf::Text text;
	text.setFont(font);
	text.setPosition(x, y);
	text.setString(word);
	text.setCharacterSize(32);
	window.draw(text);
}