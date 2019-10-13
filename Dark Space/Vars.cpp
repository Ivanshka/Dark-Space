#include <iostream>

#include "Vars.h"
#include <fstream>

// ���� ����
RenderWindow* win = nullptr;

// ������� �������
Player* player = nullptr;
Bot* bots = nullptr;
Bullet* bullets = nullptr;

short KILLED_IN_MISSION = 0; // ������� �������

GAME_STATE STATE = GAME_STATE::MAIN_MENU;

// ������
sf::Music * BackgroundMusic = nullptr;

// �����
sf::SoundBuffer * SoundBuffer = nullptr;
sf::Sound * Sound = nullptr;

void LoadSettings() {

}

// �������� ������������� �����
bool FileIsExist(std::string filePath)
{
	bool isExist = false;
	std::ifstream fin(filePath.c_str());

	if (fin.is_open())
		isExist = true;

	fin.close();
	return isExist;
}

// ������� ��������� ������� ������

// ������� ����
// ������ ����
void ClickPlay() {
	for (int i = 0; i < BOT_COUNT; i++)
		bots[i].ResetBot();
	KILLED_IN_MISSION = 0;
	(*BackgroundMusic).openFromFile("sounds/battle.ogg");
	(*BackgroundMusic).play();
	player->Hp = 100;
	STATE = GAME_STATE::PLAYING;
	win->setMouseCursorVisible(false);
}

// ���� � ���������
void ClickSettings() {
	STATE = GAME_STATE::SETTINGS;
}

// ����� �� ����
void ClickGameExit() {
	win->close();
}

// ���������
// ������
void ClickMusic() {
	if ((*BackgroundMusic).getStatus() == sf::Music::Status::Paused)
		(*BackgroundMusic).play();
	else
		(*BackgroundMusic).pause();
}

// �����
void ClickSound() {

}

// ������������� �����
void ClickFullScreen() {

}

// ����� �� ��������
void ClickSettingsExit()
{
	// ��� ��������� ���������
	STATE = GAME_STATE::MAIN_MENU;
}

// �����
// ����������
void ClickContinue()
{
	STATE = GAME_STATE::PLAYING;
}
// ���������
void ClickSaveGame()
{
	cout << "SaveGame is pressed!";
}
// ������� ����
void ClickMainMenu()
{
	(*BackgroundMusic).openFromFile("sounds/menu.ogg");
	(*BackgroundMusic).play();
	STATE = GAME_STATE::MAIN_MENU;
}