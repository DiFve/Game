#include "Player.h"
#include"Animation.h"
#include<iostream>
Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed) :
	animation(texture, imageCount, switchTime)
{
	this->realTexture = texture;
	this->speed = speed;
	check = 0;
	row = 0;
	body.setSize(sf::Vector2f(35.0f, 35.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(540.0f, 360.0f);
	body.setTexture(texture);
}

Player::~Player()
{
}

void Player::Update(float deltaTime)
{
	sf::Vector2f movement(0.0f, 0.0f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && isAlive)
	{
		row = 1;
		movement.x -= speed * deltaTime;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && isAlive)
	{
		row = 0;
		movement.x += speed * deltaTime;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && isAlive)
	{
		row = 3;
		movement.y -= speed * deltaTime;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && isAlive)
	{
		row = 2;
		movement.y += speed * deltaTime;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && isAlive)
	{
		row = 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && isAlive)
	{
		row = 0;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && isAlive)
	{
		row = 3;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && isAlive)
	{
		row = 2;
	}

	if (isAlive)
	{
		if (movement.x == 0.0f && movement.y == 0.0f)
		{
			check = 0;
		}
		else
		{
			check = 1;
		}
	}
	
	//std::cout<<body.getPosition().x << " " << body.getPosition().y << std::endl;
	animation.Update(row, deltaTime, check);
	body.setTextureRect(animation.uvRect);
	body.move(movement);
	if (!isAlive)
	{
		--dieFrame;
	}
}

void Player::Draw(sf::RenderWindow& window)
{
	if (dieFrame>0)
	{
		window.draw(body);
	}
	else if(dieFrame<-800)
	{
		dieFrame = 70;
		body.setPosition(540.0f, 360.0f);
		animation.changeSwitchTime(0.3f);
		animation.changeImageCount(sf::Vector2u(4, 4));
		body.setTexture(realTexture);
		this->isAlive = true;
		
	}
	//std::cout << dieFrame << std::endl;
}

void Player::setPlayerSpeed(float speed)
{
	if (isAlive)
	{
		this->speed = speed;
	}
}

void Player::dieAnimation(sf::Texture* texture, bool isAlive, sf::Vector2u imageCount)
{
	this->isAlive = isAlive;
	row = 0;
	animation.changeImageCount(imageCount);
	animation.changeSwitchTime(0.12f);
	body.setTexture(texture);
	this->isAlive = false;
}

void Player::setPosition(float x, float y)
{
	body.setPosition(x, y);
}

