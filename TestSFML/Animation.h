#pragma once
#include<SFML\Graphics.hpp>
class Animation
{
public:
	Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);
	~Animation();
	void changeImageCount(sf::Vector2u imageCount);
	void changeSwitchTime(float switchTime);
	void Update(int row,float deltaTime,int check);
public:
	sf::IntRect uvRect;

private:
	sf::Vector2u imageCount;
	sf::Vector2u currentImage;
	float totalTime;
	float switchTime;

};

