#include "Enemies.h"
#include<iostream>
Enemies::Enemies(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed,float x, float y,int hp, int randItem) :
	animation(texture, imageCount, switchTime)
{
	this->randItem = randItem;
	this->hp = hp;
	prevhp = this->hp;
	this->speed = speed;
	check = 0;
	row = 0;
	body.setSize(sf::Vector2f(30.0f, 32.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(x, y);
	body.setTexture(texture);
}

void Enemies::Update(float deltaTime,float playerX, float playerY)
{
	sf::Vector2f movement(0.0f, 0.0f);
	srand(time(NULL));
	int randTime = rand();
	randTime %= 2500;
	randTime += 1000;
	if (prevhp!=hp)
	{
		body.setFillColor(sf::Color(128,128,128));
		shotFrame--;
	}
	if (shotFrame <= 0)
	{
		shotFrame = 60;
		body.setFillColor(sf::Color(255, 255, 255));
		prevhp = hp;
	}
	if (body.getPosition().x>playerX && isAlive)
	{
		movement.x -= speed * deltaTime;
	}
	if (body.getPosition().x < playerX && isAlive)
	{
		movement.x += speed * deltaTime;
	}
	if (body.getPosition().y < playerY && isAlive)
	{
		movement.y += speed * deltaTime;
	}
	if (body.getPosition().y > playerY && isAlive)
	{
		movement.y -= speed * deltaTime;
	}
	animation.Update(row, deltaTime, 1);
	body.setTextureRect(animation.uvRect);
	body.move(movement);
}

void Enemies::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void Enemies::setHp(int hp)
{
	this->hp = hp;
}

void Enemies::dieAnimation(sf::Texture* texture,bool isAlive, sf::Vector2u imageCount)
{
	this->isAlive = isAlive;
	animation.changeImageCount(imageCount);
	animation.changeSwitchTime(0.1f);
	body.setTexture(texture);
	--dieFrame;
}

bool Enemies::dieComplete()
{
	if (dieFrame <= 0)
	{
		return true;
	}
	else
	{
		return false;
	}
	
}


Enemies::~Enemies()
{
	
}
