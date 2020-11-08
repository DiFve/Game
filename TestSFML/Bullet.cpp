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
		movement.x -= (speed - 80) * deltaTime;
		movement.y -= (speed - 80) * deltaTime;
	}
	if (direction == 5)
	{
		movement.x += (speed - 80) * deltaTime;
		movement.y -= (speed - 80) * deltaTime;
	}
	if (direction == 6)
	{
		movement.x += (speed - 80) * deltaTime;
		movement.y += (speed - 80) * deltaTime;
	}
	if (direction == 7)
	{
		movement.x -= (speed - 80) * deltaTime;
		movement.y += (speed - 80) * deltaTime;
	}
	if (direction == 8)
	{
		movement.x -= (speed - 200) * deltaTime;
		movement.y -= (speed ) * deltaTime;
	}
	if (direction == 9)
	{
		movement.x += (speed - 200) * deltaTime;
		movement.y -= (speed ) * deltaTime;
	}
	if (direction == 10)
	{
		movement.x += (speed - 110) * deltaTime;
		movement.y -= (speed - 50)*deltaTime;
	}
	if (direction == 11)
	{
		movement.x += (speed - 50) * deltaTime;
		movement.y -= (speed - 110) * deltaTime;
	}
	if (direction == 12)
	{
		movement.x += (speed) * deltaTime;
		movement.y -= (speed - 200) * deltaTime;
	}
	if (direction == 13)
	{
		movement.x += (speed)*deltaTime;
		movement.y += (speed - 200) * deltaTime;
	}
	if (direction == 14)
	{
		movement.x += (speed - 110) * deltaTime;
		movement.y += (speed - 50) * deltaTime;
	}
	if (direction == 15)
	{
		movement.x += (speed - 50) * deltaTime;
		movement.y += (speed - 110) * deltaTime;
	}
	if (direction == 16)
	{
		movement.x -= (speed - 200) * deltaTime;
		movement.y += (speed)*deltaTime;
	}
	if (direction == 17)
	{
		movement.x += (speed - 200) * deltaTime;
		movement.y += (speed)*deltaTime;
	}
	if (direction == 18)
	{
		movement.x -= (speed - 110) * deltaTime;
		movement.y += (speed - 50) * deltaTime;
	}
	if (direction == 19)
	{
		movement.x -= (speed - 50) * deltaTime;
		movement.y += (speed - 110) * deltaTime;
	}
	if (direction == 20)
	{
		movement.x -= (speed)*deltaTime;
		movement.y += (speed - 200) * deltaTime;
	}
	if (direction == 21)
	{
		movement.x -= (speed)*deltaTime;
		movement.y -= (speed - 200) * deltaTime;
	}
	if (direction == 22)
	{
		movement.x -= (speed - 110) * deltaTime;
		movement.y -= (speed - 50) * deltaTime;
	}
	if (direction == 23)
	{
		movement.x -= (speed - 50) * deltaTime;
		movement.y -= (speed - 110) * deltaTime;
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

