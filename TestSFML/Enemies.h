#pragma once
#include<SFML/Graphics.hpp>
#include"Animation.h"
#include"Collider.h"
#include<Windows.h>
#include<iostream>
class Enemies
{
public:
	Enemies(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float x,float y,int hp,int randItem, int type);
	void Update(float deltaTime, float playerX, float playerY);
	void Draw(sf::RenderWindow& window);
	void setHp(int hp);
	void dieAnimation(sf::Texture* texture, bool isAlive, sf::Vector2u imageCount);
	float GetPositionX() { return body.getPosition().x; }
	float GetPositionY() { return body.getPosition().y; }
	bool dieComplete();
	int getHp() { return hp; }
	int randItemRate() { return randItem; }
	bool isThisAlive() { return isAlive; }
	Collider GetCollider() { return Collider(body); }
	void setSpeed(float speed);
	void movementUpdateCollision(float otherX, float otherY);
	int type;
	~Enemies();
	void setSpeed(float anotherEnemyX, float anotherEnemyY);
private:
	
	sf::RectangleShape body;
	Animation animation;
	unsigned int check=1;
	unsigned int row;
	float speed;
	bool isAlive = true;
	float deltaTime;
	int hp,prevhp;
	int randItem;
	int dieFrame = 60,shotFrame=60;
	
};

