#include "Animation.h"

Animation::Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime)
{
	this->imageCount = imageCount;
	this->switchTime = switchTime;
	totalTime = 0.0f;
	currentImage.x = 0;

	uvRect.width = texture->getSize().x / float(imageCount.x);
	uvRect.height = texture->getSize().y / float(imageCount.y);
}

Animation::~Animation()
{
}

void Animation::changeImageCount(sf::Vector2u imageCount)
{
	this->imageCount = imageCount;
}

void Animation::changeSwitchTime(float switchTime)
{
	this->switchTime = switchTime;
}



void Animation::Update(int row , float deltaTime,int check)
{
	currentImage.y = row;
	totalTime += deltaTime;

	if (totalTime >= switchTime && check)
	{
		totalTime -= switchTime;
		currentImage.x++;
		if (currentImage.x >= imageCount.x)
		{
			currentImage.x = 0;
		}
	}
	else if (totalTime>=1 && check==0)
	{
		currentImage.x = 1;
		totalTime = 0;
	}
	uvRect.left = currentImage.x * uvRect.width;
	uvRect.top = currentImage.y * uvRect.height;
}
