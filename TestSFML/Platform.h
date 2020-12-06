#pragma once
#include<SFML\Graphics.hpp>
#include"Collider.h"
class Platform
{
public:
	Platform(sf::Texture* texture,sf::Vector2f size, sf::Vector2f position);
	~Platform();

	void Draw(sf::RenderWindow& window);
	void setFillColor(sf::Color color);
	void setOutlineColor(sf::Color color);
	void setOutlineThickness(int thick);
	Collider GetCollider() { return Collider(body); }
	sf::Vector2f Getposition() { return body.getPosition(); }
	

private:
	sf::RectangleShape body;
};

