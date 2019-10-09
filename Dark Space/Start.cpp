#pragma once

#include <iostream>
#include <vector>
#include <list>
#include <thread>
#include <ctime>
#include <string>
#include <sstream>

#include "Vars.h"

using namespace std;
using namespace sf;

int FPS = 0;
void fpsc()
{
	while (true)
	{
		sleep(milliseconds(1000));
		cout << "FPS = " << FPS << endl;
		FPS = 0;
	}
}

int main(int argc, char *argv[])
{
	setlocale(LC_ALL, "Rus");

	RenderWindow * win;
	if (argc > 1)
		win = new RenderWindow(VideoMode(800, 600), "Dark Space", Style::Fullscreen);
	else
		win = new RenderWindow(VideoMode(800, 600), "Dark Space");

	//win->setMouseCursorVisible(false);

	// ПОДГОТОВКА

	// часы
	Clock clock;
	// инициализация генератора случайных чисел
	srand(time(0));

	// вспомогательные материалы:
	// текстуры и спрайты:
	Texture tBackground; tBackground.loadFromFile("images/space.png"); // фон главного меню
	Sprite sBackground; sBackground.setTexture(tBackground);
	Texture tBullet; tBullet.loadFromFile("images/fire.png"); // атака
	Texture tBot; tBot.loadFromFile("images/enemy.png"); // враги
	Texture tMenu; tMenu.loadFromFile("images/menu.png"); // фон меню паузы
	Sprite sMenu; sMenu.setTexture(tMenu);
	Texture tButtonPlay; tButtonPlay.loadFromFile("images/gui/buttonPlay.png"); // кнопка "играть"
	Texture tButtonSettings; tButtonSettings.loadFromFile("images/gui/buttonSettings.png"); // кнопка "настройки"
	Texture tButtonExit; tButtonExit.loadFromFile("images/gui/buttonExit.png"); // кнопка "выход"
	Texture tDisCheckBox; tDisCheckBox.loadFromFile("images/gui/DisabledCheckBox.png");
	Texture tEnCheckBox; tEnCheckBox.loadFromFile("images/gui/EnabledCheckBox.png");

	// инициализация объектов:
	Player player(100, 100, "images/player.png");
	Bot * bots = new Bot[BOT_COUNT];
	Bullet * bullets = new Bullet[BULLET_COUNT];
	for (int i = 0; i < BOT_COUNT; i++)
		bots[i] = Bot(0 + rand() % 704, -(64 + rand() % 800), 0.16f, 100., &tBot);
	for (int i = 0; i < BULLET_COUNT; i++)
		bullets[i] = Bullet(-8, -600, 0.64f, &tBullet);
	// инициализация счетчика
	int bulIterator = 0;

	// инфопанель, здоровье и кол-во убитых
	Texture tInfopanel; tInfopanel.loadFromFile("images/infopanel.png");
	Sprite sInfopanel(tInfopanel);
	RectangleShape health(Vector2f(200., 30.));
	health.setPosition(Vector2f(530, 52));
	Font font;
	font.loadFromFile("calibri.ttf");
	Text killed("", font, 30);
	killed.setFillColor(Color::Red);
	killed.setOutlineColor(Color::Red);
	killed.setPosition(25, 30);
	ostringstream sKILLED_IN_MISSION;

	// поток для вывода fps 
	thread thr(fpsc);
	// время
	float elapsed;

	// координаты мыши для возврата в игру из меню
	Vector2i SAVED_MOUSE_POINT;

	// музыка. из-з невозможности засунуть музыку в кучу делаем костыль через расшаренность указателем
	Music Music;
	BackgroundMusic = &Music; // указатель mMainMenu extern'овский
	if (!Music.openFromFile("sounds/menu.ogg"))
		cout << "Not found: sounds/menu.ogg";
	else
		Music.play();
	Music.setLoop(true);
	//звуки
	sf::SoundBuffer HpSBuffer;
	if (!HpSBuffer.loadFromFile("sounds/hp.ogg"))
		cout << "Not found: sounds/hp.ogg";
	sf::Sound HpSound;
	HpSound.setBuffer(HpSBuffer);

	// кнопки менюшек
	// главное меню
	Button bPlay(100, 100, &tButtonPlay, ClickPlay);
	Button bSettings(100, 180, &tButtonSettings, ClickSettings);
	Button bGameExit(100, 260, &tButtonExit, ClickGameExit);
	// настройки
	CheckBox cbMusic(100, 100, &tEnCheckBox, &tDisCheckBox, ClickMusic);
	// недоделаный вариант с программным текстом
	/*Text tPlay("ИГРАТЬ", font, 20); tPlay.setPosition()
	Text tSettings("НАСТРОЙКИ", font, 20);
	Text tExit("ВЫХОД", font, 20);
	{
		Color clr(102, 102, 238);
		tPlay.setFillColor(clr);    tSettings.setFillColor(clr);    tExit.setFillColor(clr);
		tPlay.setOutlineColor(clr); tSettings.setOutlineColor(clr); tExit.setOutlineColor(clr);
	}*/

	while (win->isOpen())
	{
		elapsed = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		elapsed /= 1600; //регулировка скорости игры

		// положение мыши в окне
		Vector2f MousePos = win->mapPixelToCoords(Mouse::getPosition(*win));
		Event event;
		while (win->pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				win->close();
			}
			if (event.type == Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == Mouse::Button::Left)
				{
					switch (STATE)
					{
					case MAIN_MENU:
						bPlay.Update(MousePos, win);
						bSettings.Update(MousePos, win);
						bGameExit.Update(MousePos, win);
						break;
					case PLAYING:
						HpSound.play();
						if (player.Hp > 0)
						{
							bullets[bulIterator].Damage = 35 + rand() % 65;
							bullets[bulIterator].sprite.setPosition(bullets[bulIterator].X = MousePos.x - 4, bullets[bulIterator].Y = MousePos.y - 70);
							bulIterator++;
							if (bulIterator == BULLET_COUNT)
								bulIterator = 0;
						}
						break;
					case SETTINGS:
						cbMusic.Update(MousePos, win);
					}
					
				}
			}
			if (event.type == Event::KeyReleased)
			{
				if (event.key.code == Keyboard::Escape)
				{
					switch (STATE) {
					case PLAYING:
						STATE = PAUSE;
						SAVED_MOUSE_POINT = Mouse::getPosition();
						win->setMouseCursorVisible(true);
						break;
					case PAUSE:
						STATE = PLAYING;
						win->setMouseCursorVisible(false);
						Mouse::setPosition(SAVED_MOUSE_POINT);
						break;
					case SETTINGS:
						STATE = MAIN_MENU;
					default:
						break;
					}
				}
			}
		}

		win->clear();

		// обновление
		if (STATE == PLAYING)
		{
			if (player.Hp > 0)
			{
				health.setSize(Vector2f(player.Hp * 2, 30));
				if (player.Hp > 66)
					health.setFillColor(Color::Green);
				else if (player.Hp > 33)
					health.setFillColor(Color::Yellow);
				else health.setFillColor(Color::Red);
				player.Update(MousePos, bots, elapsed);
				for (int i = 0; i < BOT_COUNT; i++)
					bots[i].Update(elapsed);
				for (int i = 0; i < BULLET_COUNT; i++)
					bullets[i].Update(bots, elapsed);
			}
			else
			{
				health.setSize(Vector2f(0, 30));
				win->setMouseCursorVisible(true);
			}

			// строка для вывода кол-ва убитых
			sKILLED_IN_MISSION.str(""); // очистка текстового потока
			sKILLED_IN_MISSION << KILLED_IN_MISSION << endl;
			killed.setString(sKILLED_IN_MISSION.str());
		}

		// отрисовка
		win->draw(sBackground); // фон
		switch (STATE)
		{
		case MAIN_MENU: // ГЛАВНОЕ МЕНЮ
			win->draw(bPlay.Rect); 
			win->draw(bSettings.Rect);
			win->draw(bGameExit.Rect);
			break;
		case PLAYING: // ИГРА
			for (int i = 0; i < BOT_COUNT; i++) // боты
				win->draw(bots[i].sprite);
			win->draw(player.sprite); // игрок
			for (int i = 0; i < BULLET_COUNT; i++) // лазеры
				win->draw(bullets[i].sprite);
			win->draw(sInfopanel); // инфопанель
			win->draw(health); // полоса хп
			win->draw(killed); // число убитых
			break;
		case PAUSE: // ПАУЗА ИГРЫ
			win->draw(sMenu);
			break;
		case SETTINGS:
			win->draw(cbMusic.Rect);
			break;
		}
		
		win->display();
		FPS++;
	}
	return 0;
}