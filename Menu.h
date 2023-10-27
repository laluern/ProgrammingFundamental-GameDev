#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.h"

class Menu
{
public:
	sf::Text mainmenu[3];
	sf::Text MyName;
	sf::Text StudentID;
	Menu(float width, float height);
	void draw(sf::RenderWindow& window);
	void MoveUp();
	void MoveDown();
	void setSelected(int n);
	int pressed() {
		return selected;
	}
	~Menu();

private:
	int selected;
	sf::Font font;

};