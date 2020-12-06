#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include<iostream>
#include<string>
#define HIGHSCORE 124
#define CLOSE_HIGHSCORE 125
#define MENU 123
using namespace std;
class Button
{
public:
	Button(sf::Vector2f position, int size, sf::Font* font, int nextStateGame, string text, sf::SoundBuffer& buttonClickBuffer);
	~Button();
	void Update(sf::Vector2i mousePos, int& stateGame,bool &isShowHighScore);
	void Draw(sf::RenderWindow& window);
	bool isClick = false;
private:
	sf::Clock delayClick;
	sf::Font* font;
	sf::Text body;
	int nextState;
	bool pressed;
	sf::Sound buttonClickSF;
};

