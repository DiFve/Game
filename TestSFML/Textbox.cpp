#include "Textbox.h"

Textbox::Textbox(int size, sf::Color color, bool sel, sf::Font& font, sf::Vector2f position)
{
	textbox.setFont(font);
	textbox.setPosition(position);
	textbox.setCharacterSize(size);
	
	
	body.setSize(sf::Vector2f(200.0f,40.0f));
	//body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(position.x-5,position.y-5);
	body.setFillColor(color);
	isSelectedBool = sel;
	hasLimit = true;
	limit = 10;
	if (sel)
	{
		textbox.setString("_");
	}
	else
	{
		textbox.setString("  Input your name");
	}
}

void Textbox::setSelected(bool sel)
{
	isSelectedBool = sel;
	if (!sel)
	{
		std::string t = text.str();
		std::string newT = "";
		for (int i = 0; i < t.length(); i++)
		{
			newT += t[i];
		}
		textbox.setString(newT);
	}
}

void Textbox::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	window.draw(textbox);
}

void Textbox::typedOn(sf::Event input)
{
	if (isSelectedBool)
	{
		int charTyped = input.text.unicode;
		if (charTyped < 128)
		{
			if (hasLimit)
			{
				if (text.str().length() <= limit)
				{
					inputLogic(charTyped);
				}
				else if (text.str().length() > limit && charTyped == DELETE_KEY)
				{
					deleteLastChar();
				}
			}
			else
			{
				inputLogic(charTyped);
			}
		}
	}
}

void Textbox::Update(sf::Vector2i mousePos)
{
	//std::cout << isSelectedBool << std::endl;
	if (isSelectedBool)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			name = text.str();
			isSelectedBool = false;
			textbox.setString(text.str());
		}
	}
	if (body.getGlobalBounds().contains(sf::Vector2f(mousePos))) 
	{
		
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && delay.getElapsedTime().asMilliseconds()>500) 
		{
			delay.restart();
			this->isSelectedBool = !this->isSelectedBool;
			if (isSelectedBool) 
			{
				textbox.setString(text.str() + "_");
			}
			else 
			{
				textbox.setString(text.str());
			}
		}
		
	}
	else if ((!body.getGlobalBounds().contains(sf::Vector2f(mousePos))))
	{
		if (text.str() != "")
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && delay.getElapsedTime().asMilliseconds() > 500)
			{
				name = text.str();
				delay.restart();
				this->isSelectedBool = false;
				if (isSelectedBool)
				{
					textbox.setString(text.str() + "_");
				}
				else
				{
					textbox.setString(text.str());
				}
			}
		}
	}
}

void Textbox::resetString()
{
	textbox.setString("  Input your name");
	text.str("");
	name = "";
}

void Textbox::inputLogic(int charTyped)
{
	if (charTyped != DELETE_KEY && charTyped != ENTER_KEY && charTyped != ESCAPE_KEY)
	{
		text << static_cast<char>(charTyped);
	}
	else if (charTyped == DELETE_KEY)
	{
		if (text.str().length() > 0)
		{
			deleteLastChar();
		}
	}
	textbox.setString(text.str() + "_");
}

void Textbox::deleteLastChar()
{
	std::string t = text.str();
	std::string newT = "";
	for (int i = 0; i < t.length() - 1; i++)
	{
		newT += t[i];
	}
	text.str("");
	text << newT;

	textbox.setString(text.str());
}
