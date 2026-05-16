#include <SFML/Graphics.hpp>
using namespace sf;
class Weapon
{
public:
	bool ready;
	float timer, rate, speed, rotation, rotSpeed, dmg;
	Texture texture;
	Sprite sprite, s;
	std::list<Bullet*>  Bullets;
	std::list<Bullet*>::iterator it;
	Weapon(){}
	void setWeapon(__int8 type)
	{
		ready = false;
		Image image;
		switch (type)
		{
		case 1: rate = 0.2f; speed = 500; rotSpeed = 180; image.loadFromFile("images/redGun.png"); break;
		case 2: rate = 0.05f; speed = 1200; rotSpeed = 540; image.loadFromFile("images/blueGun.png"); break;
		}
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setOrigin((float)sprite.getTextureRect().width / 2, (float)sprite.getTextureRect().height / 2);
	}
	void setBullet(__int8 type, Sprite sp)
	{
		switch (type)
		{
		case 1: dmg=5; break;
		case 2: dmg=44; break;
		}
		s = sp;
	}
	void setRotation(float r)
	{
		rotation = r;
		sprite.setRotation(r);
	}
	void rotate(float time, float angle)
	{
		float delta = angle - rotation;
		if (delta > 180) delta -= 360;
		else if (delta < -180) delta += 360;
		float tempVar = rotSpeed*time;
		if (abs(delta)>tempVar)
		{
			if (delta > 0) rotation += tempVar; else rotation -= tempVar;
			ready = false;
		}
		else
		{
			rotation = angle;
			ready = true;
		}
		sprite.setRotation(rotation);
		rotation = sprite.getRotation();
	}
	void checkForDel()
	{
		if (!Bullets.empty() && (*Bullets.begin())->timer > 1) Bullets.pop_front();
	}
	void fight(float time, float angle, long double x, long double y, float vx, float vy, Sound *gun)
	{
		rotate(time, angle*57.2957795131f);
		if (timer > rate && ready)
		{
			timer = 0;
			Bullets.push_back(new Bullet(s, x, y, angle, vx, vy, speed));
			gun->play();
		}
		timer += time;
	}
	int hitTest(long double X, long double Y, Sound *hit, float v)
	{
		int damage = 0;
		for (it = Bullets.begin(); it != Bullets.end();)
		{
			double a = (*it)->x - X;
			double b = (*it)->y - Y;
			if (sqrt(a*a + b*b) < 44 && !(*it)->play)
			{
				damage += (int)dmg;
				(*it)->play = true;
				hit->setVolume(v);
				hit->play();
			}
			if ((*it)->frame >= 12)
			{
				Bullet *d = *it;
				it = Bullets.erase(it);
				delete d;
			}
			else it++;
		}
		return damage;
	}
	bool hitTest1(Sound *hit, float v, float time, long double x, long double y, long double x1, long double y1, double speedX, double speedY)
	{
		bool b = false;
		for (it = Bullets.begin(); it != Bullets.end();)
		{
			double a = (*it)->x - x1 + speedX*time, a1 = (*it)->x - x;
			double b = (*it)->y - y1 + speedY*time, b1 = (*it)->y - y;
			if (sqrt(a*a + b*b) < 44 && !(*it)->play)
			{
				b =  true;
				(*it)->speedX = (float)speedX;
				(*it)->speedY = (float)speedY;
				(*it)->play = true;
				hit->setVolume((float)(100 * v / (sqrt(a1*a1 + b1*b1) + 100)));
				hit->play();
			}
			else b = false;
			if ((*it)->frame >= 12)
			{
				Bullet *d = *it;
				it = Bullets.erase(it);
				delete d;
			}
			else it++;
			if (b) return true;
		}
		return b;
	}
};