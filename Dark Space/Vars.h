#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Bot.h"
#include "Player.h"
#include "Bullet.h"
#include "Button.h"
#include "CheckBox.h"

// Количество ботов
#define BOT_COUNT 10
// Высота спрайта бота
#define BOT_HEIGHT 64
// Ширина спрайта бота
#define BOT_WIDTH 56
// Количество атак
#define BULLET_COUNT 10
// Кадровый множитель. Регулирует скорость анимации.
#define FRAME_MULTIPLIER 0.025


// Окно игры
extern sf::RenderWindow* win;

// Настройки игры
//bool bSettingsSounds;
//bool bSettingsMusic;
//bool bSettingsFullScreen;
// Загрузка настроек
void LoadSettings();

// Фоновая музыка
extern sf::Music* BackgroundMusic;
// Звуки
extern sf::Sound* Sound;
// Звуковой буфер
extern sf::SoundBuffer* SoundBuffer;

// Счетчик убийств в текущей миссии
extern short KILLED_IN_MISSION;

// Состояния игры
enum class GAME_STATE { MAIN_MENU, PLAYING, PAUSE, SETTINGS, GAME_OVER };

// текущее состояние игры (экраны)
extern GAME_STATE STATE;

// ИГРОВЫЕ ОБЪЕКТЫ

// Объект игрока
extern Player* player;
// Массив объектов ботов
extern Bot* bots;
// Массив объектов атак
extern Bullet* bullets;

// ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ: ФУНКЦИИ РАБОТЫ КНОПОК

// ГЛАВНОЕ МЕНЮ:

// Запуск игры
void ClickPlay();
// Вход в настройки
void ClickSettings();
// Выход из игры
void ClickGameExit();

// НАСТРОЙКИ:

// Включение / выключение музыки
void ClickMusic();
// Включение / выключение звуков
void ClickSound();
// Включение / выключение полноэкранного режима
void ClickFullScreen();
// Выход из настроек
void ClickSettingsExit();

// ПАУЗА

// Продолжение игры
void ClickContinue();
// Сохранение игры
void ClickSaveGame();
// Выход в главное меню игры
void ClickMainMenu();