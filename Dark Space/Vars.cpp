#include <iostream>

#include "Vars.h"
#include <fstream>

// Флаг работы игры
bool GAMING = true;

// окно игры
RenderWindow* win = nullptr;

// СИСТЕМА АТАКИ

// Флаг атаки
bool IsAttacking = false;
// Время атаки
float AttackTime = 0;

// игровой фон
Texture tBackground;

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
bool bSettingsSounds = true;
// Параметр музыки
bool bSettingsMusic = true;
// Параметр полноэкраного режима
bool bSettingsFullScreen = true;

// Уровень
unsigned char level = 1;

// Загрузка настроек
void LoadSettings() {
	cout << "Here must be loading of settings!\n";
	// если существует файл настроек, загружаем их
	if (FileExist("settings.txt"))
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

// Загрузка сохранения
void LoadSave()
{
	if (FileExist("save.bin"))
	{
		std::ifstream in("save.bin");          // поток для записи
		in >> level;
	}
	else
	{
		std::ofstream out("save.bin");
		out << "1";
		level = 1;
	}
}

// Сохранение игры

// Проверка существования файла
bool FileExist(std::string filePath) {
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
	bSettingsFullScreen = !bSettingsFullScreen;
}

// Выход из настроек: сохранение настроек
void ClickSettingsExit() {
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
	std::ofstream out("save.bin");
	out << level;
	out.close();
}

// Главное меню
void ClickMainMenu() {
	IsAttacking = false;
	tBackground.loadFromFile("images/space.png");
	(*BackgroundMusic).openFromFile("sounds/menu.ogg");
	if (bSettingsMusic)(*BackgroundMusic).play();
	STATE = GAME_STATE::MAIN_MENU;
}
