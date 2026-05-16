#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <list>
#include <SFML/Audio.hpp>
#include "Player.h"
#include "Enemy.h"
#include "Background.h"
#include "Menu.h"
#include "Universe.h"
#include "time.h"
#include "Planets.h"
#include "Minimap.h"
using namespace sf;
int main()
{
	bool saved;
	unsigned int maxNumber = 0;
	int starSystem = 0, galaxy = 0, planetSpeed = 3000;
	unsigned char planet = 1;
	float alpha = 0, planetR = 0, depth = 100;
	double angle = 0, ang = 0;
	long double orbitalDistanse = 2000000000, seconds = 0, x, y, planetX = 0, planetY = 0, pplanetX = 0, pplanetY = 0;
//Окно игры
	RenderWindow *window = new RenderWindow(sf::VideoMode(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN) + 1), "SpaceAction2D");
	window->display();
	window->setPosition(Vector2i(-8, -31));

	int w = window->getSize().x, h = window->getSize().y;

	Font font;
	font.loadFromFile("Helvetica-Regular.ttf");
	Text text("", font, 20), teleportation("", font, 70);
	text.setPosition(100, 77);

	Menu menu("menu.png", font, w, h);

	SoundBuffer bGun, bExplode, bHit, bFly, bSong;
	bGun.loadFromFile("sounds/gun.wav");
	bExplode.loadFromFile("sounds/explode.wav");
	bHit.loadFromFile("sounds/hit.wav");
	bFly.loadFromFile("sounds/fly.wav");
	bSong.loadFromFile("sounds/song.wav");
	Sound gun, explode, hit, fly, song;
	gun.setBuffer(bGun);
	explode.setBuffer(bExplode);
	hit.setBuffer(bHit);
	fly.setBuffer(bFly);
	song.setBuffer(bSong);
	gun.setAttenuation(0);
	explode.setAttenuation(0);
	hit.setAttenuation(0);
	fly.setAttenuation(0);
	song.setAttenuation(0);

	Vector2f pos, ppos;

	Event event;
	Event::MouseWheelEvent wheel;

	Clock clock;
	
	teleportation.setOrigin(444, 35);
	teleportation.setPosition((float)w / 2, (float)h / 2);
	teleportation.setColor(Color(0, 0, 255, 0));

	Image *Ip = new Image, *Ie = new Image, *Ib = new Image, *Ib1 = new Image;
	Texture Tp, Te, Tb, Tb1;
	Sprite Sp, Se, Sb, Sb1;
	Ip->loadFromFile("images/hero.png");
	Ip->createMaskFromColor(Color(255, 255, 255));
	Tp.loadFromImage(*Ip);
	Sp.setTexture(Tp);
	Ie->loadFromFile("images/alien.png");
	Ie->createMaskFromColor(Color(255, 255, 255));
	Te.loadFromImage(*Ie);
	Se.setTexture(Te);
	Ib->loadFromFile("images/bullet.png");
	Ib1->loadFromFile("images/bullet1.png");
	Ib->createMaskFromColor(Color(255, 255, 255));
	Ib1->createMaskFromColor(Color(255, 255, 255));
	Tb.loadFromImage(*Ib);
	Tb1.loadFromImage(*Ib1);
	Sb.setTexture(Tb);
	Sb1.setTexture(Tb1);
	Sb.setTextureRect(IntRect(0, 0, 22, 12));
	Sb1.setTextureRect(IntRect(0, 0, 22, 14));
	Sb.setOrigin((float)Sb.getTextureRect().width / 2, (float)Sb.getTextureRect().height / 2);
	Sb1.setOrigin((float)Sb1.getTextureRect().width / 2, (float)Sb1.getTextureRect().height / 2);
	delete Ip, Ie, Ib;

	Player p(Sp, Sb1, 0, 0, w, h);

	FILE *fT, *fP, *fS, *fPD;
//Сохранена ли игра
	if (fopen("data/time.dat", "rb") == NULL)
		saved = false;
	else
	{
		saved = true;
		fT = fopen("data/time.dat", "rb");
		fread(&seconds, sizeof(long double), 1, fT);
		fclose(fT);

		fP = fopen("data/position.dat", "rb");
		fread(&galaxy, sizeof(int), 1, fP);
		fread(&starSystem, sizeof(int), 1, fP);
		fread(&planet, sizeof(int), 1, fP);
		fclose(fP);

		fS = fopen("data/settings.dat", "rb");
		fread(&menu.v1, sizeof(float), 1, fS);
		fread(&menu.v2, sizeof(float), 1, fS);
		fread(&p.Control, sizeof(bool), 1, fS);
		for (unsigned char i = 0; i < sizeof(p.Controls); i++)
			fread(&p.Controls[i], sizeof(unsigned char), 1, fS);
		fclose(fS);

		fPD = fopen("data/playerData.dat", "rb");
		fread(&p.health, sizeof(int), 1, fP);
		fclose(fPD);
	}

	gun.setVolume(menu.v2);
	hit.setVolume(menu.v2);
	explode.setVolume(menu.v2);
	fly.setVolume(menu.v2);
	song.setVolume(menu.v1);
	song.play();
	song.setLoop(true);

	std::list<Ship*>  enemies;
	std::list<Ship*>::iterator it;

	Minimap minimap(h, &font);

	Planets planets;

	Universe universe(font, w, h);

	Background background(w, h);

	RectangleShape hp;

	CircleShape target(13), enemy(16);

	target.setFillColor(Color(0, 0, 0, 0));
	target.setOutlineThickness(4);
	target.setOutlineColor(Color(255, 0, 0));
	target.setOrigin(13, 13);

	enemy.setFillColor(Color(255, 0, 0));
	enemy.setOrigin(16, 16);

	//Загрузка сохранённых данных
	if (saved)
	{
		background.loadImage("images/background.png", w, h);
		
		universe.loadUniverse("Universe.png", w, h);
		
		planets.setNumberOfPlanets(universe.systemInfo[galaxy][starSystem][0], universe.planetInfo[galaxy][starSystem]);
		ang = (universe.planetInfo[galaxy][starSystem][planet - 1][0] + (seconds * planetSpeed / (planet * orbitalDistanse)) / 57.2957795131l)*universe.planetInfo[galaxy][starSystem][planet - 1][2];
		x = planet * orbitalDistanse * cos(ang) - p.x / depth;
		y = planet * orbitalDistanse * sin(ang) - p.y / depth;
		p.move(x * depth, y * depth);
		planetX = x * depth;
		planetY = y * depth;
	}

	srand(int(time(NULL)));
	
	//Главный цикл
	while (window->isOpen())
	{
		pos = (Vector2f)Mouse::getPosition(*window);

		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		
		while (window->pollEvent(event))
		{
			wheel = event.mouseWheel;
			if (event.type == Event::Closed)
				window->close();
			if (event.type == Event::MouseButtonPressed)
			{
				if (menu.page == 1)
				{
					if (menu.rect1.getGlobalBounds().contains(pos) || menu.line1.getGlobalBounds().contains(pos)) menu.changingVolume1 = true;
					if (menu.rect2.getGlobalBounds().contains(pos) || menu.line2.getGlobalBounds().contains(pos)) menu.changingVolume2 = true;
				}
				ppos = pos;
			}
			if (event.type == Event::MouseButtonReleased)
			{
				if (menu.changingControl == 1)
				{
					p.Controls[0] = event.key.code;
					menu.changingControl = 0;
				}
				if (event.key.code == Mouse::Left)
				{
					minimap.changingSize = false;
					menu.changingVolume1 = false;
					menu.changingVolume2 = false;

					if (menu.showMenu)
					{
						if (menu.page == 0)
						{
							if (menu.New.getGlobalBounds().contains(ppos) && menu.New.getGlobalBounds().contains(pos))////Новая игра////
							{
								p.newGame(0, 0);
								background.createImage(window, &text);
								universe.createUniverse(w, h);
								planets.setNumberOfPlanets(universe.systemInfo[galaxy][starSystem][0], universe.planetInfo[galaxy][starSystem]);
								seconds = 0;
								planet = 1;
								ang = (universe.planetInfo[galaxy][starSystem][planet - 1][0] + (seconds * planetSpeed / (planet * orbitalDistanse)) / 57.2957795131l)*universe.planetInfo[galaxy][starSystem][planet - 1][2];
								x = planet * orbitalDistanse * cos(ang) - p.x / depth;
								y = planet * orbitalDistanse * sin(ang) - p.y / depth;
								p.move(x * depth, y * depth);
								planetX = x * depth;
								planetY = y * depth;

								universe.page = false;
								minimap.targetPlanet = 0;
								minimap.setScale(2500000000);
								text.setPosition(100, 77);
								menu.showMenu = false;
								saved = true;
								clock.restart();
							}///////////////////////////////////////////////////////////////////////////////////////////////
							if (menu.Continue.getGlobalBounds().contains(ppos) && menu.Continue.getGlobalBounds().contains(pos) && saved)    menu.showMenu = false;
							if (menu.Exit.getGlobalBounds().contains(ppos) && menu.Exit.getGlobalBounds().contains(pos))                   { if (p.health <= 0) p.health = p.maxhp; window->close(); }//Выход
							if (menu.Settings.getGlobalBounds().contains(ppos) && menu.Settings.getGlobalBounds().contains(pos))             menu.page = 1;
						}
						else
						{
							if (menu.Back.getGlobalBounds().contains(ppos) && menu.Back.getGlobalBounds().contains(pos))                     menu.page--;
							if (menu.Close.getGlobalBounds().contains(ppos) && menu.Close.getGlobalBounds().contains(pos) && saved)        { menu.page = 0; menu.showMenu = false; }
						}
						if (menu.page == 1 && menu.control.getGlobalBounds().contains(ppos) && menu.control.getGlobalBounds().contains(pos)) menu.page = 2;
						menu.changingControl = 0;
						if (menu.page == 2)
						{
							for (unsigned char i = 1; i < 5 + (!p.Control) * 3; i++) if (menu.text[i].getGlobalBounds().contains(pos))       menu.changingControl = i;
							if (menu.text[0].getGlobalBounds().contains(ppos) && menu.text[0].getGlobalBounds().contains(pos))             { p.Control = !p.Control; p.tempX = p.x + p.DGCx; p.tempY = p.y + p.DGCy; }
						}
					}
					else if (universe.showMap)
					{
						if (universe.Back.getGlobalBounds().contains(ppos) && universe.Back.getGlobalBounds().contains(pos)) universe.showMap = false;
						if (universe.Page.getGlobalBounds().contains(ppos) && universe.Page.getGlobalBounds().contains(pos)) universe.changePage();
					}
					else if (p.alife && minimap.text.getGlobalBounds().contains(ppos) && minimap.text.getGlobalBounds().contains(pos))
					if (minimap.targetPlanet != 0 && p.alife)
					{//Телепортация на планету
						ang = (universe.planetInfo[galaxy][starSystem][minimap.targetPlanet - 1][0] + (seconds * planetSpeed / (minimap.targetPlanet * orbitalDistanse)) / 57.2957795131l)*universe.planetInfo[galaxy][starSystem][minimap.targetPlanet - 1][2];
						x = minimap.targetPlanet * orbitalDistanse * cos(ang);
						y = minimap.targetPlanet * orbitalDistanse * sin(ang);
						p.move(x * depth - 10000 + rand() % 20001, y * depth - 10000 + rand() % 20001);
						planetX = x * depth;
						planetY = y * depth;
						planet = minimap.targetPlanet;
						alpha = 255;
						minimap.targetPlanet = 0;
					}
					else universe.showMap = true;
				}
			}
			if (event.type == Event::MouseWheelMoved) minimap.setScale(minimap.scale*(1 - (float)wheel.delta / 20)); //Изменение масштаба у миникарты
			if (event.type == Event::KeyReleased)
			{
				if (menu.changingControl > 1 && event.key.code >= 0 && (!p.Control || menu.changingControl<5))
				{
					p.Controls[menu.changingControl - 1] = event.key.code;
					menu.changingControl = 0;
				}
				else
				{
					if (event.key.code == p.Controls[1])   if(saved) { menu.showMenu = !menu.showMenu; menu.page = 0; }
					if (event.key.code == p.Controls[2])   minimap.setScale(5000000000);
					if (event.key.code == p.Controls[3])   minimap.setScale(100);
				}
			}
		}
		window->clear();//очистка окна

		if (menu.showMenu)
			if (!menu.page) menu.update0(pos, saved, window);
			else if (menu.page == 1)
			{
				menu.update1(pos, saved, window);
				song.setVolume(menu.v1);
				gun.setVolume(menu.v2);
			}
			else menu.update2(pos, saved, window, &p, time);
		else if (universe.showMap) universe.update(window, pos, galaxy, starSystem);
		else
		{
			if (p.alife)
			{
				if (Mouse::isButtonPressed(Mouse::Button::Left) && (!minimap.text.getGlobalBounds().contains(pos)) && !minimap.changingSize)
				{
					if (minimap.chosenPlanet != 0 && (minimap.chosenPlanet != planet || p.distanceToPlanet>10000*depth))
						minimap.targetPlanet = minimap.chosenPlanet;
					else
					{
						minimap.targetPlanet = 0;
						if (minimap.map.getGlobalBounds().contains(pos)) minimap.fly(pos, &p);//Дальний полёт
						else if (p.Control) p.fly(p.x + int(pos.x - (float)w / 2), p.y + int(pos.y - (float)h / 2));//Ближний
					}                                                  //
				}                                                      //
				if (!p.Control) p.keyControl(time);                    //Полёт

				if (Mouse::isButtonPressed(Mouse::Button(p.Controls[0])) && !minimap.changingSize) p.weapon.fight(time, atan2(h / 2 - pos.y, w / 2 - pos.x), p.x, p.y, (float)p.speedX, (float)p.speedY, &gun);//Стрельба

				target.setPosition((float)(p.tempX - p.x + w / 2), (float)(p.tempY - p.y + h / 2));//Цель полёта корабля

				p.update(time, planetX, planetY, &fly);

				maxNumber = int(pow(p.distanceToPlanet, 0.25l) / 5);////////////////////Спавн мобов//////////////////////////////////
				if (maxNumber == 0 && p.health < p.maxhp && p.health > 0 && seconds * 22 - int(seconds * 22) < time * 22) p.health++;
				if (enemies.size() < maxNumber && seconds / 4 - int(seconds / 4) < time / 4) enemies.push_back(new Enemy(Se, Sb, p.x + (w / 2 + rand() % w)*((rand() % 2) * 2 - 1), p.y + (h / 2 + rand() % h)*((rand() % 2) * 2 - 1), w, h));
				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			}
			double a, b, c;
			for (it = enemies.begin(); it != enemies.end();)//Движение и апдейт мобов///
			{
				Ship *d = *it;
				if (p.alife) p.health-=d->weapon.hitTest(p.x, p.y, &hit, menu.v2);
				d->update(time, planetX, planetY, &fly);
				a = p.x - d->x;
				b = p.y - d->y;
				c = sqrt(a*a + b*b);
				if (d->frame >= 11 || c > 44444)
				{
					it = enemies.erase(it);
					delete d;
				}
				else
				{
					if (d->health <= 0) d->explose(&explode, time, p.x, p.y, menu.v2);
					else
					{
						if (p.weapon.hitTest1(&hit, menu.v2, time, p.x, p.y, (*it)->x, (*it)->y, (*it)->speedX, (*it)->speedY)) (*it)->hitted(p.weapon.dmg);
						d->setTarget(time, &p, &gun);
					}
					it++;
				}
			}///////////////////////////////////////////////////////////////////////////
			background.update(window, p.x, p.y);

			/////////////////////Текст////////////////////////
			std::ostringstream coords, str;
			coords << "x: " << (__int64)p.x << "m\ny: " << (__int64)p.y << "m\nspeed: " << (__int64)p.speed << "m/s\nfps: " << 1 / time << "\ndistance: " << (__int64)p.getDistance() << "m\n" << enemies.size() << "/" << maxNumber << " enemies nearby";
			text.setString(coords.str());

			seconds += time;
			///////////Отображение звезды и планет////////////
			x = -p.x / depth + w / 2;
			y = -p.y / depth + h / 2;
			float dist = (float)planets.ss.getTextureRect().height / 2;
			if (x > -dist && x < w + dist && y > -dist && y < h + dist)
			{
				planets.ss.setPosition((float)x, (float)y);
				window->draw(planets.ss);
			}
			x = planetX / depth + w / 2 - p.x / depth;
			y = planetY / depth + h / 2 - p.y / depth;
			dist = (float)planets.ps[planet - 1].getTextureRect().height / 2;
			if (x > -dist && x < w + dist && y > -dist && y < h + dist)
			{
				planets.ps[planet - 1].setPosition((float)x, (float)y);
				planets.ps[planet - 1].setRotation(planetR - 45);
				window->draw(planets.ps[planet - 1]);
				if (p.distanceToPlanet < 99000) p.nearPlanet = true; else p.nearPlanet = false;
			} else p.nearPlanet = false;
			///////////////////Прорисовка мобов//////////////
			for (it = enemies.begin(); it != enemies.end(); it++)
			{
				x = (*it)->x - p.x + w / 2;
				y = (*it)->y - p.y + h / 2;
				dist = (float)(*it)->sprite.getTextureRect().width / 2;
				if (x > -dist && x < w + dist && y > -dist && y < h + dist)
				{
					(*it)->sprite.setPosition((float)x, (float)y);
					(*it)->weapon.sprite.setPosition((float)x, (float)y);
					window->draw((*it)->sprite);
					if ((*it)->maxhp>(*it)->health && (*it)->health>0)
					{
						hp.setFillColor(Color(0, 255, 0));
						hp.setSize(Vector2f(100 * ((float)(*it)->health / (*it)->maxhp), 6));
						hp.setPosition((float)x - 50, (float)y - dist);
						window->draw(hp);
						hp.setFillColor(Color(128, 128, 128, 128));
						hp.setPosition((float)x - 50 + hp.getSize().x, (float)y - dist);
						hp.setSize(Vector2f(100 * (1 - ((float)(*it)->health / (*it)->maxhp)), 6));
						window->draw(hp);
					}
				}
				(*it)->nearPlanet = (*it)->distanceToPlanet < 4444;
			}
			if (p.alife && (p.Control || p.longMoving)) window->draw(target);//Точка, куда летит игрок
			window->draw(p.sprite);//Прорисовка игрока
			////////////Прорисовка снарядов игрока///////////////
			for (p.weapon.it = p.weapon.Bullets.begin(); p.weapon.it != p.weapon.Bullets.end(); p.weapon.it++)
			{
				(*p.weapon.it)->update(time);
				(*p.weapon.it)->sprite.setPosition((float)((*p.weapon.it)->x - p.x) + w / 2, (float)((*p.weapon.it)->y - p.y) + h / 2);
				window->draw((*p.weapon.it)->sprite);
			}
			if (p.alife) window->draw(p.weapon.sprite);
			for (it = enemies.begin(); it != enemies.end(); it++)//вражеские снаряды:
			{
				for ((*it)->weapon.it = (*it)->weapon.Bullets.begin(); (*it)->weapon.it != (*it)->weapon.Bullets.end(); (*it)->weapon.it++)
				{
					(*(*it)->weapon.it)->update(time);
					if (!(*(*it)->weapon.it)->play) (*(*it)->weapon.it)->sprite.setPosition((float)((*(*it)->weapon.it)->x - p.x) + w / 2, (float)((*(*it)->weapon.it)->y - p.y) + h / 2);
					window->draw((*(*it)->weapon.it)->sprite);
				}
				if ((*it)->alife) window->draw((*it)->weapon.sprite);
			}
			////////////////////Здоровье игрока//////////////////
			if (p.health>0)
			{
				hp.setFillColor(Color(0, 255, 0));
				hp.setSize(Vector2f(w/4 * ((float)p.health / p.maxhp), 16));
				hp.setPosition(100, 55);
				window->draw(hp);
				hp.setFillColor(Color(128, 128, 128, 128));
				hp.setPosition(100 + hp.getSize().x, 55);
				hp.setSize(Vector2f(w/4 * (1 - ((float)p.health / p.maxhp)), 16));
				window->draw(hp);
			}
			else
			{
				song.pause();
				p.explose(&explode, time, menu.v2);
				if (p.frame > 16)
				{
					p.speedX = 0;
					p.speedY = 0;
				}
				if (p.frame > 88)
				{
					window->clear();
					if (seconds / 10 - int(seconds / 10) < time)
					{
						p.newGame(planetX, planetY);
						song.play();
					}
				}
			}
			
			window->draw(text);
			///////////////Сообщение про телепортацию//////////////////
			str << "You moved to the planet " << (int)planet;
			teleportation.setString(str.str());
			if (alpha > 0)
			{
				teleportation.setColor(Color(255, 255, 0, (Uint8)alpha));
				alpha -= time * 125;
				window->draw(teleportation);
			}////////////////////////Поиск ближайшей планеты//////////////////////////
			p.distanceToPlanet = 999999999999999;
			if (minimap.targetPlanet != 0) minimap.chosenPlanet = 0;
			pplanetX = planetX;
			pplanetY = planetY;
			unsigned char tempPlanet = -1;
			background.update1(p.isMove, window, (float)p.getspeedX()*time, (float)p.getspeedY()*time);
			window->draw(minimap.map);
			for (unsigned char i = 1; i <= universe.systemInfo[galaxy][starSystem][0]; i++)
			{
				ang = (universe.planetInfo[galaxy][starSystem][i - 1][0] + (seconds * planetSpeed / (i * orbitalDistanse)) / 57.2957795131l)*universe.planetInfo[galaxy][starSystem][i - 1][2];
				x = i * orbitalDistanse * cos(ang);
				y = i * orbitalDistanse * sin(ang);
				minimap.drawPlanet(window, universe.systemInfo[galaxy][starSystem][0], pos, p.x, p.y, x, y, i, planet, depth);
				long double a = x * depth - p.x, b = y * depth - p.y;
				c = sqrt(a*a + b*b);
				if (c <= p.distanceToPlanet)
				{
					p.distanceToPlanet = c;
					tempPlanet = i;
					planetX = x * depth;
					planetY = y * depth;
					planetR = (float)ang*57.2957795131f;
				}
			}/////////////////////////////////////////////////////////////////////////
			minimap.drawAllButPlanets(window, &enemies, pos, p.x, p.y);
			planet = tempPlanet;

			float k = std::max((float)(p.distanceToPlanet - 2222), 0.0f) / 300000 + 1;
			p.xAboutPlanet = x - pplanetX;
			p.yAboutPlanet = y - pplanetY;
			double planVx = (-x + planetX + p.xAboutPlanet) / k;
			double planVy = (-y + planetY + p.yAboutPlanet) / k;

			if (p.nearPlanet)
			{
				p.goWithPlanet(planetX, planetY, pplanetX, pplanetY, k, planVx, planVy);
				for (it = enemies.begin(); it != enemies.end(); it++)
				{//Движение мобов за планетой
					long double a1 = planetX - (*it)->x, b1 = planetY - (*it)->y;
					(*it)->distanceToPlanet = sqrt(a1*a1 + b1*b1);
					(*it)->goWithPlanet(planetX, planetY, pplanetX, pplanetY, k, planVx, planVy);
				}
			}
		}
		window->display();
	}
	if (saved)
	{//////////////Сохранение данных
		fT = fopen("data/time.dat", "wb");
		fwrite(&seconds, sizeof(long double), 1, fT);
		fclose(fT);

		fP = fopen("data/position.dat", "wb");
		fwrite(&galaxy, sizeof(int), 1, fP);
		fwrite(&starSystem, sizeof(int), 1, fP);
		fwrite(&planet, sizeof(int), 1, fP);
		fclose(fP);

		fS = fopen("data/settings.dat", "wb");
		fwrite(&menu.v1, sizeof(float), 1, fS);
		fwrite(&menu.v2, sizeof(float), 1, fS);
		fwrite(&p.Control, sizeof(bool), 1, fS);
		for (unsigned char i = 0; i < sizeof(p.Controls); i++)
			fwrite(&p.Controls[i], sizeof(unsigned char), 1, fS);
		fclose(fS);

		fPD = fopen("data/playerData.dat", "wb");
		fwrite(&p.health, sizeof(int), 1, fP);
		fclose(fPD);
	}
	return 0;
}