#include "BombEffect.h"
#include<iostream>
BombEffect::BombEffect(sf::Texture* texture, sf::Vector2u imageCount, float PosX, float PosY) :
	animation(texture, imageCount, 0.05f)
{
	check = 1;
	row = 0;
	body.setSize(sf::Vector2f(35.0f, 35.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(PosX, PosY);
	body.setTexture(texture);
}

BombEffect::~BombEffect()
{
}

void BombEffect::Update(float deltaTime)
{
	//std::cout << body.getPosition().x << " " << body.getPosition().y << std::endl;
	animation.Update(row, deltaTime, check);
	body.setTextureRect(animation.uvRect);
}

void BombEffect::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}
