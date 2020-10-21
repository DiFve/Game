#define _CRT_SECURE_NO_WARNINGS
#include <SFML/Graphics.hpp>
#include <iostream>
#include<string>
#include<stdio.h>
#include<algorithm>
#include<utility>
#include<vector>
#include"Player.h"
#include"Platform.h"
using namespace std;
void showHighScore(int x,int y,string word, sf::RenderWindow& window);
int main()
{
	sf::RenderWindow window(sf::VideoMode(1080, 720), "Game Test!", sf::Style::Close | sf::Style::Resize);
	sf::Texture RightSide;
	sf::Texture BG1;
	vector <pair<int, string>> userScore;

	//------------HIGHSCORE------------------
	char temp[255];
	int score[6];
	string name[6];
	FILE* fp;
	fp = fopen("./Score.txt", "r");
	for (int i = 0; i < 6; i++)
	{
		fscanf(fp, "%s", temp);
		name[i] = temp;
		//std::cout << name[i];
		fscanf(fp, "%d", &score[i]);
		//printf("%d\n", score[i]);
		userScore.push_back(make_pair(score[i], name[i]));
	}
	sort(userScore.begin(), userScore.end());
	fclose(fp);
	fopen("./Score.txt", "w");
	for (int i = 5; i >= 1; i--)
	{
		strcpy(temp,userScore[i].second.c_str());
		fprintf(fp, "%s %d\n",temp, userScore[i].first);
		cout << userScore[i].second << " " << userScore[i].first;
		cout << endl;
		
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
	
	while (window.isOpen())
	{
		
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
		
		player.Update(deltaTime);
		Collider test = player.GetCollider();
		platform1.GetCollider().CheckCollider(test, 1.0f);
		platform2.GetCollider().CheckCollider(test, 1.0f);
		platform3.GetCollider().CheckCollider(test, 1.0f);
		platform4.GetCollider().CheckCollider(test, 1.0f);
		platform5.GetCollider().CheckCollider(test, 1.0f);
		platform6.GetCollider().CheckCollider(test, 1.0f);
		platform7.GetCollider().CheckCollider(test, 1.0f);
		platform8.GetCollider().CheckCollider(test, 1.0f);
		platform9.GetCollider().CheckCollider(test, 1.0f);
		platform10.GetCollider().CheckCollider(test, 1.0f);
		platform11.GetCollider().CheckCollider(test, 1.0f);
		platform12.GetCollider().CheckCollider(test, 1.0f);
		
		window.clear();
		window.draw(BackGround);
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
		player.Draw(window);
		window.display();
		
	}
	
	return 0;
}
void showHighScore(int x,int y,string word, sf::RenderWindow& window)
{
	sf::Font font;
	font.loadFromFile("Sound Bubble DEMO.otf");
	sf::Text text;
	text.setFont(font);
	text.setPosition(x, y);
	text.setString(word);
	text.setCharacterSize(32);
	window.draw(text);
}