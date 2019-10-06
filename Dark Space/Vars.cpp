#include <iostream>

#include <SFML/Graphics.hpp>

#include "Vars.h"


short KILLED_IN_MISSION = 0; // ������� �������

GAME_STATE STATE = MAIN_MENU;

// ������ ����
void ClickPlay(sf::RenderWindow * win)
{
	STATE = PLAYING;
	std::cout << "����!" << std::endl;
}

// ���� � ���������
void ClickSettings(sf::RenderWindow * win)
{
	STATE = SETTINGS;
	std::cout << "���������!" << std::endl;
}

// ����� �� ����
void ClickGameExit(sf::RenderWindow * win)
{
	win->close();
	std::cout << "�����!" << std::endl;
}