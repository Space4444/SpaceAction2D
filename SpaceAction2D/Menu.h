#include <SFML/Graphics.hpp>
#include "str.h"
using namespace sf;
class Menu{
private:
	Font font;
	Texture texture;
public:
	Sprite sprite;
	Text text[9], New, Continue, Exit, Settings, Back, Close, t, control;
	RectangleShape line1, line2, rect1, rect2;
	float v1, v2;
	unsigned char page, changingControl;
	bool showMenu, changingVolume1, changingVolume2;
	Menu(String file, Font f, int w, int h)
	{
		changingControl = 0;
		text[0] = Text("Mouse", font, 30);
		text[1] = Text("Left mouse button", font, 30);
		text[2] = Text("P", font, 30);
		text[3] = Text("E", font, 30);
		text[4] = Text("Q", font, 30);
		text[5] = Text("W", font, 30);
		text[6] = Text("A", font, 30);
		text[7] = Text("D", font, 30);
		text[8] = Text("Moving", font, 30);
		for (unsigned char i = 0; i < 8; i++)
		{
			text[i].setPosition((float)w / 2, (float)h * (i + 1) / 9 + 15);
			text[i].setColor(Color(255, 255, 0));
		}
		text[8].setColor(Color(255, 255, 0));
		text[0].setColor(Color(0, 255, 0));
		Image image;
		showMenu = true;
		changingVolume1 = changingVolume2 = false;
		page = 0;
		v1 = v2 = 50;
		font = f;
		line1.setFillColor(Color(0, 255, 0));
		line1.setSize(Vector2f((float)w / 2, 4));
		line1.setOrigin(0, 2);
		line2.setFillColor(Color(0, 255, 0));
		line2.setSize(Vector2f((float)w / 2, 4));
		line2.setOrigin(0, 2);
		rect1.setFillColor(Color(0, 128, 0));
		rect1.setSize(Vector2f((float)12, 24));
		rect1.setOrigin(6, 12);
		rect1.setOutlineColor(Color(0, 64, 0));
		rect2.setFillColor(Color(0, 128, 0));
		rect2.setSize(Vector2f((float)12, 24));
		rect2.setOrigin(6, 12);
		rect2.setOutlineColor(Color(0, 64, 0));
		New.setString("New game");
		New.setFont(font);
		New.setColor(Color(255, 255, 0));
		Continue.setString("Continue");
		Continue.setFont(font);
		Continue.setColor(Color(255, 255, 0));
		Exit.setString("Exit");
		Exit.setFont(font);
		Exit.setColor(Color(255, 255, 0));
		Settings.setString("Settings");
		Settings.setFont(font);
		Settings.setColor(Color(255, 255, 0));
		Back.setString("Back");
		Back.setFont(font);
		Back.setColor(Color(255, 255, 0));
		Close.setString("Close");
		Close.setFont(font);
		Close.setColor(Color(255, 255, 0));
		control.setFont(font);
		control.setColor(Color(0, 255, 0));
		t.setCharacterSize(22);
		t.setFont(font);
		t.setColor(Color(255, 255, 0));
		image.loadFromFile("images/" + file);
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setScale((float)w / texture.getSize().x, (float)h / texture.getSize().y);
		
		New.setPosition((float)w / 2, (float)h / 2 - 150);
		Continue.setPosition((float)w / 2, (float)h / 2 - 50);
		Settings.setPosition((float)w / 2, (float)h / 2 + 50);
		Exit.setPosition((float)w / 2, (float)h / 2 + 150);
		Close.setPosition((float)w - 122, (float)h - 44);
		Back.setPosition(122, (float)h - 44);
		sprite.setPosition(0, 0);

		line1.setPosition((float)w / 4, (float)h / 4);
		line2.setPosition((float)w / 4, (float)h / 2);
	}
	void update0(Vector2f mouse, bool saved, RenderWindow *window){
		window->draw(sprite);
		
		if (saved) Continue.setColor(Color(255, 255, 0)); else Continue.setColor(Color(128, 128, 0));
		
		if (New.getGlobalBounds().contains(mouse)) New.setCharacterSize(70); else New.setCharacterSize(50);
		if (Continue.getGlobalBounds().contains(mouse) && saved) Continue.setCharacterSize(70); else Continue.setCharacterSize(50);
		if (Settings.getGlobalBounds().contains(mouse)) Settings.setCharacterSize(70); else Settings.setCharacterSize(50);
		if (Exit.getGlobalBounds().contains(mouse)) Exit.setCharacterSize(70); else Exit.setCharacterSize(50);

		New.setOrigin(New.getGlobalBounds().width / 2, New.getGlobalBounds().height / 2);
		Continue.setOrigin(Continue.getGlobalBounds().width / 2, Continue.getGlobalBounds().height / 2);
		Settings.setOrigin(Settings.getGlobalBounds().width / 2, Settings.getGlobalBounds().height / 2);
		Exit.setOrigin(Exit.getGlobalBounds().width / 2, Exit.getGlobalBounds().height / 2);
		
		window->draw(New);
		window->draw(Continue);
		window->draw(Settings);
		window->draw(Exit);
	}
	void update1(Vector2f mouse, bool saved, RenderWindow *window){
		window->draw(sprite);
		BackOrClose(mouse);
		float w = (float)window->getSize().x, h = (float)window->getSize().y;
		if (changingVolume1)
		{
			v1 = (mouse.x - w / 4) * 100 / w * 2;
			if (v1 > 100) v1 = 100; else if (v1 < 0) v1 = 0;
		}
		if (changingVolume2)
		{
			v2 = (mouse.x - w / 4) * 100 / w * 2;
			if (v2 > 100) v2 = 100; else if (v2 < 0) v2 = 0;
		}
		rect1.setPosition(w / 4 + v1 / 100 * w / 2, h / 4);
		if (rect1.getGlobalBounds().contains(mouse)) rect1.setOutlineThickness(4); else rect1.setOutlineThickness(0);
		t.setString("Music");
		t.setPosition(w / 4 - 65, h / 4 - 16);
		window->draw(t);
		rect2.setPosition(w / 4 + v2 / 100 * w / 2, h / 2);
		if (rect2.getGlobalBounds().contains(mouse)) rect2.setOutlineThickness(4); else rect2.setOutlineThickness(0);
		t.setString("Sound");
		t.setPosition(w / 4 - 70, h / 2 - 16);
		window->draw(t);
		control.setPosition((float)w / 2, (float)h * 0.75f);
		control.setString("Controls");
		if (control.getGlobalBounds().contains(mouse)) control.setCharacterSize(70); else control.setCharacterSize(50);
		control.setOrigin(control.getGlobalBounds().width / 2, control.getGlobalBounds().height / 2);
		window->draw(control);
		window->draw(line1);
		window->draw(rect1);
		window->draw(line2);
		window->draw(rect2);
		window->draw(Back);
		if(saved) window->draw(Close);
	}
	void update2(Vector2f mouse, bool saved, RenderWindow *window, Player *p, float time)
	{
		window->draw(sprite);
		BackOrClose(mouse);
		float w = (float)window->getSize().x, h = (float)window->getSize().y;
		for (unsigned char i = 1; i < 5; i++)
		{
			if (i == 1)
				text[1].setString(strM(p->Controls[0]));
			else
				text[i].setString(strK(p->Controls[i - 1]));
			if (i != changingControl)
			{
				if (text[i].getGlobalBounds().contains(mouse)) text[i].setCharacterSize(44); else text[i].setCharacterSize(30);
				text[i].setColor(Color(255, 255, 0));
			}
			text[i].setOrigin(text[i].getGlobalBounds().width / 2, text[i].getGlobalBounds().height / 2);
		}
		for (unsigned char i = 1; i < 5; i++) window->draw(text[i]);

		text[8].setString("Moving:");
		text[8].setPosition(w / 4, h / 9);
		window->draw(text[8]);
		text[8].setString("Fire:");
		text[8].setPosition(w / 4, h * 2 / 9);
		window->draw(text[8]);
		text[8].setString("Pause:");
		text[8].setPosition(w / 4, h * 1 / 3);
		window->draw(text[8]);
		text[8].setString("Scale min:");
		text[8].setPosition(w / 4, h * 4 / 9);
		window->draw(text[8]);
		text[8].setString("Scale max:");
		text[8].setPosition(w / 4, h * 5 / 9);
		window->draw(text[8]);

		if (!p->Control)
		{
			for (unsigned char i = 5; i < 8; i++)
			{
				text[i].setString(strK(p->Controls[i - 1]));
				if (i != changingControl)
				{
					if (text[i].getGlobalBounds().contains(mouse)) text[i].setCharacterSize(44); else text[i].setCharacterSize(30);
					text[i].setColor(Color(255, 255, 0));
				}
				text[i].setOrigin(text[i].getGlobalBounds().width / 2, text[i].getGlobalBounds().height / 2);
			}

			for (unsigned char i = 5; i < 8; i++) window->draw(text[i]);

			text[0].setString("Keyboard");

			text[8].setString("Speedup:");
			text[8].setPosition(w / 4, h * 2 / 3);
			window->draw(text[8]);
			text[8].setString("Left:");
			text[8].setPosition(w / 4, h * 7 / 9);
			window->draw(text[8]);
			text[8].setString("Right:");
			text[8].setPosition(w / 4, h * 8 / 9);
			window->draw(text[8]);
		}
		else
		{
			text[0].setString("Mouse");
			text[1].setString(strM(p->Controls[0]));
			if (1 == changingControl)
				blink(&text[1], time);
			else
			{
				text[1].setColor(Color(255, 255, 0));
				if (text[1].getGlobalBounds().contains(mouse)) text[1].setCharacterSize(44); else text[1].setCharacterSize(30);
			}
			text[1].setOrigin(text[1].getGlobalBounds().width / 2, text[1].getGlobalBounds().height / 2);
			window->draw(text[0]);
			window->draw(text[1]);
		}
		if (changingControl) blink(&text[changingControl], time);
		if (text[0].getGlobalBounds().contains(mouse)) text[0].setCharacterSize(55); else text[0].setCharacterSize(44);
		text[0].setOrigin(text[0].getGlobalBounds().width / 2, text[0].getGlobalBounds().height / 2);
		window->draw(text[0]);
		window->draw(Back);
		if(saved) window->draw(Close);
	}
	void BackOrClose(Vector2f mouse)
	{
		if (Back.getGlobalBounds().contains(mouse)) Back.setCharacterSize(33); else Back.setCharacterSize(25);
		if (Close.getGlobalBounds().contains(mouse)) Close.setCharacterSize(33); else Close.setCharacterSize(25);
		Close.setOrigin(Close.getGlobalBounds().width / 2, Close.getGlobalBounds().height / 2);
		Back.setOrigin(Back.getGlobalBounds().width / 2, Back.getGlobalBounds().height / 2);
	}
	void blink(Text *t, float time)
	{
		unsigned char r = t->getColor().r, g = t->getColor().g;
		if (r < 250 && g == 64) r += int(time * 1000);
		if (g < 250 && r == 250) g += int(time * 1000);
		if (r > 64 && g == 250) r -= int(time * 1000);
		if (g > 64 && r == 64) g -= int(time * 1000);
		if (r >= 250) r = 250;
		if (g >= 250) g = 250;
		if (r <= 64) r = 64;
		if (g <= 64) g = 64;
		t->setColor(Color(r, g, t->getColor().b));
		t->setCharacterSize(45);
	}
};