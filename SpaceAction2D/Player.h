#include <SFML/Graphics.hpp>
#include "Ship.h"
using namespace sf;
class Player :public Ship
{
public:
	bool Control, longMoving;
	unsigned char Controls[7];
	Player(Sprite S, Sprite S1, long double X, long double Y, int screenW, int screenH) :Ship(S, S1, X, Y, screenW, screenH)
	{
		weapon.setWeapon(2);
		weapon.setBullet(2, S1);
		Controls[0] = 1;
		Controls[1] = 15;
		Controls[2] = 16;
		Controls[3] = 4;
		Controls[4] = 22;
		Controls[5] = 0;
		Controls[6] = 3;
		Control = true;
		exploseW = 240;
		speedUp = 5000;
		maxspeed = 30000;
		endspeed = 30000;
		rotSpeed = 360;
		maxhp = 1000;
		health = 1000;
		w = 148;
		sprite.setPosition((float)screenW / 2, (float)screenH / 2);
		weapon.sprite.setPosition((float)screenW / 2, (float)screenH / 2);
		weapon.setRotation(180);
	}
	void update(float time, long double planetX, long double planetY, Sound *fly)
	{
		if (isMove && alife)
		{
			if (Control || longMoving)
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
				if (abs(speed) < abs(speedUp*time*4) && c < abs(speed*time*4))
				{
					x = tempX;
					y = tempY;
					c = 0;
					speedX = 0;
					speedY = 0;
					go = false;
					isMove = false;
					longMoving = false;
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
						if(dx) speedX -= speedX*speedX / dx / 2 * time;
						if(dy) speedY -= speedY*speedY / dy / 2 * time;
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
			}
			speedAnglerad = atan2(speedY, speedX);
			speed = sqrt(speedX*speedX + speedY*speedY);
			DGC = speed*speed / 2 / speedUp;
			DGCx = DGC*cos(speedAnglerad);
			DGCy = DGC*sin(speedAnglerad);
		}
		x += speedX*time;
		y += speedY*time;
		sprite.setRotation((float)rotation);
		weapon.checkForDel();
	}
	void move(long double X, long double Y)
	{
		x = X;
		y = Y;
		tempX = x;
		tempY = y;
	}
	void newGame(long double X, long double Y)
	{
		frame = 0;
		health = 1000;
		alife = isMove = go = true;
		speed = speedX = speedY = speedUpx = speedUpy = rotation = tempX = tempY = xAboutPlanet = yAboutPlanet = tempxAboutPlanet = tempyAboutPlanet = distanceToPlanet = 0;
		x = X;
		y = Y;
		tempX = x;
		tempY = y;
		sprite.setTextureRect(IntRect(0, 0, w, h));
		sprite.setOrigin((float)w / 1.8f, (float)h / 2);
	}
	void explose(Sound *explode, float time, float v)
	{
		x += speedX*time;
		y += speedY*time;
		if (alife)
		{
			maxed = true;
			alife = false;
			health = 0;
			explode->setVolume(v);
			explode->play();
		}
		if (frame<8)
			sprite.setTextureRect(IntRect(0, 72 + exploseW * int(frame), exploseW, exploseW));
		else
			sprite.setTextureRect(IntRect(259, 72 + exploseW * int(frame - 8), exploseW, exploseW));
		sprite.setOrigin((float)sprite.getTextureRect().width / 2, (float)sprite.getTextureRect().height / 2);
		frame += time * 24;
	}
	void keyControl(float time)
	{
		if (Keyboard::isKeyPressed(Keyboard::Key(Controls[4])))
		{
			isMove = true;
			longMoving = false;
			double rad = rotation / 57.2957795131;
			if ((abs(speedX)<abs(speedUpx*time) && abs(speedY)<abs(speedUpy*time)) || abs(rad - speedAnglerad) < rotSpeed / 57.2957795131*time)
			{
				speedX = speed*cos(rad);
				speedY = speed*sin(rad);
				speedUpx = speedUp*cos(rad);
				speedUpy = speedUp*sin(rad);
				maxspeed = 3000;
				if (speed < maxspeed)
				{
					maxed = false;
					speedX += speedUpx*time;
					speedY += speedUpy*time;
				}
				else maxed = true;
			}
			else
			{
				double a = cos(rad) - cos(speedAnglerad);
				double b = sin(rad) - sin(speedAnglerad);
				rad = atan2(b, a);
				speedUpx = speedUp*cos(rad);
				speedUpy = speedUp*sin(rad);
				speedX += speedUpx*time;
				speedY += speedUpy*time;
			}
			sprite.setTextureRect(IntRect(w, 0, w, h));
		}
		else
		{
			sprite.setTextureRect(IntRect(0, 0, w, h));
			double slowx = speedUp*cos(speedAnglerad);
			double slowy = speedUp*sin(speedAnglerad);
			if (abs(speedX) > abs(slowx*time/2) || abs(speedY) > abs(slowy*time/2))
			{
				speedX -= slowx*time;
				speedY -= slowy*time;
			}
			else 
			{
				speedX = 0;
				speedY = 0;
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Key(Controls[5])))
		{
			longMoving = false;
			rotation -= rotSpeed*time;
			if (rotation < -180) rotation += 360;
			weapon.rotation -= (float)rotSpeed*time;
			weapon.sprite.setRotation(weapon.rotation);
		}
		if (Keyboard::isKeyPressed(Keyboard::Key(Controls[6])))
		{
			longMoving = false;
			rotation += rotSpeed*time;
			if (rotation > 180) rotation -= 360;
			weapon.rotation += (float)rotSpeed*time;
			weapon.sprite.setRotation(weapon.rotation);
		}
	}
	double getspeedX()
	{
		return speedX;
	}
	double getspeedY()
	{
		return speedY;
	}
	long double getDistance()
	{
		return c;
	}
};