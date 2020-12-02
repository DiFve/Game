#pragma once
#include<SFML/Graphics.hpp>
#include"Animation.h"
#include"Collider.h"
class Player
{
public:
	Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime,float speed);
	~Player();
	bool isAliveReturn() { return isAlive; }
	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
	void setPlayerSpeed(float speed);
	void dieAnimation(sf::Texture* texture, bool isAlive, sf::Vector2u imageCount);
	sf::Vector2f Getposition() { return body.getPosition(); }
	Collider GetCollider() { return Collider(body); }
	void setPosition(float x, float y);
	int dieFrame = 70;
	bool isAlive = true;

private:
	sf::Texture *realTexture;
	sf::RectangleShape body;
	sf::Clock delayInvulnerable;
	Animation animation;
	unsigned int check;
	unsigned int row;
	float speed;
	bool faceRight;
	
};

