#include <iostream>

#include "Vars.h"
#include <fstream>

// окно игры
RenderWindow* win = nullptr;

// ИГРОВЫЕ ОБЪЕКТЫ
Player* player = nullptr;
Bot* bots = nullptr;
Bullet* bullets = nullptr;

// Счетчик убийств
short KILLED_IN_MISSION = 0;

// Текущее состояние игры
GAME_STATE STATE = GAME_STATE::MAIN_MENU;

// Фоновая музыка
sf::Music * BackgroundMusic = nullptr;

// Звуки
sf::SoundBuffer * SoundBuffer = nullptr;
sf::Sound * Sound = nullptr;

// НАСТРОЙКИ
// Параметр звука
extern bool bSettingsSounds = true;
// Параметр музыки
extern bool bSettingsMusic = true;
// Параметр полноэкраного режима
extern bool bSettingsFullScreen = true;

// Загрузка настроек
void LoadSettings() {
	cout << "Here must be loading of settings!\n";
	// если существует файл настроек, загружаем их
	if (FileIsExist("settings.txt"))
	{
		ifstream in;          // поток для чтения
		in.open("settings.txt");
		//char buf;
		in >> bSettingsSounds;
		in >> bSettingsMusic;
		in >> bSettingsFullScreen;
		cout << "Settings:\nbSound: " << (bSettingsSounds == true) << "\nMusic: " << (bSettingsMusic == true) << "\nFullScreen: " << (bSettingsFullScreen == true) << endl;
		in.close();
	}
	else // иначе ставит стандартные настройки, прописанные тут, и сохраняем их в файл настроек
	{
		std::ofstream out("settings.txt");          // поток для записи
		out << "1\n1\n1";
		bSettingsSounds = true;
		bSettingsMusic = true;
		bSettingsFullScreen = true;
		out.close();
	}
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
	if (bSettingsMusic)(*BackgroundMusic).play();
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

// Звуки
void ClickSound() {
	bSettingsSounds = !bSettingsSounds; //cout << "Sound control is in developing!\n";
}

// Полноэкранный режим
void ClickFullScreen() {
	bSettingsFullScreen = !bSettingsFullScreen; //cout << "Fullscreen control is in developing!\n";
}

// Выход из настроек
void ClickSettingsExit() {
	// тут сохраняем настройки
	// cout << "Here must be settings saving!\n";
	ofstream out("settings.txt");
	out << bSettingsSounds << endl << bSettingsMusic << endl << bSettingsFullScreen;
	out.close();
	STATE = GAME_STATE::MAIN_MENU;
}

// ПАУЗА

// Продолжить
void ClickContinue() {
	win->setMouseCursorVisible(false);
	STATE = GAME_STATE::PLAYING;
}

// Сохранить
void ClickSaveGame() {
	cout << "Game saving is in developing!\n";
}

// Главное меню
void ClickMainMenu() {
	(*BackgroundMusic).openFromFile("sounds/menu.ogg");
	if (bSettingsMusic)(*BackgroundMusic).play();
	STATE = GAME_STATE::MAIN_MENU;
}
