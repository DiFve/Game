#pragma once
#include<SFML/Graphics.hpp>
#include"Animation.h"
#include"Collider.h"
#include<Windows.h>
#include<iostream>
class Enemies
{
public:
	Enemies(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float x,float y,int hp);
	void Update(float deltaTime, float playerX, float playerY);
	void Draw(sf::RenderWindow& window);
	void setHp(int hp);
	int getHp() { return hp; }
	Collider GetCollider() { return Collider(body); }
	~Enemies();
private:
	sf::RectangleShape body;
	Animation animation;
	unsigned int check=1;
	unsigned int row;
	float speed;
	int hp;
};

