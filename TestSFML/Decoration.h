#pragma once
#include<SFML/Graphics.hpp>
#include"Animation.h"
class Decoration
{
public:
	Decoration(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, sf::Vector2f size, sf::Vector2f Position);
	~Decoration();
	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
private:
	Animation animation;
	unsigned int row;
	sf::RectangleShape body;
};

