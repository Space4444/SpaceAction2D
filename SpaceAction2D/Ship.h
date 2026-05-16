#include <SFML/Graphics.hpp>
#include "Bullet.h"
#include "Weapon.h"
#include <list>
using namespace sf;
class Ship
{
public:
	bool alife, isMove, nearPlanet, randomized, maxed, go;
	int health, maxhp, w, h, exploseW;
	float fireRate, frame;
	double DGC, DGCx, DGCy, anglerad, speed, speedX, speedY, maxspeed, endspeed, rotSpeed, speedUp, rotation, speedAnglerad, speedUpx, speedUpy;
	long double x, y, c, dx, dy, tempX, tempY, xAboutPlanet, yAboutPlanet, tempxAboutPlanet, tempyAboutPlanet, distanceToPlanet, randX, randY;
	Sprite sprite, sp;
	Weapon weapon;
	Ship(Sprite S, Sprite S1, long double X, long double Y, int screenW, int screenH)
	{
		weapon.setWeapon(1);
		weapon.setBullet(1, S1);
		alife = isMove = true;
		nearPlanet = maxed = false;
		DGC = DGCx = DGCy = speed = speedX = speedY = speedUpx = speedUpy = rotation = xAboutPlanet = yAboutPlanet = tempxAboutPlanet = tempyAboutPlanet = distanceToPlanet = 0;
		rotSpeed = 720;
		frame = 0;
		x = tempX = X;
		y = tempY = Y;
		w = 144;
		h = 72;
		dx = 0;
		dy = 0;
		c = 0;
		sprite = S;
		sprite.setTextureRect(IntRect(0, 0, w, h));
		sprite.setOrigin((float)w / 1.8f, (float)h / 2);
		sp = S1;
	}
	void update(float time, long double planetX, long double planetY, Sound *fly)
	{
		maxed = false;
		if (isMove && alife)
		{
			sprite.setTextureRect(IntRect(0, 0, w, h));
			dx = tempX - x;
			dy = tempY - y;
			c = sqrt(dx*dx + dy*dy);
			anglerad = atan2(dy, dx);
			maxed = false;
			double angle = anglerad*57.2957795131;
			double delta = angle - rotation;
			if (delta > 180) delta -= 360;
			else if (delta < -180) delta += 360;
			double tempVar = rotSpeed*time;
			if (abs(delta)>tempVar)
				if (delta > 0)
				{
					rotation += tempVar;
					weapon.rotation += (float)tempVar;
					weapon.sprite.setRotation(weapon.rotation);
				}
				else
				{
					rotation -= tempVar;				
					weapon.rotation -= (float)tempVar;
					weapon.sprite.setRotation(weapon.rotation);
				}
			else
			{
				rotation = angle;
				go = true;
			}
			//////////////////////Остановка////////////////////////////////
			if (abs(speed) < abs(speedUp*time * 4) && c < abs(speed*time * 4))
			{
				x = tempX;
				y = tempY;
				c = 0;
				speedX = 0;
				speedY = 0;
				go = false;
				isMove = false;
			}
			////////////////////////Полёт///////////////////////////////////
			if (go)
			if ((abs(speedX)<abs(speedUpx*time) && abs(speedY)<abs(speedUpy*time)) || abs(anglerad - speedAnglerad) < rotSpeed / 57.2957795131*time)
			{
				speedX = speed*cos(anglerad);
				speedY = speed*sin(anglerad);
				speedUpx = speedUp*cos(anglerad);
				speedUpy = speedUp*sin(anglerad);
				if (abs(dx) > abs(DGCx) || abs(dy) > abs(DGCy))
				{
					if (c < endspeed * 3) maxspeed = (c / 2 - DGC / 2) / time; else maxspeed = endspeed;
					if (speedX*speedX + speedY*speedY < maxspeed*maxspeed)
					{
						sprite.setTextureRect(IntRect(w, 0, w, h));
						speedX += speedUpx*time;
						speedY += speedUpy*time;
					}
					if (speed == maxspeed) maxed = true;
				}
				else
				{
					if (dx) speedX -= speedX*speedX / dx / 2 * time;
					if (dy) speedY -= speedY*speedY / dy / 2 * time;
				}
			}
			else
			{
				tempVar = atan2(sin(anglerad) - sin(speedAnglerad), cos(anglerad) - cos(speedAnglerad));
				speedUpx = speedUp*cos(tempVar);
				speedUpy = speedUp*sin(tempVar);
				sprite.setTextureRect(IntRect(w, 0, w, h));
				speedX += speedUpx*time;
				speedY += speedUpy*time;
			}
			speedAnglerad = atan2(speedY, speedX);
			speed = sqrt(speedX*speedX + speedY*speedY);
			DGC = speed*speed / 2 / speedUp;
			DGCx = DGC*cos(speedAnglerad);
			DGCy = DGC*sin(speedAnglerad);
			sprite.setRotation((float)rotation);
		}
		x += speedX*time;
		y += speedY*time;
		weapon.checkForDel();
	}
	void explose(Sound *explode, float time, long double X, long double Y, float v)
	{
		if (alife)
		{
			double a = x - X;
			double b = y - Y;
			explode->setVolume((float)(100 * v / (sqrt(a*a + b*b)+100)));
			explode->play();
		}
		health = 0;
		sprite.setTextureRect(IntRect(0, 72 + exploseW * int(frame), exploseW, exploseW));
		sprite.setOrigin((float)sprite.getTextureRect().width / 2, (float)sprite.getTextureRect().height / 2);
		frame += time * 24;
		alife = false;
	}
	void goWithPlanet(long double planetX, long double planetY, long double pplanetX, long double pplanetY, float k, double Vx, double Vy)
	{
		tempxAboutPlanet = tempX - pplanetX;
		tempyAboutPlanet = tempY - pplanetY;
		x += Vx;
		y += Vy;
		tempX += (-tempX + planetX + tempxAboutPlanet) / k;
		tempY += (-tempY + planetY + tempyAboutPlanet) / k;
		for (std::list<Bullet*>::iterator it = weapon.Bullets.begin(); it != weapon.Bullets.end(); it++)
		{
			(*it)->xAboutPlanet = (*it)->x - pplanetX;
			(*it)->yAboutPlanet = (*it)->y - pplanetY;
			(*it)->x += (-(*it)->x + planetX + (*it)->xAboutPlanet) / k;
			(*it)->y += (-(*it)->y + planetY + (*it)->yAboutPlanet) / k;
		}
	}
	void fly(long double X, long double Y)
	{
		tempX = X;
		tempY = Y;
		if (abs(x - tempX) >= 0.005 || abs(y - tempY) >= 0.005) isMove = true;
	}
	virtual void randomize(){}
	virtual void setTarget(float time, Ship *p, Sound *gun){}
	virtual void hitted(float dmg){}
};