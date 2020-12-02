#include "DecorationMove.h"

DecorationMove::DecorationMove(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed,sf::Vector2f position, int type, sf::Vector2f size):
	animation(texture, imageCount, switchTime)
{
	this->type = type;
	this->speed = speed;
	check = 1;
	row = 0;
	body.setSize(size);
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(position);
	body.setTexture(texture);
}

DecorationMove::~DecorationMove()
{
}

void DecorationMove::Update(float deltaTime)
{
	sf::Vector2f movement(0.0f, 0.0f);
	if (isCollider)
	{
		if (type == 1)
		{
			row = 1;
		}

		movement.x -= speed * deltaTime;
	}
	if (!isCollider)
	{
		if (type == 1)
		{
			row = 0;
		}
		movement.x += speed * deltaTime;
	}
	animation.Update(row, deltaTime, check);
	body.setTextureRect(animation.uvRect);
	body.move(movement);
}

void DecorationMove::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void DecorationMove::setPosition(sf::Vector2f position)
{
	body.setPosition(position);
}
