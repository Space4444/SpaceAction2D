#include <SFML/Graphics.hpp>
using namespace sf;
class Bullet 
{
public:
	long double x, y, xAboutPlanet, yAboutPlanet;
	float frame, speed, rotation, timer, speedX, speedY;
	bool play;
	Sprite sprite;
	Bullet(Sprite S, long double X, long double Y, float R, float vX, float vY, float s)
	{
		play = false;
		xAboutPlanet = yAboutPlanet = 0;
		x = X;
		y = Y;
		frame = 0;
		speedX = vX;
		speedY = vY;
		speed = s;
		timer = 0;
		rotation = R + 3.14159265359f;// -0.5 + (float)(rand() % 20) / 20;
		sprite = S;
		sprite.setRotation(rotation*57.2957795131f);
	}
	void update(float time)
	{
		timer += time;
		x += speedX*time;
		y += speedY*time;
		if (play)
		{
			sprite.setTextureRect(IntRect(22 + 39 * int(frame), 0, 39, 39));
			sprite.setOrigin((float)sprite.getTextureRect().width / 2, (float)sprite.getTextureRect().height / 2);
			frame += time*24;
		}
		else
		{
			x += speed*cos(rotation)*time;
			y += speed*sin(rotation)*time;
		}
	}
};