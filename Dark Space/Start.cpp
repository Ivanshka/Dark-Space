#include <iostream>
#include <vector>
#include <list>
#include <thread>
#include <ctime>
#include <string>
#include <sstream>

#include "Vars.h"
#include "Bot.h"
#include "Player.h"
#include "Bullet.h"
#include "Button.h"

using namespace std;
using namespace sf;

int FPS = 0;
void fpsc()
{
	while (true)
	{
		sleep(milliseconds(1000));
		cout << "FPS = " << FPS << endl << "STATE = " << STATE << endl;
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
	srand(time(0));

	// ��������������� ���������:
	// �������� � �������:
	Texture tBackground; tBackground.loadFromFile("images/space.png"); // ��� �������� ����
	Sprite sBackground; sBackground.setTexture(tBackground);
	Texture tBullet; tBullet.loadFromFile("images/fire.png"); // �����
	Texture tBot; tBot.loadFromFile("images/enemy.png"); // �����
	Texture tMenu; tMenu.loadFromFile("images/menu.png"); // ��� ���� �����
	Sprite sMenu; sMenu.setTexture(tMenu);
	Texture tButtonPlay; tButtonPlay.loadFromFile("images/buttons/buttonPlay.png"); // ������ "������"
	Texture tButtonSettings; tButtonSettings.loadFromFile("images/buttons/buttonSettings.png"); // ������ "���������"
	Texture tButtonExit; tButtonExit.loadFromFile("images/buttons/buttonExit.png"); // ������ "�����"

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

	// ������ �������
	// ������� ����
	Button bPlay(100, 100, &tButtonPlay, ClickPlay);
	Button bSettings(100, 180, &tButtonSettings, ClickSettings);
	Button bGameExit(100, 260, &tButtonExit, ClickGameExit);
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
		elapsed /= 1600; //����������� �������� ����

		// ��������� ���� � ����
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
						if (player.Hp > 0)
						{
							bullets[bulIterator].Damage = 35 + rand() % 65;
							bullets[bulIterator].sprite.setPosition(bullets[bulIterator].X = MousePos.x - 4, bullets[bulIterator].Y = MousePos.y - 70);
							bulIterator++;
							if (bulIterator == BULLET_COUNT)
								bulIterator = 0;
						}
						break;
					}
					
				}
			}
			if (event.type == Event::KeyReleased)
			{
				if (event.key.code == Keyboard::Escape)
				{
					cout << "ESCAPE!!!" << endl;
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

		// ����������
		if (STATE == PLAYING)
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

		// ���������
		win->draw(sBackground); // ���
		switch (STATE)
		{
		case MAIN_MENU: // ������� ����
			win->draw(bPlay.Rect); 
			win->draw(bSettings.Rect);
			win->draw(bGameExit.Rect);
			break;
		case PLAYING: // ����
			for (int i = 0; i < BOT_COUNT; i++) // ����
				win->draw(bots[i].sprite);
			win->draw(player.sprite); // �����
			for (int i = 0; i < BULLET_COUNT; i++) // ������
				win->draw(bullets[i].sprite);
			win->draw(sInfopanel); // ����������
			win->draw(health); // ������ ��
			win->draw(killed); // ����� ������
			break;
		case PAUSE: // ����� ����
			win->draw(sMenu);
			break;
		case SETTINGS:
			break;
		}
		
		win->display();
		FPS++;
	}
	return 0;
}