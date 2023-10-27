#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>

class Item
{
private:
	sf::Texture ShieldTex;
	sf::Sprite Shield;

	int speed;
	int points;

	void initVariables();
	void initTexture();
	void initSprite();
public:
	Item(float pos_x, float pos_y);
	virtual ~Item();

	const sf::FloatRect getBounds() const;
	const int& getPoints() const;

	void update();
	void render(sf::RenderTarget* target);
};