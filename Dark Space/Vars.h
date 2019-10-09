#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Bot.h"
#include "Player.h"
#include "Bullet.h"
#include "Button.h"
#include "CheckBox.h"

#define BOT_COUNT 10
#define BOT_HEIGHT 64
#define BOT_WIDTH 56
#define BULLET_COUNT 10
#define FRAME_MULTIPLIER 0.025

// ОКНО ИГРЫ. РАСШАРЕНО ДЛЯ ДОСТУПА ИЗ ЛЮБОЙ ТОЧКИ
extern sf::RenderWindow * win;

// музыка
extern sf::Music * BackgroundMusic;
// звуки
extern sf::SoundBuffer * SoundBuffer;
extern sf::Sound * Sound;

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
// НАСТРОЙКИ:
void ClickMusic();
void ClickSound();
void ClickFullScreen();
// ПАУЗА
void ClickContinue(sf::RenderWindow * win);
void ClickSaveGame(sf::RenderWindow * win);
void ClickExit(sf::RenderWindow * win);