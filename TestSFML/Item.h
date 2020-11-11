#pragma once
#include<SFML/Graphics.hpp>
#include"Animation.h"
#include<Windows.h>
#include"Collider.h"
class Item
{
public:
	Item(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float EnemyX, float EnemyY,int row);
	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window); 
	unsigned int whatRow() { return row; }
	Collider GetCollider() { return Collider(body); }
	bool isTimeExcess();
	~Item();
private:
	sf::RectangleShape body;
	sf::Clock itemTimeLeft;
	sf::Clock delayItemShow;
	Animation animation;
	unsigned int row;
	int randRate;
};

