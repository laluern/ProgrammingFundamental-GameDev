#pragma once
#include<map>
#include<sstream>
#include<fstream>
#include<string>
#include<iostream>
#include<SFML/Audio.hpp>
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Item.h"

class Game
{
private:
	//window
	sf::RenderWindow* window;

	//resources
	std::map<std::string, sf::Texture*> textures;
	std::vector<Bullet*> bullets;

	//GUI
	sf::Font font;
	sf::Text pointText;

	sf::Text gameOverText;

	sf::Text escText;

	sf::Texture heartTex;
	sf::Sprite heart;

	//bg
	sf::Texture spaceBackgroundTex;
	sf::Sprite spaceBackground;

	//systems
	unsigned points;

	//player
	Player* player;

	//player GUI
	sf::RectangleShape playerHpBar;
	sf::RectangleShape playerHpBarBack;

	//enemies
	float spawnTimerEnemy;
	float spawnTimerMaxEnemy;
	std::vector<Enemy*> enemies;

	//item
	float spawnTimerItem;
	float spawnTimerMaxItem;
	std::vector<Item*> items;
	
	//audio
	sf::SoundBuffer BulletBuffer;
	sf::Sound soundBullet;

	void initWindow();
	void initTextures();
	void initGUI();
	void initSpace();
	void initSystems();
	void initPlayer();
	void initEnemies();
	void initItem();
public:
	Game();
	virtual ~Game();

	void run();

	const int& getScore() const;

	void updatePollEvents();
	void updateInput();
	void updateGUI();
	//void updateSpace(); 
	void updateCollision();
	void updateBullets();
	void updateEnemies();
	void updateItem();
	void updateCombat();
	void update();
	void renderGUI();
	void renderSpace();
	void render();
};