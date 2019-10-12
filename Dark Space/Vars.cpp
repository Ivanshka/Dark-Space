#include <iostream>

#include "Vars.h"
#include <fstream>

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
void ClickPlay(sf::RenderWindow * win) {
	//(*BackgroundMusic).stop();
	(*BackgroundMusic).openFromFile("sounds/battle.ogg");
	(*BackgroundMusic).play();
	STATE = GAME_STATE::PLAYING;
	win->setMouseCursorVisible(false);
}

// ���� � ���������
void ClickSettings(sf::RenderWindow * win) {
	STATE = GAME_STATE::SETTINGS;
}

// ����� �� ����
void ClickGameExit(sf::RenderWindow * win) {
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
void ClickSettingsExit(sf::RenderWindow* win)
{
	// ��� ��������� ���������
	STATE = GAME_STATE::MAIN_MENU;
}

// �����

void ClickContinue(sf::RenderWindow* win)
{
	STATE = GAME_STATE::PLAYING;
}

void ClickSaveGame(sf::RenderWindow* win)
{
	
}

void ClickExit(sf::RenderWindow* win)
{
	STATE = GAME_STATE::MAIN_MENU;
}