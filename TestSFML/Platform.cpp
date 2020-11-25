#include "Platform.h"

Platform::Platform(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position)
{
	body.setSize(size);
	body.setOrigin(size/2.0f);
	body.setTexture(texture);
	body.setPosition(position);
}

Platform::~Platform()
{
}

void Platform::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void Platform::setFillColor(sf::Color color)
{
	body.setFillColor(color);
}

void Platform::setOutlineColor(sf::Color color)
{
	body.setOutlineColor(color);
}

void Platform::setOutlineThickness(int thick)
{
	body.setOutlineThickness(thick);
}

