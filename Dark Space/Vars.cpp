#include <iostream>

#include "Vars.h"
#include <fstream>

// окно игры
RenderWindow* win = nullptr;

// ИГРОВЫЕ ОБЪЕКТЫ
Player* player = nullptr;
Bot* bots = nullptr;
Bullet* bullets = nullptr;

short KILLED_IN_MISSION = 0; // счетчик убийств

GAME_STATE STATE = GAME_STATE::MAIN_MENU;

// музыка
sf::Music * BackgroundMusic = nullptr;

// звуки
sf::SoundBuffer * SoundBuffer = nullptr;
sf::Sound * Sound = nullptr;

void LoadSettings() {
	cout << "Here must be loading of settings!\n";
}

// Проверка существования файла
bool FileIsExist(std::string filePath) {
	bool isExist = false;
	std::ifstream fin(filePath.c_str());

	if (fin.is_open())
		isExist = true;

	fin.close();
	return isExist;
}

// ФУНКЦИИ ОБРАБОТКИ НАЖАТИЯ КЛАВИШ

// ГЛАВНОЕ МЕНЮ
// Начало игры
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

// Вход в настройки
void ClickSettings() {
	STATE = GAME_STATE::SETTINGS;
}

// Выход из игры
void ClickGameExit() {
	win->close();
}

// НАСТРОЙКИ
// Музыка
void ClickMusic() {
	if ((*BackgroundMusic).getStatus() == sf::Music::Status::Paused)
		(*BackgroundMusic).play();
	else
		(*BackgroundMusic).pause();
}

// звуки
void ClickSound() {
	cout << "Sound control is in developing!\n";
}

// полноэкранный режим
void ClickFullScreen() {
	cout << "Fullscreen control is in developing!\n";
}

// выход из настроек
void ClickSettingsExit() {
	// тут сохраняем настройки
	cout << "Here must be settings saving!\n";
	STATE = GAME_STATE::MAIN_MENU;
}

// ПАУЗА
// продолжить
void ClickContinue() {
	win->setMouseCursorVisible(false);
	STATE = GAME_STATE::PLAYING;
}
// сохранить
void ClickSaveGame() {
	cout << "Game saving is in developing!\n";
}
// главное меню
void ClickMainMenu() {
	(*BackgroundMusic).openFromFile("sounds/menu.ogg");
	(*BackgroundMusic).play();
	STATE = GAME_STATE::MAIN_MENU;
}
