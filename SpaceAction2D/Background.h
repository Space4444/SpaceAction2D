#include <SFML/Graphics.hpp>
using namespace sf;
class Background{
public:
	float **coords;
	float *size;
	Color *color;
	Sprite sprite;
	Texture texture;
	CircleShape *circle;
	Background(int w, int h)
	{
		circle = new CircleShape[33];
		coords = new float*[33];
		size = new float[200];
		color = new Color[200];
		for (unsigned __int8 i = 0; i < 33; i++)
		{
			coords[i] = new float[2];
			coords[i][1] = (float)(rand() % w);
			coords[i][2] = (float)(rand() % h);
			size[i] = 1 + (float)(rand() % 20)/10;
			color[i] = Color(rand() % 255, rand() % 255, rand() % 255);
			circle[i].setRadius(size[i]);
			circle[i].setFillColor(color[i]);
			circle[i].setOutlineThickness(size[i]);
			circle[i].setOutlineColor(Color(color[i].r, color[i].g, color[i].b, color[i].a / 2));
			circle[i].setOrigin(size[i], size[i]);
			circle[i].setPosition(coords[i][1], coords[i][2]);
		}
	}
	void loadImage(String file, int w, int h){
		Image image;
		image.loadFromFile(file);
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setOrigin((float)w / 2, (float)h / 2);
	}
	void createImage(RenderWindow *window, Text *text)
	{
		Image tempImage, image;
		int w = window->getSize().x, h = window->getSize().y;
		int a = 50 + rand() % (w - 100), b = 50 + rand() % (h - 100);
		int x1 = rand() % 256, y1 = rand() % 256, z1 = rand() % 256;
		float x = (float)x1 / (x1 + y1 + z1) * 255;
		float y = (float)y1 / (x1 + y1 + z1) * 255;
		float z = (float)z1 / (x1 + y1 + z1) * 255;
		image.create(w, h, Color((Uint8)(x / 4), (Uint8)(y / 4), (Uint8)(z / 4)));
		tempImage.create(w, h, Color((Uint8)(x / 4), (Uint8)(y / 4), (Uint8)(z / 4)));
		text->setPosition(300, 250);
		int random = 200000 + rand() % 400001;
		for (int i = 0; i < random; i++)
		{
			a += (rand() % 3) - 1;
			b += (rand() % 3) - 1;
			x += (float)((rand() % 101) - 50) / 200;
			y += (float)((rand() % 101) - 50) / 200;
			z += (float)((rand() % 101) - 50) / 200;
			if (x>200)
				x = 199;
			else if (x < 55)
				x = 56;
			if (y>200)
				y = 199;
			else if (y < 55)
				y = 56;
			if (z>200)
				z = 199;
			else if (z < 55)
				z = 56;
			if (a < 20 || a > w - 21 || b < 20 || b > h - 21)
			{
				a = 20 + rand() % (w - 41);
				b = 20 + rand() % (h - 41);
				x1 = rand() % 256;
				y1 = rand() % 256;
				z1 = rand() % 255;
				x = (float)x1 / (x1 + y1 + z1) * 255;
				y = (float)y1 / (x1 + y1 + z1) * 255;
				z = (float)z1 / (x1 + y1 + z1) * 255;
			}
			image.setPixel(a, b, Color((Uint8)x, (Uint8)y, (Uint8)z));
		}
		int l = 0;
		float m = 16;
		for (__int16 s = 0; s < m; s++)
		{
			l = int(s / m * 100);
			std::ostringstream load;
			load << l << "% of universe created.";
			text->setString(load.str());
			window->draw(*text);
			window->display();
			window->clear();
			for (unsigned __int16 i = 1; i < w - 1; i++)
			for (unsigned __int16 j = 1; j < h - 1; j++)
			{
				x = (float)(image.getPixel(i, j).r + image.getPixel(i + 1, j).r + image.getPixel(i - 1, j).r + image.getPixel(i, j + 1).r + image.getPixel(i, j - 1).r) / 5;
				y = (float)(image.getPixel(i, j).g + image.getPixel(i + 1, j).g + image.getPixel(i - 1, j).g + image.getPixel(i, j + 1).g + image.getPixel(i, j - 1).g) / 5;
				z = (float)(image.getPixel(i, j).b + image.getPixel(i + 1, j).b + image.getPixel(i - 1, j).b + image.getPixel(i, j + 1).b + image.getPixel(i, j - 1).b) / 5;
				tempImage.setPixel(i, j, Color((Uint8)x, (Uint8)y, (Uint8)z));
			}
			for (unsigned __int16 i = 1; i < w - 1; i++)
			for (unsigned __int16 j = 1; j < h - 1; j++)
			{
				x = (float)(tempImage.getPixel(i, j).r + tempImage.getPixel(i + 1, j).r + image.getPixel(i - 1, j).r + image.getPixel(i, j + 1).r + image.getPixel(i, j - 1).r) / 5;
				y = (float)(tempImage.getPixel(i, j).g + tempImage.getPixel(i + 1, j).g + image.getPixel(i - 1, j).g + image.getPixel(i, j + 1).g + image.getPixel(i, j - 1).g) / 5;
				z = (float)(tempImage.getPixel(i, j).b + tempImage.getPixel(i + 1, j).b + image.getPixel(i - 1, j).b + image.getPixel(i, j + 1).b + image.getPixel(i, j - 1).b) / 5;
				image.setPixel(i, j, Color((Uint8)x, (Uint8)y, (Uint8)z));
			}
		}
		random = 333 + rand() % 444;
		for (int i = 0; i < random; i++)
		{
			a = rand() % w;
			b = rand() % h;
			x = (float)(55 + rand() % 200);
			image.setPixel(a, b, Color(255, 255, 255, (Uint8)x));
		}
		random = 32 + rand() % 80;
		for (int i = 0; i < random; i++)
		{
			__int8 size = (rand() % 8) * 2;
			a = size * 2 + 1 + rand() % (w - size * 4 - 2);
			b = size * 2 + 1 + rand() % (h - size * 4 - 2);
			x = (float)(151 + rand() % 105);
			y = (float)(151 + rand() % 105);
			z = (float)(151 + rand() % 105);
			/////////////////////////////////////////////////////////////////////////////////
			__int8 r = rand() % 2;
			if (r)
			for (int j = 1; j < size; j++)
			{
				float k = (float)(255 - j * 255 / size) / 511;
				__int16 cr = (__int16)(image.getPixel(a + j, b).r + x*k);
				__int16 cg = (__int16)(image.getPixel(a + j, b).g + y*k);
				__int16 cb = (__int16)(image.getPixel(a + j, b).b + z*k);
				if (cr>255)
					cr = 255;
				if (cg>255)
					cg = 255;
				if (cb>255)
					cb = 255;
				image.setPixel(a + j, b, Color((Uint8)cr, (Uint8)cg, (Uint8)cb));
				cr = (__int16)(image.getPixel(a - j, b).r + x*k);
				cg = (__int16)(image.getPixel(a - j, b).g + y*k);
				cb = (__int16)(image.getPixel(a - j, b).b + z*k);
				if (cr>255)
					cr = 255;
				if (cg>255)
					cg = 255;
				if (cb>255)
					cb = 255;
				image.setPixel(a - j, b, Color((Uint8)cr, (Uint8)cg, (Uint8)cb));
				cr = (__int16)(image.getPixel(a, b + j).r + x*k);
				cg = (__int16)(image.getPixel(a, b + j).g + y*k);
				cb = (__int16)(image.getPixel(a, b + j).b + z*k);
				if (cr>255)
					cr = 255;
				if (cg>255)
					cg = 255;
				if (cb>255)
					cb = 255;
				image.setPixel(a, b + j, Color((Uint8)cr, (Uint8)cg, (Uint8)cb));
				cr = (__int16)(image.getPixel(a, b - j).r + x*k);
				cg = (__int16)(image.getPixel(a, b - j).g + y*k);
				cb = (__int16)(image.getPixel(a, b - j).b + z*k);
				if (cr>255)
					cr = 255;
				if (cg>255)
					cg = 255;
				if (cb>255)
					cb = 255;
				image.setPixel(a, b - j, Color((Uint8)cr, (Uint8)cg, (Uint8)cb));
			}
			else
			for (int j = 1; j <= size / sqrt(2); j++)
			{
				float k = (float)(255 - j * 360 / size) / 511;
				__int16 cr = (__int16)(image.getPixel(a + j, b + j).r + x*k);
				__int16 cg = (__int16)(image.getPixel(a + j, b + j).g + y*k);
				__int16 cb = (__int16)(image.getPixel(a + j, b + j).b + z*k);
				if (cr>255)
					cr = 255;
				if (cg>255)
					cg = 255;
				if (cb>255)
					cb = 255;
				image.setPixel(a + j, b + j, Color((Uint8)cr, (Uint8)cg, (Uint8)cb));
				cr = (__int16)(image.getPixel(a + j, b - j).r + x*k);
				cg = (__int16)(image.getPixel(a + j, b - j).g + y*k);
				cb = (__int16)(image.getPixel(a + j, b - j).b + z*k);
				if (cr>255)
					cr = 255;
				if (cg>255)
					cg = 255;
				if (cb>255)
					cb = 255;
				image.setPixel(a + j, b - j, Color((Uint8)cr, (Uint8)cg, (Uint8)cb));
				cr = (__int16)(image.getPixel(a - j, b + j).r + x*k);
				cg = (__int16)(image.getPixel(a - j, b + j).g + y*k);
				cb = (__int16)(image.getPixel(a - j, b + j).b + z*k);
				if (cr>255)
					cr = 255;
				if (cg>255)
					cg = 255;
				if (cb>255)
					cb = 255;
				image.setPixel(a - j, b + j, Color((Uint8)cr, (Uint8)cg, (Uint8)cb));
				cr = (__int16)(image.getPixel(a - j, b - j).r + x*k);
				cg = (__int16)(image.getPixel(a - j, b - j).g + y*k);
				cb = (__int16)(image.getPixel(a - j, b - j).b + z*k);
				if (cr>255)
					cr = 255;
				if (cg>255)
					cg = 255;
				if (cb>255)
					cb = 255;
				image.setPixel(a - j, b - j, Color((Uint8)cr, (Uint8)cg, (Uint8)cb));
			}
			/////////////////////////////////////////////////////////////////////////////////
			for (int j = a - size; j <= a + size; j++)
			for (int k = b - size; k <= b + size; k++)
			{
				if ((j - a)*(j - a) + (k - b)*(k - b) < size*size)
				{
					double c = sqrt((j - a)*(j - a) + (k - b)*(k - b));
					__int16 cr = (__int16)(image.getPixel(j, k).r + x*size / 8 / c - 32);
					__int16 cg = (__int16)(image.getPixel(j, k).g + y*size / 8 / c - 32);
					__int16 cb = (__int16)(image.getPixel(j, k).b + z*size / 8 / c - 32);
					if (cr>255)
						cr = 255;
					if (cr<image.getPixel(j, k).r)
						cr = image.getPixel(j, k).r;
					if (cg>255)
						cg = 255;
					if (cg<image.getPixel(j, k).g)
						cg = image.getPixel(j, k).g;
					if (cb>255)
						cb = 255;
					if (cb<image.getPixel(j, k).b)
						cb = image.getPixel(j, k).b;
					image.setPixel(j, k, Color((Uint8)cr, (Uint8)cg, (Uint8)cb));
				}
			}
			image.setPixel(a, b, Color(255, 255, 255));
		}
		image.saveToFile("images/background.png");
		texture.loadFromImage(image);

		sprite.setTexture(texture);
		sprite.setOrigin((float)w / 2, (float)h / 2);
	}
	void update(RenderWindow *window, long double x, long double y)
	{
		float w = (float)window->getSize().x, h = (float)window->getSize().y;
		float X1, Y1, X2, Y3;
		long double v = 0.002;//v - скорость движения фона относительно персонажа по сравнению со скоростью самого персонажа
		long double XxV = x*v, YxV = y*v;
		int n = (int)round(x / (w / v) + 0.5), m = (int)round(y / (h / v) + 0.5);
		if ((float)n / 2 == int((float)n / 2)){
			X1 = (float)((n + 0.5) * w - XxV);
			X2 = (float)((n - 0.5) * w - XxV);
		}
		else{
			X1 = (float)((n - 0.5) * w - XxV);
			X2 = (float)((n + 0.5) * w - XxV);
		}
		if ((float)m / 2 == int((float)m / 2)){
			Y1 = (float)((m + 0.5) * h - YxV);
			Y3 = (float)((m - 0.5) * h - YxV);
		}
		else{
			Y1 = (float)((m - 0.5) * h - YxV);
			Y3 = (float)((m + 0.5) * h - YxV);
		}
		sprite.setPosition(X1, Y1);
		window->draw(sprite);
		sprite.setPosition(X2, Y1);
		window->draw(sprite);
		sprite.setPosition(X1, Y3);
		window->draw(sprite);
		sprite.setPosition(X2, Y3);
		window->draw(sprite);
	}
	void update1(bool isMove, RenderWindow *window, float speedX, float speedY)
	{
		int w = window->getSize().x, h = window->getSize().y;
		for (unsigned __int8 i = 0; i < 33; i++)
		{
			if (isMove)
			{
				coords[i][1] -= speedX;
				coords[i][2] -= speedY;
				if (coords[i][1] >= (signed int)w)
				{
					coords[i][1] -= w*int(coords[i][1] / w);
					coords[i][2] = (float)(rand() % h);
				}
				if (coords[i][1] < 0)
				{
					coords[i][1] -= w*(int(coords[i][1] / w) - 1);
					coords[i][2] = (float)(rand() % h);
				}
				if (coords[i][2] >= (signed int)h)
				{
					coords[i][2] -= h*int(coords[i][1] / h);
					coords[i][1] = (float)(rand() % w);
				}
				if (coords[i][2] < 0)
				{
					coords[i][2] -= h*(int(coords[i][1] / h) - 1);
					coords[i][1] = (float)(rand() % w);
				}
				circle[i].setPosition(coords[i][1], coords[i][2]);
			}
			window->draw(circle[i]);
		}
	}
};