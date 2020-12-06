#include "Button.h"

Button::Button(sf::Vector2f position, int size,sf::Font* font, int nextStateGame, string text, sf::SoundBuffer& buttonClickBuffer)
{
	this->nextState = nextStateGame;
	body.setCharacterSize(size);
	body.setPosition(position);
	body.setFont(*font);
	body.setString(text);
	buttonClickSF.setBuffer(buttonClickBuffer);
	buttonClickSF.setVolume(100);
}

Button::~Button()
{
}

void Button::Update(sf::Vector2i mousePos, int& stateGame, bool& isShowHighScore)
{
	
	if (this->body.getGlobalBounds().contains(sf::Vector2f(mousePos)))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && delayClick.getElapsedTime().asMilliseconds() > 500) 
		{
			buttonClickSF.play();
			isClick = true;
			delayClick.restart();
			body.setFillColor(sf::Color(133.0f, 87.0f, 35.0f));
			if (nextState == HIGHSCORE)
			{
				isShowHighScore = true;
			}
			else if (nextState == CLOSE_HIGHSCORE)
			{
				isShowHighScore = false;
			}
			else
			{
				stateGame = nextState;
			}	
		} 
		else 
		{
			isClick = false;
			if (nextState == CLOSE_HIGHSCORE)
			{
				body.setFillColor(sf::Color(188, 51, 74));
				body.setOutlineColor(sf::Color::White);
				body.setOutlineThickness(2);
			}
			else
			{
				body.setFillColor(sf::Color::White);
				body.setOutlineColor(sf::Color::Black);
				body.setOutlineThickness(5);
			}
		}
	}
	else 
	{
		if (nextState == CLOSE_HIGHSCORE)
		{
			body.setFillColor(sf::Color(188,51,74));
			body.setOutlineColor(sf::Color::Black);
			body.setOutlineThickness(0);
		}
		else
		{
			body.setFillColor(sf::Color::White);
			body.setOutlineThickness(2);
		}
		
	}
}

void Button::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}
