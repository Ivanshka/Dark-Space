#pragma once

#include <SFML/Graphics.hpp>

#define BOT_COUNT 10
#define BOT_HEIGHT 64
#define BOT_WIDTH 56
#define BULLET_COUNT 10
#define FRAME_MULTIPLIER 0.025

// ОКНО ИГРЫ. РАСШАРЕНО ДЛЯ ДОСТУПА ИЗ ЛЮБОЙ ТОЧКИ
extern sf::RenderWindow * win;

// счетчик убийств в текущей миссии
extern short KILLED_IN_MISSION;
// перечисление состояний игры
enum GAME_STATE { MAIN_MENU, PLAYING, PAUSE, SETTINGS };
// текущее состояние игры (экраны)
extern GAME_STATE STATE;

// ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ: ФУНКЦИИ РАБОТЫ КНОПОК
// ГЛАВНОЕ МЕНЮ:
void ClickPlay(sf::RenderWindow * win);
void ClickSettings(sf::RenderWindow * win);
void ClickGameExit(sf::RenderWindow * win);