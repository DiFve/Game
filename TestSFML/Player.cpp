#include "Player.h"
#include"Animation.h"
#include<iostream>
Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed) :
	animation(texture, imageCount, switchTime)
{
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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		row = 1;
		movement.x -= speed * deltaTime;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		row = 0;
		movement.x += speed * deltaTime;
	}	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		row = 3;
		movement.y -= speed * deltaTime;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		row = 2;
		movement.y += speed * deltaTime;
	}
		
	//std::cout << "x = " << body.getPosition().x <<" "<< "y = " << body.getPosition().y << "\n";
	if (movement.x == 0.0f && movement.y==0.0f)
	{
		check = 0;
	}
	else
	{
		check = 1;

	}
	
	animation.Update(row,deltaTime,check);
	body.setTextureRect(animation.uvRect);
	body.move(movement);
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}