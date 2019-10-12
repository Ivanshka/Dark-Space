#pragma once

#include <iostream>
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
void fpsc()
{
	std::ofstream out;          // ����� ��� ������
	out.open("logFPS.log");
	while (true)
	{
		sleep(milliseconds(1000));
		circles++;
		AllFPS += FPS;
		//cout << "FPS = " << FPS << endl;
		cout << AllFPS << endl;
		out << "FPS = " << FPS << ", ������� = " << (AllFPS / circles) << ", ������ = " << AllFPS<< endl;
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

	// ����������

	// ����
	Clock clock;
	// ������������� ���������� ��������� �����
	srand((unsigned int)time(0));

	// ��������������� ���������:
	// �������� � �������:
	Texture tBackground; tBackground.loadFromFile("images/space.png"); // ��� �������� ����
	Sprite sBackground; sBackground.setTexture(tBackground);
	Texture tBullet; tBullet.loadFromFile("images/fire.png"); // �����
	Texture tBot; tBot.loadFromFile("images/enemy.png"); // �����
	Texture tMenu; tMenu.loadFromFile("images/menu.png"); // ��� ���� �����
	Sprite sMenu; sMenu.setTexture(tMenu);
	//Texture tButton; tButton.loadFromFile("images/gui/button.png"); // ������
	Texture tButtonPlay; tButtonPlay.loadFromFile("images/gui/buttonPlay.png"); // ������ "������"
	Texture tButtonSettings; tButtonSettings.loadFromFile("images/gui/buttonSettings.png"); // ������ "���������"
	Texture tButtonExit; tButtonExit.loadFromFile("images/gui/buttonExit.png"); // ������ "�����"
	Texture tDisCheckBox; tDisCheckBox.loadFromFile("images/gui/DisabledCheckBox.png");
	Texture tEnCheckBox; tEnCheckBox.loadFromFile("images/gui/EnabledCheckBox.png");

	// ������������� ��������:
	Player player(100, 100, "images/player.png");
	Bot * bots = new Bot[BOT_COUNT];
	Bullet * bullets = new Bullet[BULLET_COUNT];
	for (int i = 0; i < BOT_COUNT; i++)
		bots[i] = Bot(0 + rand() % 704, -(64 + rand() % 800), 0.16f, 100., &tBot);
	for (int i = 0; i < BULLET_COUNT; i++)
		bullets[i] = Bullet(-8, -600, 0.64f, &tBullet);
	// ������������� ��������
	int bulIterator = 0;

	// ����������, �������� � ���-�� ������
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

	// ����� ��� ������ fps 
	thread thr(fpsc);
	// �����
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
	Button bPlay(100, 195, &tButtonPlay, ClickPlay);
	Button bSettings(100, 275, &tButtonSettings, ClickSettings);
	Button bGameExit(100, 355, &tButtonExit, ClickGameExit);
	//Text tPlay(L"������", font, 27); tPlay.setPosition(149, 202);
	//Text tSettings(L"���������", font, 27); tSettings.setPosition(1, 1);
	//Text tGameExit(L"�����", font, 27); tGameExit.setPosition(1, 1);
	// ���������
	CheckBox cbSounds(585, 205, &tEnCheckBox, &tDisCheckBox, ClickSound, true);
	CheckBox cbMusic(585, 275, &tEnCheckBox, &tDisCheckBox, ClickMusic, true);
	CheckBox cbFullScreen(585, 345, &tEnCheckBox, &tDisCheckBox, ClickFullScreen, true);
	Button bSettingsExit(310, 422, &tButtonExit, ClickSettingsExit);
	Text tSound(L"�����", font, 50); tSound.setPosition(165, 205);
	Text tMusic(L"������", font, 50); tMusic.setPosition(165, 275);
	Text tFullScreen(L"������ �����", font, 50); tFullScreen.setPosition(165, 345);
	{
		Color clr(102, 102, 238);
		// ������� ����
		//tPlay.setFillColor(clr); tPlay.setOutlineColor(clr);
		//tSettings.setFillColor(clr); tSettings.setOutlineColor(clr);
		//tGameExit.setFillColor(clr); tGameExit.setOutlineColor(clr);
		// ���������
		tMusic.setFillColor(clr); tMusic.setOutlineColor(clr);
		tSound.setFillColor(clr); tSound.setOutlineColor(clr);
		tFullScreen.setFillColor(clr); tFullScreen.setOutlineColor(clr);
	}
	// ����������� ������� � ����������� �������
	/*Text tPlay("������", font, 20); tPlay.setPosition()
	Text tSettings("���������", font, 20);
	Text tExit("�����", font, 20);
	{
		Color clr(102, 102, 238);
		tPlay.setFillColor(clr);    tSettings.setFillColor(clr);    tExit.setFillColor(clr);
		tPlay.setOutlineColor(clr); tSettings.setOutlineColor(clr); tExit.setOutlineColor(clr);
	}*/
	while (win->isOpen())
	{
		elapsed = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		elapsed *= 0.000625; //����������� �������� ����: elapsed /= 1600; 0.000625 = 1 / 1600 

		// ��������� ���� � ����
		Vector2f MousePos = win->mapPixelToCoords(Mouse::getPosition(*win));
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
					switch (STATE)
					{
					// ������� ����
					case GAME_STATE::MAIN_MENU:
						bPlay.Update(MousePos, win);
						bSettings.Update(MousePos, win);
						bGameExit.Update(MousePos, win);
						break;
					// ����
					case GAME_STATE::PLAYING:
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
					// ���������
					case GAME_STATE::SETTINGS:
						cbMusic.Update(MousePos, win);
						cbSounds.Update(MousePos, win);
						cbFullScreen.Update(MousePos, win);
						bSettingsExit.Update(MousePos, win);
						break;
					}
					
				}
			}
			if (event.type == Event::KeyReleased)
			{
				if (event.key.code == Keyboard::Escape)
				{
					switch (STATE) {
					case GAME_STATE::PLAYING:
						STATE = GAME_STATE::PAUSE;
						SAVED_MOUSE_POINT = Mouse::getPosition();
						win->setMouseCursorVisible(true);
						break;
					case GAME_STATE::PAUSE:
						STATE = GAME_STATE::PLAYING;
						win->setMouseCursorVisible(false);
						Mouse::setPosition(SAVED_MOUSE_POINT);
						break;
					case GAME_STATE::SETTINGS:
						STATE = GAME_STATE::MAIN_MENU;
					default:
						break;
					}
				}
			}
		}

		win->clear();

		// ����������
		if (STATE == GAME_STATE::PLAYING)
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

			// ������ ��� ������ ���-�� ������
			sKILLED_IN_MISSION.str(""); // ������� ���������� ������
			sKILLED_IN_MISSION << KILLED_IN_MISSION << endl;
			killed.setString(sKILLED_IN_MISSION.str());
		}

		// ���������
		win->draw(sBackground); // ���
		switch (STATE)
		{
		// ������� ����
		case GAME_STATE::MAIN_MENU:
			win->draw(bPlay.Rect);
			//win->draw(tPlay);
			win->draw(bSettings.Rect);
			win->draw(bGameExit.Rect);
			break;
		// ����
		case GAME_STATE::PLAYING:
			for (int i = 0; i < BOT_COUNT; i++) // ����
				win->draw(bots[i].sprite);
			win->draw(player.sprite); // �����
			for (int i = 0; i < BULLET_COUNT; i++) // ������
				win->draw(bullets[i].sprite);
			win->draw(sInfopanel); // ����������
			win->draw(health); // ������ ��
			win->draw(killed); // ����� ������
			break;
		// �����
		case GAME_STATE::PAUSE:
			win->draw(sMenu);
			break;
		// ���������
		case GAME_STATE::SETTINGS:
			win->draw(cbMusic.Rect);
			win->draw(cbSounds.Rect);
			win->draw(cbFullScreen.Rect);
			win->draw(tMusic);
			win->draw(tSound);
			win->draw(tFullScreen);
			win->draw(bSettingsExit.Rect);
			break;
		}
		
		win->display();
		FPS++;
	}
	return 0;
}