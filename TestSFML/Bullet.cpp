#include "Bullet.h"

Bullet::Bullet(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed,int dir, float playerPosX, float playerPosY) :
	animation(texture, imageCount, switchTime)
{
	this->speed = speed;
	check = 0;
	row = 0;
	body.setSize(sf::Vector2f(8.0f, 8.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(playerPosX, playerPosY);
	direction = dir;
	body.setTexture(texture);
}

Bullet::~Bullet()
{
}

void Bullet::Update(float deltaTime)
{
	sf::Vector2f movement(0.0f, 0.0f);
	if (direction==0)
	{
		movement.x -= speed * deltaTime;
	}
	if (direction == 1)
	{
		movement.x += speed * deltaTime;
	}
	if (direction == 2)
	{
		movement.y -= speed * deltaTime;
	}
	if (direction == 3)
	{
		movement.y += speed * deltaTime;
	}
	if (direction == 4)
	{
		movement.x -= speed * deltaTime;
		movement.y -= speed * deltaTime;
	}
	if (direction == 5)
	{
		movement.x += speed * deltaTime;
		movement.y -= speed * deltaTime;
	}
	if (direction == 6)
	{
		movement.x += speed * deltaTime;
		movement.y += speed * deltaTime;
	}
	if (direction == 7)
	{
		movement.x -= speed * deltaTime;
		movement.y += speed * deltaTime;
	}
	body.setTextureRect(animation.uvRect);
	body.move(movement);
}

void Bullet::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void Bullet::bulletCheck(bool check)
{
	this->bulletDestroy = check;
}

