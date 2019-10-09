#include <iostream>

#include "Vars.h"

short KILLED_IN_MISSION = 0; // ������� �������

GAME_STATE STATE = MAIN_MENU;

// ������
sf::Music * BackgroundMusic = nullptr;

// �����
extern sf::SoundBuffer * SoundBuffer = nullptr;
extern sf::Sound * Sound = nullptr;

// ������� ��������� ������� ������

// ������� ����
// ������ ����
void ClickPlay(sf::RenderWindow * win) {
	//(*BackgroundMusic).stop();
	(*BackgroundMusic).openFromFile("sounds/battle.ogg");
	(*BackgroundMusic).play();
	STATE = PLAYING;
	win->setMouseCursorVisible(false);
}

// ���� � ���������
void ClickSettings(sf::RenderWindow * win) {
	STATE = SETTINGS;
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

