#pragma once
#include<SFML/Graphics.hpp>
#include"Animation.h"
#include"Collider.h"
class Bullet
{
public:
	Bullet(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, int dir, float playerPosX, float playerPosY);
	~Bullet();

	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
	void bulletCheck(bool check);
	bool isDestroy() { return bulletDestroy; }
	sf::Vector2f Getposition() { return body.getPosition(); }
	Collider GetCollider() { return Collider(body); }
private:
	bool bulletDestroy=false;
	sf::RectangleShape body;
	Animation animation;
	unsigned int check;
	unsigned int row=0;
	float speed;
	int direction;
};

