#include <SFML/Graphics.hpp>
using namespace sf;
class Enemy :public Ship
{
public:
	Enemy(Sprite S, Sprite S1, long double X, long double Y, int screenW, int screenH) :Ship(S, S1, X, Y, screenW, screenH)
	{
		exploseW = 130;
		maxspeed = 20000;
		endspeed = 20000;
		speedUp = 5000;
		maxhp = 500;
		health = 500;
		w = 148;
		randomize();
	}
	void setTarget(float time, Ship *p, Sound *gun)
	{
		if (p->alife)
		{
			double a = p->x + p->DGCx - x;
			double b = p->y + p->DGCy - y;
			if (sqrt(a*a + b*b) > 400)
			{
				if (!randomized) randomize();
				fly(p->x + p->DGCx + randX, p->y + p->DGCy + randY);
			}
			else randomized = false;
			a = p->x - x;
			b = p->y - y;
			if (sqrt(a*a + b*b) < 400) weapon.fight(time, (float)atan2(y - p->y, x - p->x), x, y, (float)speedX, (float)speedY, gun);
		}
		else
		{
			tempX = p->x + randX * 10000;
			tempY = p->y + randY * 10000;
			isMove = true;
		}
	}
	void hitted(float dmg)
	{
		randomize();
		if (!isMove) fly(x + randX, y + randY);
		health -= (int)dmg;
	}
	void randomize()
	{
		randomized = true;
		randX = -200 + rand() % 400;
		randY = -200 + rand() % 400;
	}
};