#include <iostream>

#include "Vars.h"
#include <fstream>

// ���� ������ ����
bool GAMING = true;

// ���� ����
RenderWindow* win = nullptr;

// ������� �����

// ���� �����
bool IsAttacking = false;
// ����� �����
float AttackTime = 0;

// ������� ���
Texture tBackground;

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
bool bSettingsSounds = true;
// �������� ������
bool bSettingsMusic = true;
// �������� ������������� ������
bool bSettingsFullScreen = true;

// �������
unsigned char level = 1;

// �������� ��������
void LoadSettings() {
	cout << "Here must be loading of settings!\n";
	// ���� ���������� ���� ��������, ��������� ��
	if (FileExist("settings.txt"))
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

// �������� ����������
void LoadSave()
{
	if (FileExist("save.bin"))
	{
		std::ifstream in("save.bin");          // ����� ��� ������
		in >> level;
	}
	else
	{
		std::ofstream out("save.bin");
		out << "1";
		level = 1;
	}
}

// ���������� ����

// �������� ������������� �����
bool FileExist(std::string filePath) {
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
	{
		bots[i].Reset();
		bullets[i].Reset();
	}
	KILLED_IN_MISSION = 0;
	(*BackgroundMusic).openFromFile("sounds/battle.ogg");
	if (bSettingsMusic)(*BackgroundMusic).play();
	player->Hp = 100;

	switch (level)
	{
	case '1': tBackground.loadFromFile("images/levels/stars.png"); break;
	case '2': tBackground.loadFromFile("images/levels/milkyway.png"); break;
	case '3': tBackground.loadFromFile("images/levels/orionnebula.png"); break;
	case '4': tBackground.loadFromFile("images/levels/snailnebula.png"); break;
	case '5': tBackground.loadFromFile("images/levels/thegiantnebulainkiel.png"); break;
	case '6': tBackground.loadFromFile("images/levels/theomegam17nebula.png"); break;
	case '7': tBackground.loadFromFile("images/levels/wanttoknow.png"); break;
	}

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
	bSettingsFullScreen = !bSettingsFullScreen;
}

// ����� �� ��������: ���������� ��������
void ClickSettingsExit() {
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
	std::ofstream out("save.bin");
	out << level;
	out.close();
}

// ������� ����
void ClickMainMenu() {
	IsAttacking = false;
	tBackground.loadFromFile("images/space.png");
	(*BackgroundMusic).openFromFile("sounds/menu.ogg");
	if (bSettingsMusic)(*BackgroundMusic).play();
	STATE = GAME_STATE::MAIN_MENU;
}
