#pragma once
#include<SFML/Graphics.hpp>
#include"Animation.h"
#include"Collider.h"
class DecorationMove
{
public:
	DecorationMove(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, sf::Vector2f position,int type, sf::Vector2f size);
	~DecorationMove();
	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
	void setPosition(sf::Vector2f position);
	sf::Vector2f Getposition() { return body.getPosition(); }
	Collider GetCollider() { return Collider(body); }
	bool isCollider = false;
private:
	sf::RectangleShape body;
	Animation animation;
	unsigned int check;
	unsigned int row;
	float speed;
	int type;
};

