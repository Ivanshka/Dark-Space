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

// ���� ����. ��������� ��� ������� �� ����� �����
extern sf::RenderWindow * win;

// ������
extern sf::Music * BackgroundMusic;
// �����
extern sf::SoundBuffer * SoundBuffer;
extern sf::Sound * Sound;

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
// ���������:
void ClickMusic();
void ClickSound();
void ClickFullScreen();
// �����
void ClickContinue(sf::RenderWindow * win);
void ClickSaveGame(sf::RenderWindow * win);
void ClickExit(sf::RenderWindow * win);