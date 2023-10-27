#include "Item.h"
#include <iostream>

void Item::initVariables()
{
	this->points = 10;
	this->speed = 15.f;
}

void Item::initTexture()
{
	if (!this->ShieldTex.loadFromFile("assets/RoundShield.png"))
	{
		std::cout << "cannot load shield file" << "\n";
	}
}

void Item::initSprite()
{
	this->Shield.setTexture(ShieldTex);
	this->Shield.setScale(2.f, 2.f);
}

Item::Item(float pos_x, float pos_y)
{
	this->initVariables();
	this->initTexture();
	this->initSprite();
	this->Shield.setPosition(pos_x, pos_y);
}

Item::~Item()
{
}

const sf::FloatRect Item::getBounds() const
{
	return this->Shield.getGlobalBounds();
}

const int& Item::getPoints() const
{
	return this->points;
}

void Item::update()
{
	this->Shield.move(0.f, this->speed);
}

void Item::render(sf::RenderTarget* target)
{
	//std::cout << "test" << this->Shield.getGlobalBounds().left << std::endl;
	target->draw(this->Shield);
}