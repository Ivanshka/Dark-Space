#include <iostream>

#include "Vars.h"

short KILLED_IN_MISSION = 0; // счетчик убийств

GAME_STATE STATE = MAIN_MENU;

// музыка
sf::Music * BackgroundMusic = nullptr;

// звуки
extern sf::SoundBuffer * SoundBuffer = nullptr;
extern sf::Sound * Sound = nullptr;

// ФУНКЦИИ ОБРАБОТКИ НАЖАТИЯ КЛАВИШ

// главное меню
// Начало игры
void ClickPlay(sf::RenderWindow * win) {
	//(*BackgroundMusic).stop();
	(*BackgroundMusic).openFromFile("sounds/battle.ogg");
	(*BackgroundMusic).play();
	STATE = PLAYING;
	win->setMouseCursorVisible(false);
}

// Вход в настройки
void ClickSettings(sf::RenderWindow * win) {
	STATE = SETTINGS;
}

// Выход из игры
void ClickGameExit(sf::RenderWindow * win) {
	win->close();
}

// настройки
// Музыка
void ClickMusic() {
	if ((*BackgroundMusic).getStatus() == sf::Music::Status::Paused)
		(*BackgroundMusic).play();
	else
		(*BackgroundMusic).pause();
}

