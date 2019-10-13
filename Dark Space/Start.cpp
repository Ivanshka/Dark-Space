#pragma once

#include <iostream>
#include <stdio.h> // ��� printf
#include <sstream>
#include <fstream>
#include <vector>
#include <list>
#include <thread>
#include <ctime>
#include <string>

#include "Vars.h"

using namespace std;
using namespace sf;

int FPS = 0;
int circles = 0;
int AllFPS = 0;
void fpsOut()
{
	std::ofstream out;          // ����� ��� ������
	out.open("logFPS.log");
	while (true)
	{
		sleep(milliseconds(1000));
		circles++;
		AllFPS += FPS;
		printf("Circle: %3i   FPS: %4i   aFPS: %4i   fFPS: %6i\n", circles, FPS, (AllFPS / circles), AllFPS);
		out << "Circle = " << circles << "FPS = " << FPS << ", average = " << (AllFPS / circles) << ", full = " << AllFPS<< endl;
		FPS = 0;
	}
}

int main(int argc, char *argv[])
{
	//setlocale(LC_ALL, "Rus");

	if (argc > 1)
		win = new RenderWindow(VideoMode(800, 600), "Dark Space", Style::Fullscreen);
	else
		win = new RenderWindow(VideoMode(800, 600), "Dark Space");

	// ����������

	// ����
	Clock clock;
	// ������������� ���������� ��������� �����
	srand((unsigned int)time(0));

	// ��������������� ���������:
	// �������� � �������:
	Texture tBackground; tBackground.loadFromFile("images/space.png"); // ��� �������� ����
	Sprite sBackground(tBackground);
	Texture tMenu; tMenu.loadFromFile("images/menu.png"); // ��� ���� �����
	Sprite sMenu(tMenu);
	Texture tInfopanel; tInfopanel.loadFromFile("images/infopanel.png"); // ����������
	Sprite sInfopanel(tInfopanel);
	Texture tBullet; tBullet.loadFromFile("images/fire.png"); // �����
	Texture tBot; tBot.loadFromFile("images/enemy.png"); // �����
	Texture tButton; tButton.loadFromFile("images/gui/button.png"); // ������
	Texture tDisCheckBox; tDisCheckBox.loadFromFile("images/gui/DisabledCheckBox.png"); // ����������� �������
	Texture tEnCheckBox; tEnCheckBox.loadFromFile("images/gui/EnabledCheckBox.png"); // ���������� �������

	// ������������� ��������:
	player = new Player(100, 100, "images/player.png");
	bots = new Bot[BOT_COUNT];
	bullets = new Bullet[BULLET_COUNT];
	for (int i = 0; i < BOT_COUNT; i++)
		bots[i] = Bot(0 + rand() % 704, -(64 + rand() % 800), 0.16f, 100., &tBot);
	for (int i = 0; i < BULLET_COUNT; i++)
		bullets[i] = Bullet(-8, -600, 0.64f, &tBullet);
	// ������������� �������� ����
	int bulIterator = 0;

	// ����������: �������� � ���-�� ������
	RectangleShape health(Vector2f(200., 30.));
	health.setPosition(Vector2f(530, 52));
	Font font;
	font.loadFromFile("calibri.ttf");
	Text killed("", font, 30);
	killed.setFillColor(Color::Red);
	killed.setOutlineColor(Color::Red);
	killed.setPosition(25, 30);
	ostringstream sKILLED_IN_MISSION;

	// ����� �����
	float elapsed;

	// ���������� ���� ��� �������� � ���� �� ����
	Vector2i SAVED_MOUSE_POINT;

	// ������
	BackgroundMusic = new Music(); // ��������� mMainMenu extern'������
	if (BackgroundMusic->openFromFile("sounds/menu.ogg"))
		BackgroundMusic->play();
	BackgroundMusic->setLoop(true);
	//�����
	sf::SoundBuffer HpSBuffer;
	HpSBuffer.loadFromFile("sounds/hp.ogg");
	sf::Sound HpSound;
	HpSound.setBuffer(HpSBuffer);

	// ������ �������
	// ������� ����
	Button bPlay(100, 195, &tButton, ClickPlay);
	Button bSettings(100, 275, &tButton, ClickSettings);
	Button bGameExit(100, 355, &tButton, ClickGameExit);
	Text tPlay(L"������", font, 27); tPlay.setPosition(149, 202);
	Text tSettings(L"���������", font, 27); tSettings.setPosition(121, 282);
	Text tGameExit(L"�����", font, 27); tGameExit.setPosition(148, 362);
	// ���������
	CheckBox cbSounds(585, 205, &tEnCheckBox, &tDisCheckBox, ClickSound, true);
	CheckBox cbMusic(585, 275, &tEnCheckBox, &tDisCheckBox, ClickMusic, true);
	CheckBox cbFullScreen(585, 345, &tEnCheckBox, &tDisCheckBox, ClickFullScreen, true);
	Button bSettingsExit(310, 422, &tButton, ClickSettingsExit);
	Text tSound(L"�����", font, 50); tSound.setPosition(165, 205);
	Text tMusic(L"������", font, 50); tMusic.setPosition(165, 275);
	Text tFullScreen(L"������ �����", font, 50); tFullScreen.setPosition(165, 345);
	Text tSettingsExit(L"�����", font, 27); tSettingsExit.setPosition(358, 429);
	// �����
	Button bContinue(310, 195, &tButton, ClickContinue);
	Button bSaveGame(310, 275, &tButton, ClickSaveGame);
	Button bMainMenu(310, 355, &tButton, ClickMainMenu);
	Text tContinue(L"����������", font, 27); tContinue.setPosition(315, 202);
	Text tSaveGame(L"���������", font, 27); tSaveGame.setPosition(332, 282);
	Text tMainMenu(L"������� ����", font, 25); tMainMenu.setPosition(314, 361);
	// ��������
	Button bRestart(310, 195, &tButton, ClickPlay);
	Text tRestart(L"�������", font, 27); tRestart.setPosition(352, 202);


	// ��������� ����� ������
	/*{
		//Color clr(102, 102, 238);
		Color clr(21, 202, 212);
		// ������� ����
		tPlay.setFillColor(clr); tPlay.setOutlineColor(clr);
		tSettings.setFillColor(clr); tSettings.setOutlineColor(clr);
		tGameExit.setFillColor(clr); tGameExit.setOutlineColor(clr);
		// ���������
		tMusic.setFillColor(clr); tMusic.setOutlineColor(clr);
		tSound.setFillColor(clr); tSound.setOutlineColor(clr);
		tFullScreen.setFillColor(clr); tFullScreen.setOutlineColor(clr);
		tSettingsExit.setFillColor(clr); tSettingsExit.setOutlineColor(clr);
	}*/

	// ����� ��� ������ fps 
	thread thr(fpsOut);

	while (win->isOpen())
	{
		elapsed = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		elapsed *= 0.000625; //����������� �������� ����: elapsed /= 1600; 0.000625 = 1 / 1600 

		// ��������� ���� � ����
		Vector2f MousePos = win->mapPixelToCoords(Mouse::getPosition(*win));
		
		// ������� ����
		if (STATE == GAME_STATE::MAIN_MENU)
		{
			// �������
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
						bPlay.Update(MousePos);
						bSettings.Update(MousePos);
						bGameExit.Update(MousePos);
					}
				}
			}

			win->clear();

			// ���������
			win->draw(sBackground); // ���
			
			win->draw(bPlay.Rect);
			win->draw(tPlay);
			win->draw(bSettings.Rect);
			win->draw(tSettings);
			win->draw(bGameExit.Rect);
			win->draw(tGameExit);

			win->display();
			FPS++;

			continue;
		}
		
		// �����
		if (STATE == GAME_STATE::PAUSE)
		{
			// �������
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
						bContinue.Update(MousePos);
						bSaveGame.Update(MousePos);
						bMainMenu.Update(MousePos);
					}
				}
				if (event.type == Event::KeyReleased)
				{
					if (event.key.code == Keyboard::Escape)
					{
						STATE = GAME_STATE::PLAYING;
						win->setMouseCursorVisible(false);
						Mouse::setPosition(SAVED_MOUSE_POINT);
					}
				}
			}

			win->clear();

			// ���������
			win->draw(sBackground); // ���
			// �����
			win->draw(sMenu);

			win->draw(bContinue.Rect);
			win->draw(bSaveGame.Rect);
			win->draw(bMainMenu.Rect);
			win->draw(tContinue);
			win->draw(tSaveGame);
			win->draw(tMainMenu);
			win->display();
			FPS++;

			continue;
		}

		// ��������
		if (STATE == GAME_STATE::GAME_OVER)
		{
			// �������
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
						bRestart.Update(MousePos);
						bSaveGame.Update(MousePos);
						bMainMenu.Update(MousePos);
					}
				}
				if (event.type == Event::KeyReleased)
				{
					if (event.key.code == Keyboard::Escape)
					{
						STATE = GAME_STATE::PLAYING;
						win->setMouseCursorVisible(false);
						Mouse::setPosition(SAVED_MOUSE_POINT);
					}
				}
			}

			win->clear();

			// ���������
			win->draw(sBackground); // ���
			win->draw(sMenu);

			win->draw(bRestart.Rect);
			win->draw(bSaveGame.Rect);
			win->draw(bMainMenu.Rect);
			win->draw(tRestart);
			win->draw(tSaveGame);
			win->draw(tMainMenu);
			win->display();
			FPS++;

			continue;
		}

		// ����
		if (STATE == GAME_STATE::PLAYING)
		{
			// �������
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
						// ����
						HpSound.play();
						if (player->Hp > 0)
						{
							bullets[bulIterator].Damage = 35 + rand() % 65;
							bullets[bulIterator].sprite.setPosition(bullets[bulIterator].X = MousePos.x - 4, bullets[bulIterator].Y = MousePos.y - 70);
							bulIterator++;
							if (bulIterator == BULLET_COUNT)
								bulIterator = 0;
						}
					}
				}
				if (event.type == Event::KeyReleased)
				{
					if (event.key.code == Keyboard::Escape)
					{
						STATE = GAME_STATE::PAUSE;
						SAVED_MOUSE_POINT = Mouse::getPosition();
						win->setMouseCursorVisible(true);
					}
				}
			}

			win->clear();

			// ����������
			
			if (player->Hp > 0)
			{
				health.setSize(Vector2f(player->Hp * 2, 30));
				if (player->Hp > 66)
					health.setFillColor(Color::Green);
				else if (player->Hp > 33)
					health.setFillColor(Color::Yellow);
				else health.setFillColor(Color::Red);
				player->Update(MousePos, bots, elapsed);
				for (int i = 0; i < BOT_COUNT; i++)
					bots[i].Update(elapsed);
				for (int i = 0; i < BULLET_COUNT; i++)
					bullets[i].Update(bots, elapsed);
			}
			else
			{
				health.setSize(Vector2f(0, 30));
				win->setMouseCursorVisible(true);
				STATE = GAME_STATE::GAME_OVER;
			}

			// ������ ��� ������ ���-�� ������
			sKILLED_IN_MISSION.str(""); // ������� ���������� ������
			sKILLED_IN_MISSION << KILLED_IN_MISSION << endl;
			killed.setString(sKILLED_IN_MISSION.str());
			
			// ���������
			win->draw(sBackground); // ���
			
			// ����
			for (int i = 0; i < BOT_COUNT; i++) // ����
				win->draw(bots[i].sprite);
			win->draw(player->sprite); // �����
			for (int i = 0; i < BULLET_COUNT; i++) // ������
				win->draw(bullets[i].sprite);
			win->draw(sInfopanel); // ����������
			win->draw(health); // ������ ��
			win->draw(killed); // ����� ������
			
			win->display();
			FPS++;

			continue;
		}

		// ���������
		if (STATE == GAME_STATE::SETTINGS)
		{
			// �������
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
						cbMusic.Update(MousePos);
						cbSounds.Update(MousePos);
						cbFullScreen.Update(MousePos);
						bSettingsExit.Update(MousePos);
					}
				}
			}

			win->clear();

			// ���������
			win->draw(sBackground); // ���
			
			win->draw(cbMusic.Rect);
			win->draw(cbSounds.Rect);
			win->draw(cbFullScreen.Rect);
			win->draw(tMusic);
			win->draw(tSound);
			win->draw(tFullScreen);
			win->draw(bSettingsExit.Rect);
			win->draw(tSettingsExit);
			
			win->display();
			FPS++;

			continue;
		}
	}
	return 0;
}