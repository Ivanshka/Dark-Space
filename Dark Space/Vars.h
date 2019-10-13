#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Bot.h"
#include "Player.h"
#include "Bullet.h"
#include "Button.h"
#include "CheckBox.h"

// ���������� �����
#define BOT_COUNT 10
// ������ ������� ����
#define BOT_HEIGHT 64
// ������ ������� ����
#define BOT_WIDTH 56
// ���������� ����
#define BULLET_COUNT 10
// �������� ���������. ���������� �������� ��������.
#define FRAME_MULTIPLIER 0.025


// ���� ����
extern sf::RenderWindow* win;

// ��������� ����
//bool bSettingsSounds;
//bool bSettingsMusic;
//bool bSettingsFullScreen;
// �������� ��������
void LoadSettings();

// ������� ������
extern sf::Music* BackgroundMusic;
// �����
extern sf::Sound* Sound;
// �������� �����
extern sf::SoundBuffer* SoundBuffer;

// ������� ������� � ������� ������
extern short KILLED_IN_MISSION;

// ��������� ����
enum class GAME_STATE { MAIN_MENU, PLAYING, PAUSE, SETTINGS, GAME_OVER };

// ������� ��������� ���� (������)
extern GAME_STATE STATE;

// ������� �������

// ������ ������
extern Player* player;
// ������ �������� �����
extern Bot* bots;
// ������ �������� ����
extern Bullet* bullets;

// ��������������� �������: ������� ������ ������

// ������� ����:

// ������ ����
void ClickPlay();
// ���� � ���������
void ClickSettings();
// ����� �� ����
void ClickGameExit();

// ���������:

// ��������� / ���������� ������
void ClickMusic();
// ��������� / ���������� ������
void ClickSound();
// ��������� / ���������� �������������� ������
void ClickFullScreen();
// ����� �� ��������
void ClickSettingsExit();

// �����

// ����������� ����
void ClickContinue();
// ���������� ����
void ClickSaveGame();
// ����� � ������� ���� ����
void ClickMainMenu();