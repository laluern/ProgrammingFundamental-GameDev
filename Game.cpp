#include "Game.h"
#include "Menu.h"

void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(512, 930), "Heart Shooter", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(60);
}

void Game::initTextures()
{
	this->textures["BULLET"] = new sf::Texture();
	this->textures["BULLET"]->loadFromFile("assets/bullet.png");
}

void Game::initGUI()
{
	//load font
	if (!this->font.loadFromFile("fonts/PressStart2P_Regular.ttf"))
	{
		std::cout << "failed to load fonts" << "\n";
	}

	//init point text
	this->pointText.setPosition(320.f, 30.f);
	this->pointText.setFont(this->font);
	this->pointText.setCharacterSize(12);
	this->pointText.setFillColor(sf::Color::White);
	this->pointText.setString("test");

	this->gameOverText.setFont(this->font);
	this->gameOverText.setCharacterSize(20);
	this->gameOverText.setFillColor(sf::Color::Red);
	this->gameOverText.setString("Game Over!");
	this->gameOverText.setPosition(
		this->window->getSize().x / 2.f - this->gameOverText.getGlobalBounds().width / 2.f, 
		this->window->getSize().y / 2.f - this->gameOverText.getGlobalBounds().height / 2.f);

	this->escText.setFont(this->font);
	this->escText.setCharacterSize(20);
	this->escText.setFillColor(sf::Color::Red);
	this->escText.setString("Press esc to escape");
	this->escText.setPosition(80, 500);
	//heart
	if (!this->heartTex.loadFromFile("assets/heart.png"))
	{
		std::cout << "cannot load heart texture" << "\n";
	}
	this->heart.setTexture(heartTex);
	this->heart.setPosition(10.f, 20.f);
	this->heart.setScale(3.f, 3.f);

	//init player GUI
	this->playerHpBar.setSize(sf::Vector2f(220.f, 25.f));
	this->playerHpBar.setFillColor(sf::Color::Color(194, 30, 86, 255));
	this->playerHpBar.setPosition(sf::Vector2f(40.f, 20.f));

	this->playerHpBarBack = this->playerHpBar;
	this->playerHpBarBack.setFillColor(sf::Color(25, 25, 25, 200));
}

void Game::initSpace()
{
	if (!this->spaceBackgroundTex.loadFromFile("assets/background.png"))
	{
		std::cout << "cannot load background texture" << "\n";
	}
	this->spaceBackground.setTexture(this->spaceBackgroundTex);
	this->spaceBackground.setScale(3.5f, 3.5f);
}

void Game::initSystems()
{
	this->points = 0;
}

void Game::initPlayer()
{
	this->player = new Player();
}

void Game::initEnemies()
{
	//this->spawnTimerMaxEnemy = 60.f;
	this->spawnTimerEnemy = this->spawnTimerMaxEnemy;
}

void Game::initItem()
{
	//this->spawnTimerMaxItem = 200.f;
	this->spawnTimerItem = this->spawnTimerMaxItem;
}

Game::Game()
{
	this->initWindow();
	this->initTextures();
	this->initGUI();
	this->initSpace();
	this->initSystems();
	this->initPlayer();
	this->initEnemies();
	this->initItem();
}

Game::~Game()
{
	delete this->window;
	delete this->player;

	//delete textures
	for (auto& i : this->textures)
	{
		delete i.second;
	}
	//delete bullets
	for (auto* i : this->bullets)
	{
		delete i;
	}
	//delete enemies
	for (auto* i : this->enemies)
	{
		delete i;
	}
	//delete items
	for (auto* i : this->items)
	{
		delete i;
	}
}

void Game::run()
{
	while (this->window->isOpen())
	{
		this->updatePollEvents();

		if (this->player->getHp() > 0)
		{
			this->update();
		}
		
		this->render();
	}
}

const int& Game::getScore() const
{
	return this->points;
}

void Game::updatePollEvents()
{
	sf::Event ev;
	while (this->window->pollEvent(ev))
	{
		if (ev.Event::type == sf::Event::Closed)
		{
			this->window->close();
		}
		if (ev.Event::KeyPressed && ev.Event::key.code == sf::Keyboard::Escape)
		{
			this->window->close();
		}
	}
}

void Game::updateInput()
{
	//move
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		this->player->move(0.f, -1.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		this->player->move(-1.f, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		this->player->move(0.f, 1.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		this->player->move(1.f, 0.f);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && this->player->canAttack())
	{
		this->bullets.push_back(
			new Bullet(this->textures["BULLET"], 
			this->player->getPos().x + this->player->getBounds().width/4.5f, 
			this->player->getPos().y, 
			0.f, -1.f, 5.f)
		);
	}
}

void Game::updateGUI()
{
	std::stringstream ss;

	ss << "Score : " << this->points;

	this->pointText.setString(ss.str());

	//update player GUI
	float hpPercent = static_cast<float>(this->player->getHp()) /(this->player->getHpMax());
	this->playerHpBar.setSize(sf::Vector2f(220.f * hpPercent, this->playerHpBar.getSize().y));
}

void Game::updateCollision()
{
	//left space collision
	if (this->player->getBounds().left < 0.f)
	{
		this->player->setPosition(0.f, this->player->getBounds().top);
	}
	//right space collision
	else if (this->player->getBounds().left + this->player->getBounds().width >= this->window->getSize().x)
	{
		this->player->setPosition(this->window->getSize().x - this->player->getBounds().width, this->player->getBounds().top);
	}
	//top space collision
	if (this->player->getBounds().top < 0.f)
	{
		this->player->setPosition(this->player->getBounds().left, 0.f);
	}
	//bottom space collision
	else if (this->player->getBounds().top + this->player->getBounds().height >= this->window->getSize().y)
	{
		this->player->setPosition(this->player->getBounds().left, this->window->getSize().y - this->player->getBounds().height);
	}
}

void Game::updateBullets()
{
	unsigned counter = 0;
	for (auto *bullet : this->bullets)
	{
		bullet->update();

		//bullet culling (top of screen)
		if (bullet->getBounds().top < 0.f)
			// + bullet->getBounds().height
		{
			//delete bullet
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);
		}
		++counter;
	}
}

void Game::updateEnemies()
{
	//spawning
	if (points <= 200)
	{
		this->spawnTimerMaxEnemy = 60.f;
	}
	else if (points <= 300)
	{
		this->spawnTimerMaxEnemy = 50.f;
	}
	else if (points <= 400)
	{
		this->spawnTimerMaxEnemy = 40.f;
	}
	else if (points <= 500)
	{
		this->spawnTimerMaxEnemy = 30.f;
	}
	else if (points <= 600)
	{
		this->spawnTimerMaxEnemy = 20.f;
	}
	else if (points <= 800)
	{
		this->spawnTimerMaxEnemy = 10.f;
	}
	else if (points <= 1500)
	{
		this->spawnTimerMaxEnemy = 7.f;
	}

	//spawning
	this->spawnTimerEnemy += 1.f;
	if (this->spawnTimerEnemy >= this->spawnTimerMaxEnemy)
	{
		this->enemies.push_back(new Enemy(rand() % this->window->getSize().x-20.f, -100.f));
		this->spawnTimerEnemy = 0.f;
	}
	//update
	unsigned counter = 0;
	for (auto* enemy : this->enemies)
	{
		enemy->update();

		if (enemy->getBounds().top > this->window->getSize().y)
		{
			//delete enemy
			delete this->enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);
		}
		//enemy player collision
		else if(enemy->getBounds().intersects(this->player->getBounds()))
		{
			//damage
			this->player->loseHp(this->enemies.at(counter)->getDamage());
			delete this->enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);
		}
		++counter;
	}
}

void Game::updateItem()
{
	//spawning
	this->spawnTimerItem += 1.f;
	if (points <= 200)
	{
		this->spawnTimerMaxItem = 200.f;
	}
	else if (points <= 300)
	{
		this->spawnTimerMaxItem = 220.f;
	}
	else if (points <= 400)
	{
		this->spawnTimerMaxItem = 250.f;
	}
	else if (points <= 500)
	{
		this->spawnTimerMaxItem = 300.f;
	}
	else if (points <= 600)
	{
		this->spawnTimerMaxItem = 320.f;
	}
	else if (points <= 600)
	{
		this->spawnTimerMaxItem = 350.f;
	}
	else if (points <= 1500)
	{
		this->spawnTimerMaxItem = 500.f;
	}
	if (this->spawnTimerItem >= this->spawnTimerMaxItem)
	{
		this->items.push_back(new Item(rand() % this->window->getSize().x - 20.f, -100.f));
		this->spawnTimerItem = 0.f;
	}
	//update
	unsigned counter = 0;
	for (auto* item : this->items)
	{
		item->update();
		if (item->getBounds().top > this->window->getSize().y)
		{
			//delete item
			delete this->items.at(counter);
			this->items.erase(this->items.begin() + counter);
		}
		//item player collision
		if (this->player->getHp() < 100)
		{
			if (item->getBounds().intersects(this->player->getBounds()))
			{
				this->player->getHp(this->items.at(counter)->getPoints());
				delete this->items.at(counter);
				this->items.erase(this->items.begin() + counter);
			}
		}
		++counter;
	}
}

void Game::updateCombat()
{
	for (int i = 0; i < this->enemies.size(); ++i)
	{
		bool enemy_deleted = false;
		for (size_t k = 0; k < this->bullets.size() && enemy_deleted == false; k++)
		{
			if (this->enemies[i]->getBounds().intersects(this->bullets[k]->getBounds()))
			{
				//audio
				if (!BulletBuffer.loadFromFile("cutieShot.wav"))
				{
					std::cout << "cannot load sound" << "\n";
				}
				soundBullet.setBuffer(BulletBuffer);
				soundBullet.play();

				this->points += this->enemies[i]->getPoints();

				delete this->enemies[i];
				this->enemies.erase(this->enemies.begin() + i);

				delete this->bullets[k];
				this->bullets.erase(this->bullets.begin() + k);

				enemy_deleted = true;
			}
		}
	}
}

void Game::update()
{
	this->updateInput();

	this->player->update();

	this->updateCollision();

	this->updateBullets();

	this->updateEnemies();

	this->updateItem();

	this->updateCombat();

	this->updateGUI();

	//this->updateSpace();
}

void Game::renderGUI()
{
	this->window->draw(this->heart);
	this->window->draw(this->pointText);
	this->window->draw(this->playerHpBarBack);
	this->window->draw(this->playerHpBar);
}

void Game::renderSpace()
{
	this->window->draw(this->spaceBackground);
}

void Game::render()
{
	this->window->clear();

	//draw space
	this->renderSpace();

	//draw all stuffs
	this->player->render(*this->window);

	for (auto* bullet : this->bullets)
	{
		bullet->render(this->window);
	}

	for (auto* enemy : this->enemies)
	{
		enemy->render(this->window);
	}

	for (auto* item : this->items)
	{
		item->render(this->window);
	}

	this->renderGUI();

	if (this->player->getHp() <= 0)
	{
		this->window->clear();
		this->getScore();
		this->window->draw(this->spaceBackground);
		this->window->draw(this->gameOverText);
		this->window->draw(this->escText);
	}
	this->window->display();

	std::cout << player->getHp() << std::endl;
}