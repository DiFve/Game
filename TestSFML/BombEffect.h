#pragma once
#include<SFML/Graphics.hpp>
#include"Animation.h"
class BombEffect
{
public:
	BombEffect(sf::Texture* texture, sf::Vector2u imageCount, float PosX, float PosY);
	~BombEffect();
	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
private:
	sf::RectangleShape body;
	Animation animation;
	unsigned int check = 1;
	unsigned int row = 0;
};

