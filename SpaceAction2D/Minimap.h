#include <SFML/Graphics.hpp>
using namespace sf;
class Minimap
{
public:
	VertexArray rect;
	VertexArray lines;
	RectangleShape map;
	bool changingSize;
	unsigned char chosenPlanet, targetPlanet;
	float posx, posy;
	float size, psize, px, py, r;
	long double scale;
	CircleShape planet, star, enemy, circle;
	Text text, Scale;
	std::list<Ship*>::iterator it;
	Minimap(int h, Font *font)
	{
		posx = 4;
		posy = (float)h - 4;
		changingSize = false;
		chosenPlanet = targetPlanet = 0;
		scale = 2500000000;
		size = 181;
		r = size / 2;
		rect.setPrimitiveType(LinesStrip);
		rect.resize(5);
		lines.setPrimitiveType(Lines);
		lines.resize(14);
		rect[0].position = Vector2f(posx-1, posy - size);
		rect[1].position = Vector2f(posx + size, posy - size);
		rect[2].position = Vector2f(posx + size, posy);
		rect[3].position = Vector2f(posx, posy);
		rect[4].position = Vector2f(posx, posy - size);
		lines[0].position = Vector2f(posx + r, posy - size);
		lines[1].position = Vector2f(posx + r, posy);
		lines[2].position = Vector2f(posx, posy - r);
		lines[3].position = Vector2f(posx + size, posy - r);
		lines[4].position = Vector2f(posx + size - 20, posy - size);
		lines[5].position = Vector2f(posx + size - 20, posy - size + 20);
		lines[6].position = Vector2f(posx + size - 20, posy - size + 20);
		lines[7].position = Vector2f(posx + size, posy - size + 20);
		lines[8].position = Vector2f(posx + size - 17, posy - size + 5);
		lines[9].position = Vector2f(posx + size - 4, posy - size + 5);
		lines[10].position = Vector2f(posx + size - 17, posy - size + 10);
		lines[11].position = Vector2f(posx + size - 4, posy - size + 10);
		lines[12].position = Vector2f(posx + size - 17, posy - size + 15);
		lines[13].position = Vector2f(posx + size - 4, posy - size + 15);
		for (__int8 i = 0; i < 5; i++) rect[i].color = Color::Green;
		for (__int8 i = 0; i < 14; i++) lines[i].color = Color::Green;
		map.setSize(Vector2f(size, size));
		map.setFillColor(Color(64, 0, 128, 128));
		map.setPosition(posx, posy - size);
		star.setRadius(7);
		planet.setRadius(5);
		enemy.setRadius(3);
		planet.setFillColor(Color(255, 255, 255));
		planet.setOrigin(5, 5);
		star.setFillColor(Color(255, 255, 0));
		star.setOrigin(7, 7);
		enemy.setFillColor(Color(255, 0, 0));
		enemy.setOrigin(3, 3);
		circle.setFillColor(Color(0, 0, 0, 0));
		circle.setOutlineThickness(1);
		circle.setOutlineColor(Color(0, 255, 0));
		circle.setRadius(r);
		circle.setPosition(posx, posy - size);
		text.setString("Show map");
		text.setCharacterSize(18);
		text.setFont(*font);
		text.setPosition(posx + r, posy - size - 40);
		Scale.setString("1:2500000000");
		Scale.setCharacterSize(16);
		Scale.setFont(*font);
		Scale.setPosition(posx + r, posy - size - 20);
		Scale.setOrigin(Scale.getGlobalBounds().width / 2, 4);
		planet.setOutlineThickness(3);
	}
	void drawPlanet(RenderWindow *window, int n, Vector2f mouse, long double X, long double Y, long double x, long double y, unsigned char i, unsigned char currentPlanet, float depth)
	{
		x = (x * depth - X) / scale;
		y = (y * depth - Y) / scale;
		if (x*x + y*y > r*r)
		{
			float angle = (float)atan2(y, x);
			x = r * cos(angle);
			y = r * sin(angle);
		}
		x += posx + r;
		y += posy - r;
		planet.setPosition((float)x, (float)y);
		
		if (planet.getGlobalBounds().contains(mouse))
		{
			chosenPlanet = i;
			planet.setRadius(7);
			planet.setOrigin(7, 7);
		}
		else
		{
			planet.setRadius(5);
			planet.setOrigin(5, 5);
		}
		if (i == targetPlanet)
			planet.setFillColor(Color(0, 255, 0));
		else
			planet.setFillColor(Color(255, 255, 255));
		planet.setOutlineColor(Color(0, 0, 255, (i == currentPlanet)*255));
		window->draw(planet);
	}
	void drawAllButPlanets(RenderWindow *window, std::list<Ship*> *enemies, Vector2f mouse, long double X, long double Y)
	{
		if (changingSize) setSize(mouse);
		float x = (float)(-X / scale);
		float y = (float)(-Y / scale);
		if (x*x + y*y > r*r)
		{
			float angle = atan2(y, x);
			x = r * cos(angle);
			y = r * sin(angle);	
		}
		star.setPosition((float)(posx + x + r), (float)(posy - r + y));
		window->draw(star);
		for (it = enemies->begin(); it != enemies->end(); it++)
		{
			x = (float)(((*it)->x - X) / scale);
			y = (float)(((*it)->y - Y) / scale);
			if (x*x + y*y > r*r)
			{
				float angle = atan2(y, x);
				x = r * cos(angle);
				y = r * sin(angle);
			}
			enemy.setPosition((float)(posx + x + r), (float)(posy - r + y));
			window->draw(enemy);
		}
		window->draw(rect);
		window->draw(lines);
		window->draw(circle);
		if (targetPlanet!=0)
			text.setString("Teleport!");
		else
			text.setString("Show map");
		if (text.getGlobalBounds().contains(mouse))
		{
			text.setCharacterSize(24);
			text.setOrigin(55, 12);
		}
		else
		{
			text.setCharacterSize(18);
			text.setOrigin(44, 9);
		}
		window->draw(text);
		window->draw(Scale);
	}
	void setSize(Vector2f mouse)
	{
		r = size / 2;
		float s = psize + (mouse.x - px + py - mouse.y) / 2;
		if (s < 100)
			size = 100;
		else if (s>500)
			size = 500;
		else
			size = s;
		rect[0].position = Vector2f(posx - 1, posy - size);
		rect[1].position = Vector2f(posx + size, posy - size);
		rect[2].position = Vector2f(posx + size, posy);
		rect[3].position = Vector2f(posx, posy);
		rect[4].position = Vector2f(posx, posy - size);
		lines[0].position = Vector2f(posx + r, posy - size);
		lines[1].position = Vector2f(posx + r, posy);
		lines[2].position = Vector2f(posx, posy - r);
		lines[3].position = Vector2f(posx + size, posy - r);
		lines[4].position = Vector2f(posx + size - 20, posy - size);
		lines[5].position = Vector2f(posx + size - 20, posy - size + 20);
		lines[6].position = Vector2f(posx + size - 20, posy - size + 20);
		lines[7].position = Vector2f(posx + size, posy - size + 20);
		lines[8].position = Vector2f(posx + size - 17, posy - size + 5);
		lines[9].position = Vector2f(posx + size - 4, posy - size + 5);
		lines[10].position = Vector2f(posx + size - 17, posy - size + 10);
		lines[11].position = Vector2f(posx + size - 4, posy - size + 10);
		lines[12].position = Vector2f(posx + size - 17, posy - size + 15);
		lines[13].position = Vector2f(posx + size - 4, posy - size + 15);
		circle.setRadius(r);
		circle.setPosition(posx, posy - size);
		text.setPosition(posx + r, posy - size - 40);
		Scale.setPosition(posx + r, posy - size - 20);
		map.setSize(Vector2f(size, size));
		map.setPosition(posx, posy - size);
	}
	void fly(Vector2f mouse, Player *p)
	{
		if (mouse.x < posx + size - 20 || mouse.y > posy - size + 20)
		{
			p->longMoving = true;
			p->fly(p->x + (mouse.x - r - posx)*scale, p->y + (mouse.y + r - posy)*scale);
		}
		else
		{
			changingSize = true;
			px = mouse.x;
			py = mouse.y;
			psize = size;
		}
	}
	void setScale(long double s)
	{
		if (s < 50) s = 50;
		if (s>10000000000) s = 10000000000;
		scale = s;
		std::ostringstream scale;
		scale << "1:" << (__int64)s;
		Scale.setString(scale.str());
		Scale.setOrigin(Scale.getGlobalBounds().width / 2, 4);
	}
};