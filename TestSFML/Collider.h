#pragma once
#include<SFML\Graphics.hpp>
#include<iostream>
class Collider
{
public:
	Collider(sf::RectangleShape& body);
	~Collider();

	void Move(float dx, float dy) { body.move(dx, dy); }

	bool CheckCollider(Collider& other);
	bool itemColliderCheck(Collider& other);
	sf::Vector2f Getposition() { return body.getPosition(); }
	sf::Vector2f GetHalfSize() { return body.getSize() / 2.0f; }

private:
	sf::RectangleShape& body;
	float push;
};

