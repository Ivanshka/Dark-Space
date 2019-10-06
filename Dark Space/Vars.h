#pragma once

#include <SFML/Graphics.hpp>

#define BOT_COUNT 10
#define BOT_HEIGHT 64
#define BOT_WIDTH 56
#define BULLET_COUNT 10
#define FRAME_MULTIPLIER 0.025

// ���� ����. ��������� ��� ������� �� ����� �����
extern sf::RenderWindow * win;

// ������� ������� � ������� ������
extern short KILLED_IN_MISSION;
// ������������ ��������� ����
enum GAME_STATE { MAIN_MENU, PLAYING, PAUSE, SETTINGS };
// ������� ��������� ���� (������)
extern GAME_STATE STATE;

// ��������������� �������: ������� ������ ������
// ������� ����:
void ClickPlay(sf::RenderWindow * win);
void ClickSettings(sf::RenderWindow * win);
void ClickGameExit(sf::RenderWindow * win);