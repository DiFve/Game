#include "Decoration.h"

Decoration::Decoration(sf::Texture* texture, sf::Vector2u imageCount, float switchTime,sf::Vector2f size,sf::Vector2f Position) :
	animation(texture, imageCount, switchTime)
{
	
	row = 0;
	body.setSize(size);
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(Position);
	body.setTexture(texture);
}

Decoration::~Decoration()
{
}

void Decoration::Update(float deltaTime)
{
	animation.Update(row, deltaTime, 1);
	body.setTextureRect(animation.uvRect);
}

void Decoration::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}
