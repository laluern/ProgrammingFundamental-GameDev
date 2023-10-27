#include "Menu.h"
#include <SFML/Graphics.hpp>

Menu::Menu(float width, float height)
{
	font.loadFromFile("fonts/PressStart2P_Regular.ttf");

	//play
	mainmenu[0].setFont(font);
	mainmenu[0].setFillColor(sf::Color::White);
	mainmenu[0].setString("PLAY");
	mainmenu[0].setOrigin(mainmenu[0].getGlobalBounds().width / 2, mainmenu[0].getGlobalBounds().height / 2);
	mainmenu[0].setCharacterSize(32);
	mainmenu[0].setPosition(sf::Vector2f(180, 500));

	//scoreboard
	mainmenu[1].setFont(font);
	mainmenu[1].setFillColor(sf::Color::White);
	mainmenu[1].setString("LEADERBOARD");
	mainmenu[1].setCharacterSize(32);
	mainmenu[1].setPosition(sf::Vector2f(120, 600));

	//Exit
	mainmenu[2].setFont(font);
	mainmenu[2].setFillColor(sf::Color::White);
	mainmenu[2].setString("EXIT");
	mainmenu[2].setCharacterSize(32);
	mainmenu[2].setPosition(sf::Vector2f(120, 700));

	selected = 0;

	//student id
	StudentID.setFont(font);
	StudentID.setCharacterSize(9);
	StudentID.setPosition(320.f, 30.f);
	StudentID.setFillColor(sf::Color::White);
	StudentID.setString("66010786");

	//name
	MyName.setFont(font);
	MyName.setCharacterSize(9);
	MyName.setPosition(320.f, 50.f);
	MyName.setFillColor(sf::Color::White);
	MyName.setString("Sataporn Kittisoranan");

}

Menu::~Menu() {}

void Menu::setSelected(int n)
{
	selected = n;
}

void Menu::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < 3; i++) {
		window.draw(mainmenu[i]);
	}
	window.draw(MyName);
	window.draw(StudentID);
}

void Menu::MoveDown()
{
	if (selected + 1 <= 3) //not exit
	{
		mainmenu[selected].setFillColor(sf::Color::White);
		selected++;
		if (selected == 3) {
			selected = 0;
		}
		mainmenu[selected].setFillColor(sf::Color(195, 171, 255));
	}
}

void Menu::MoveUp()
{
	if (selected - 1 >= -1) // not play
	{
		mainmenu[selected].setFillColor(sf::Color::White);
		selected--;
		if (selected == -1) {
			selected = 2;
		}
		mainmenu[selected].setFillColor(sf::Color(195, 171, 255));
	}
}