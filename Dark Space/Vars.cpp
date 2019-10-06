#include <iostream>

#include <SFML/Graphics.hpp>

#include "Vars.h"


short KILLED_IN_MISSION = 0; // счетчик убийств

GAME_STATE STATE = MAIN_MENU;

// Начало игры
void ClickPlay(sf::RenderWindow * win)
{
	STATE = PLAYING;
	std::cout << "ИГРА!" << std::endl;
}

// Вход в настройки
void ClickSettings(sf::RenderWindow * win)
{
	STATE = SETTINGS;
	std::cout << "НАСТРОЙКИ!" << std::endl;
}

// Выход из игры
void ClickGameExit(sf::RenderWindow * win)
{
	win->close();
	std::cout << "ВЫХОД!" << std::endl;
}