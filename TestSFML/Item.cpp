#include "Item.h"
#include<iostream>
using namespace std;
Item::Item(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float EnemyX, float EnemyY,int row) :
	animation(texture, imageCount, switchTime)
{
	body.setSize(sf::Vector2f(32.0f, 32.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(EnemyX, EnemyY);
	body.setTexture(texture);
	this->row = row;
	
}

void Item::Update(float deltaTime)
{
	animation.Update(row, deltaTime, 1);
	body.setTextureRect(animation.uvRect);
}

void Item::Draw(sf::RenderWindow& window)
{
	if (itemTimeLeft.getElapsedTime().asMilliseconds() > 5800)
	{
		if (delayItemShow.getElapsedTime().asMilliseconds()>200 && delayItemShow.getElapsedTime().asMilliseconds() < 400)
		{
			window.draw(body);
		}
		else if(delayItemShow.getElapsedTime().asMilliseconds() > 400)
		{
			delayItemShow.restart();
		}
	}
	else
	{
		window.draw(body);
	}
}



bool Item::isTimeExcess()
{
	if (itemTimeLeft.getElapsedTime().asSeconds()>8)
	{
		return true;
	}
	else
	{
		return false;
	}
	
}

Item::~Item()
{
}
