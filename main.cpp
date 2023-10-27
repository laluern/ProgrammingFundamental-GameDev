#include "Game.h"
#include "Menu.h"
#include <time.h>
#include <SFML/Graphics.hpp>

int pagenum = 1000;

void PName(sf::RenderWindow& window, std::string& name);
void Scoreboard(sf::RenderWindow& window);

struct Leaderboard
{
    std::string namelead;
    int scorelead = 0;
};

bool compareScore(const Leaderboard& a, const Leaderboard& b)
{
    return a.scorelead > b.scorelead;
}

int score;

int main()
{
    //audio
    sf::SoundBuffer menuBuffer;
    sf::Sound soundMenu;

    srand(static_cast<unsigned>(time(nullptr)));

    sf::RenderWindow window(sf::VideoMode(512, 930), "Main menu", sf::Style::Close | sf::Style::Titlebar);
    Menu menu(512, 930);
    sf::Texture mainmenubg;
    std::string name;
    mainmenubg.loadFromFile("assets/menuBg.png");
    sf::Sprite bg;
    bg.setTexture(mainmenubg);

    while (true) {
        if (!menuBuffer.loadFromFile("mainSound.wav"))
        {
            std::cout << "cannot load sound" << "\n";
        }
        soundMenu.setBuffer(menuBuffer);
        soundMenu.setLoop(true);
        soundMenu.play();

        if (pagenum == 1000) {
            while (window.isOpen()) {
                sf::Event ev;
                while (window.pollEvent(ev)) {
                    if (ev.type == sf::Event::Closed) {
                        window.close();
                        break;
                    }

                    if (ev.type == sf::Event::KeyPressed) {
                        if (ev.key.code == sf::Keyboard::Up) {
                            menu.MoveUp();
                        }
                        if (ev.key.code == sf::Keyboard::Down) {
                            menu.MoveDown();
                        }
                        if (ev.key.code == sf::Keyboard::Enter) {
                            if (menu.pressed() == 0) {
                                pagenum = 0;
                            }

                            if (menu.pressed() == 1) {
                                pagenum = 1;
                            }

                            if (menu.pressed() == 2) {
                                pagenum = -1;
                            }
                        }
                    }
                }

                window.clear();
                if (pagenum != 1000) {
                    break;
                }
                window.draw(bg);
                menu.draw(window);
                window.display();
            }
            if (pagenum == -1) {
                window.close();
                break;
            }
            if (pagenum == 0) 
            {
                PName(window, name);
                window.close();
            }
            if (pagenum == 1)
            {
                Scoreboard(window);
            }
            if (pagenum == 3) 
            {
                Game game;
                game.run();

                score = game.getScore();
                std::ofstream offile;
                offile.open("History.txt", std::ios::app);
                offile << name << "," << score << std::endl;
                offile.close();
            }
        }
    }

    //
}

void PName(sf::RenderWindow& window, std::string& name)
{
    if (!name.empty()) {
        name.clear();
    }
    sf::Texture background;
    background.loadFromFile("assets/EnterName.png");
    sf::Sprite bg;
    bg.setTexture(background);
    sf::Font font;
    font.loadFromFile("fonts/PressStart2P_Regular.ttf");
    sf::Text enterName;
    sf::Text playerName;
    enterName.setFont(font);
    playerName.setFont(font);
    enterName.setString("Enter your name");
    enterName.setCharacterSize(30);
    playerName.setCharacterSize(30);
    enterName.setPosition(50, 400);
    playerName.setPosition(50, 500);
    enterName.setFillColor(sf::Color(195, 171, 255));
    playerName.setFillColor(sf::Color::White);
    while (window.isOpen()) {
        sf::Event ev;
        while (window.pollEvent(ev)) {
            if (ev.type == sf::Event::Closed()) {
                window.close();
            }
            if (ev.type == sf::Event::TextEntered) {
                name += static_cast<char>(ev.text.unicode);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace) && name.size() > 0) {
                name.resize(name.size() - 1);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && name.size() > 1) {
                pagenum = 3; //game win
                return;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                pagenum = 1000;
                return;
            }
        }
        playerName.setString(name);
        window.clear();
        window.draw(bg);
        window.draw(enterName);
        window.draw(playerName);
        window.display();
    }
}

void Scoreboard(sf::RenderWindow& window)
{
    std::cout << "Loop JA" << std::endl;
    sf::Texture bgTex;
    bgTex.loadFromFile("assets/background.png");
    sf::Sprite bg;
    bg.setTexture(bgTex);
    bg.setScale(2.1f, 2.1f);
    bg.setPosition(0, 0);

    sf::Font font;
    font.loadFromFile("fonts/PressStart2P_Regular.ttf");

    sf::Text leaderborad;
    leaderborad.setFont(font);
    leaderborad.setCharacterSize(35);
    leaderborad.setString("Leaderborad");
    leaderborad.setFillColor(sf::Color{ 255, 160, 122 });
    leaderborad.setPosition((window.getSize().x / 2.f) - (leaderborad.getGlobalBounds().width / 2.f), 100);

    sf::Text title;
    title.setFont(font);
    title.setCharacterSize(20);
    title.setString("Name           Score");
    title.setFillColor(sf::Color{ 255, 160, 122 });
    title.setPosition((window.getSize().x / 2.f) - (title.getGlobalBounds().width / 2.f), 200);

    sf::Text back;
    back.setFont(font);
    back.setCharacterSize(10);
    back.setString("Press [Esc] for back to Menu");
    back.setFillColor(sf::Color::White);
    back.setPosition((window.getSize().x / 2.f) - (back.getGlobalBounds().width / 2.f), 810);

    sf::Text nametext("", font, 12);
    sf::Text scoretext("", font, 12);

    std::vector <Leaderboard> scores;
    std::ifstream scorefile("History.txt");

    if (scorefile.is_open()) {
        std::string line;
        while (getline(scorefile, line)) {
            size_t commaPos = line.find(",");
            if (commaPos != std::string::npos) {
                Leaderboard HistoryData;
                HistoryData.namelead = line.substr(0, commaPos);
                HistoryData.scorelead = stoi(line.substr(commaPos + 1));
                scores.push_back(HistoryData);
            }
        }
        scorefile.close();
    }
    else {
        std::cout << "ERROR: Could not open data.txt for reading." << std::endl;
    }

    sort(scores.begin(), scores.end(), compareScore);

    while (window.isOpen()) {
        sf::Event ev;
        while (window.pollEvent(ev)) {
            if (ev.type == sf::Event::Closed) {
                window.close();
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                pagenum = 1000;
                return;
            }
        }

        window.clear();
        window.draw(bg);
        window.draw(leaderborad);
        window.draw(title);
        window.draw(back);

        for (int i = 0; i < std::min(5, static_cast<int>(scores.size())); ++i) {
            nametext.setString(scores[i].namelead);
            nametext.setFillColor(sf::Color::White);
            nametext.setPosition(57, 70 * i + 300);

            scoretext.setString(std::to_string(scores[i].scorelead));
            scoretext.setFillColor(sf::Color::White);
            scoretext.setPosition(485, 70 * i + 300);
            scoretext.setOrigin(scoretext.getLocalBounds().width / 2, 0);
            window.draw(nametext);
            window.draw(scoretext);
        }

        window.display();
    }
}
