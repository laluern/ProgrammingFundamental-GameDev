#include "Enemy.h"

void Enemy::initVariables()
{
	this->type = 0;
	this->speed = 17.f;
	this->hpMax = 100.f;
	this->hp = this->hpMax;
	this->damage = 30;
	this->points = 10;
}
void Enemy::initTexture()
{
	//enemy1
	if (!this->enemy1Tex.loadFromFile("assets/enemy1.png"))
	{
		std::cout << "cannot load enemy1 texture" << "\n";
	}
}
void Enemy::initSprite()
{
	//enemy1
	this->enemy1.setTexture(enemy1Tex);
	this->enemy1.setScale(10.f, 10.f);
}
/*
void Enemy::initShape()
{
	this->shape.setRadius(this->pointCount * 5);
	this->shape.setPointCount(this->pointCount);
	this->shape.setFillColor(sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1, 255));
}
*/

Enemy::Enemy(float pos_x, float pos_y)
{
	this->initVariables(); 
	this->initTexture();
	this->initSprite();
	this->enemy1.setPosition(pos_x, pos_y);
}

Enemy::~Enemy()
{

}

const sf::FloatRect Enemy::getBounds() const
{
	return this->enemy1.getGlobalBounds();
}

const int& Enemy::getPoints() const
{
	return this->points;
}

const int& Enemy::getDamage() const
{
	return this->damage;
}

void Enemy::update()
{
	this->enemy1.move(0.f, this->speed);
}

void Enemy::render(sf::RenderTarget* target)
{
	target->draw(this->enemy1);
}
