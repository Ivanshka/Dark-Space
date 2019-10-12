#include <iostream>

#include "Vars.h"
#include <fstream>

short KILLED_IN_MISSION = 0; // счетчик убийств

GAME_STATE STATE = GAME_STATE::MAIN_MENU;

// музыка
sf::Music * BackgroundMusic = nullptr;

// звуки
sf::SoundBuffer * SoundBuffer = nullptr;
sf::Sound * Sound = nullptr;

void LoadSettings() {

}

// Проверка существования файла
bool FileIsExist(std::string filePath)
{
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
void ClickPlay(sf::RenderWindow * win) {
	//(*BackgroundMusic).stop();
	(*BackgroundMusic).openFromFile("sounds/battle.ogg");
	(*BackgroundMusic).play();
	STATE = GAME_STATE::PLAYING;
	win->setMouseCursorVisible(false);
}

// Вход в настройки
void ClickSettings(sf::RenderWindow * win) {
	STATE = GAME_STATE::SETTINGS;
}

// Выход из игры
void ClickGameExit(sf::RenderWindow * win) {
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

}

// полноэкранный режим
void ClickFullScreen() {

}

// выход из настроек
void ClickSettingsExit(sf::RenderWindow* win)
{
	// тут сохраняем настройки
	STATE = GAME_STATE::MAIN_MENU;
}

// ПАУЗА

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