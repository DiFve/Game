#include "Enemies.h"

Enemies::Enemies(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed,float x, float y,int hp) :
	animation(texture, imageCount, switchTime)
{
	this->hp = hp;
	this->speed = speed;
	check = 0;
	row = 0;
	body.setSize(sf::Vector2f(30.0f, 32.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(x, y);
	body.setTexture(texture);
}

void Enemies::Update(float deltaTime,float playerX, float playerY)
{
	
	sf::Vector2f movement(0.0f, 0.0f);
	srand(time(NULL));
	int randTime = rand();
	randTime %= 2500;
	randTime += 1000;
	
	if (body.getPosition().x>playerX)
	{
		movement.x -= speed * deltaTime;
	}
	if (body.getPosition().x < playerX)
	{
		movement.x += speed * deltaTime;
	}
	if (body.getPosition().y < playerY)
	{
		movement.y += speed * deltaTime;
	}
	if (body.getPosition().y > playerY)
	{
		movement.y -= speed * deltaTime;
	}
	//std::cout << body.getPosition().x <<"\n";
	animation.Update(row, deltaTime, 1);
	body.setTextureRect(animation.uvRect);
	body.move(movement);
}

void Enemies::Draw(sf::RenderWindow& window)
{

	window.draw(body);
}

void Enemies::setHp(int hp)
{
	this->hp = hp;
}


Enemies::~Enemies()
{
	
}
