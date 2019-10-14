#include <iostream>

#include "Vars.h"
#include <fstream>

// ���� ����
RenderWindow* win = nullptr;

// ������� �������
Player* player = nullptr;
Bot* bots = nullptr;
Bullet* bullets = nullptr;

// ������� �������
short KILLED_IN_MISSION = 0;

// ������� ��������� ����
GAME_STATE STATE = GAME_STATE::MAIN_MENU;

// ������� ������
sf::Music * BackgroundMusic = nullptr;

// �����
sf::SoundBuffer * SoundBuffer = nullptr;
sf::Sound * Sound = nullptr;

// ���������
// �������� �����
extern bool bSettingsSounds = true;
// �������� ������
extern bool bSettingsMusic = true;
// �������� ������������� ������
extern bool bSettingsFullScreen = true;

// �������� ��������
void LoadSettings() {
	cout << "Here must be loading of settings!\n";
	// ���� ���������� ���� ��������, ��������� ��
	if (FileIsExist("settings.txt"))
	{
		ifstream in;          // ����� ��� ������
		in.open("settings.txt");
		//char buf;
		in >> bSettingsSounds;
		in >> bSettingsMusic;
		in >> bSettingsFullScreen;
		cout << "Settings:\nbSound: " << (bSettingsSounds == true) << "\nMusic: " << (bSettingsMusic == true) << "\nFullScreen: " << (bSettingsFullScreen == true) << endl;
		in.close();
	}
	else // ����� ������ ����������� ���������, ����������� ���, � ��������� �� � ���� ��������
	{
		std::ofstream out("settings.txt");          // ����� ��� ������
		out << "1\n1\n1";
		bSettingsSounds = true;
		bSettingsMusic = true;
		bSettingsFullScreen = true;
		out.close();
	}
}

// �������� ������������� �����
bool FileIsExist(std::string filePath) {
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
	if (bSettingsMusic)(*BackgroundMusic).play();
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
	bSettingsMusic = !bSettingsMusic;
	if ((*BackgroundMusic).getStatus() == sf::Music::Status::Paused)
		(*BackgroundMusic).play();
	else
	{
		(*BackgroundMusic).play();
		(*BackgroundMusic).pause();
	}
	cout << (*BackgroundMusic).getStatus() << endl;
}

// �����
void ClickSound() {
	bSettingsSounds = !bSettingsSounds; //cout << "Sound control is in developing!\n";
}

// ������������� �����
void ClickFullScreen() {
	bSettingsFullScreen = !bSettingsFullScreen; //cout << "Fullscreen control is in developing!\n";
}

// ����� �� ��������
void ClickSettingsExit() {
	// ��� ��������� ���������
	// cout << "Here must be settings saving!\n";
	ofstream out("settings.txt");
	out << bSettingsSounds << endl << bSettingsMusic << endl << bSettingsFullScreen;
	out.close();
	STATE = GAME_STATE::MAIN_MENU;
}

// �����

// ����������
void ClickContinue() {
	win->setMouseCursorVisible(false);
	STATE = GAME_STATE::PLAYING;
}

// ���������
void ClickSaveGame() {
	cout << "Game saving is in developing!\n";
}

// ������� ����
void ClickMainMenu() {
	(*BackgroundMusic).openFromFile("sounds/menu.ogg");
	if (bSettingsMusic)(*BackgroundMusic).play();
	STATE = GAME_STATE::MAIN_MENU;
}
