#include <SFML/Graphics.hpp>
using namespace sf;
class Universe{
private:
	Font font;
	Texture texture, *tg;
public:
	int ****planetInfo, **galaxyInfo, ***systemInfo;
	Sprite sprite, *sg;
	Text Back, Page;
	CircleShape shape, currentGalaxy, currentSystem;
	bool showMap, page;
	Universe(Font f, int w, int h)
	{
		Image *ig, image;

		showMap = page = false;

		ig = new Image[3];
		tg = new Texture[3];
		sg = new Sprite[3];

		systemInfo = new int**[20];
		for (int i = 0; i < 20; i++)
			systemInfo[i] = new int*[100];
		for (int i = 0; i < 20; i++)
		for (int j = 0; j < 100; j++)
			systemInfo[i][j] = new int[4];

		galaxyInfo = new int*[20];
		for (int i = 0; i < 20; i++)
			galaxyInfo[i] = new int[6];

		planetInfo = new int***[20];
		for (int i = 0; i < 20; i++)
			planetInfo[i] = new int**[100];
		for (int i = 0; i < 20; i++)
		for (int j = 0; j < 100; j++)
			planetInfo[i][j] = new int*[10];
		for (int i = 0; i < 20; i++)
		for (int j = 0; j < 100; j++)
		for (int k = 0; k < 10; k++)
			planetInfo[i][j][k] = new int[3];

		shape.setFillColor(Color(0, 0, 0, 0));
		shape.setOutlineThickness(2);
		shape.setOutlineColor(Color(255, 0, 0));

		currentGalaxy.setRadius(32);
		currentGalaxy.setFillColor(Color(0, 0, 0, 0));
		currentGalaxy.setOutlineThickness(4);
		currentGalaxy.setOutlineColor(Color(0, 0, 255));
		currentGalaxy.setOrigin(32, 32);

		currentSystem.setRadius(20);
		currentSystem.setFillColor(Color(0, 0, 0, 0));
		currentSystem.setOutlineThickness(4);
		currentSystem.setOutlineColor(Color(0, 0, 255));
		currentSystem.setOrigin(20, 20);

		font = f;

		Back.setString("Back");
		Back.setCharacterSize(22);
		Back.setFont(font);
		Back.setColor(Color(255, 255, 0));
		Page.setString("Show universe");
		Page.setCharacterSize(18);
		Page.setFont(font);
		Page.setColor(Color(255, 255, 0));
		for (int i = 0; i < 3; i++)
		{
			std::ostringstream s;
			s << "images/Galaxy" << i << ".png";
			ig[i].loadFromFile(s.str());
			tg[i].loadFromImage(ig[i]);
			sg[i].setTexture(tg[i]);
			sg[i].setOrigin(32, 32);
		}
	}
	void loadUniverse(String file, int w, int h)
	{
		FILE *fU, *fG, *fS;
		fU = fopen("data/universe.dat", "rb");
		fG = fopen("data/galaxyInfo.dat", "rb");
		fS = fopen("data/systemInfo.dat", "rb");

		for (int i = 0; i < 20; i++)
		{
			fread(&galaxyInfo[i][0], sizeof(int), 1, fG);
			fread(&galaxyInfo[i][1], sizeof(int), 1, fG);
			fread(&galaxyInfo[i][2], sizeof(int), 1, fG);
			fread(&galaxyInfo[i][3], sizeof(int), 1, fG);
			fread(&galaxyInfo[i][4], sizeof(int), 1, fG);
			fread(&galaxyInfo[i][5], sizeof(int), 1, fG);
			for (int j = 0; j < galaxyInfo[i][5]; j++)
			{
				fread(&systemInfo[i][j][0], sizeof(int), 1, fS);
				fread(&systemInfo[i][j][1], sizeof(int), 1, fS);
				fread(&systemInfo[i][j][2], sizeof(int), 1, fS);
				fread(&systemInfo[i][j][3], sizeof(int), 1, fS);
				for (int k = 0; k < systemInfo[i][j][0]; k++)
				{
					fread(&planetInfo[i][j][k][0], sizeof(int), 1, fU);
					fread(&planetInfo[i][j][k][1], sizeof(int), 1, fU);
					fread(&planetInfo[i][j][k][2], sizeof(int), 1, fU);
				}
			}
		}
		fclose(fU);
		fclose(fG);
		fclose(fS);
	}
	void createUniverse(int w, int h)
	{
		FILE *fU, *fG, *fS;
		fU = fopen("data/universe.dat", "wb");
		fG = fopen("data/galaxyInfo.dat", "wb");
		fS = fopen("data/systemInfo.dat", "wb");
		
		for (int i = 0; i < 20; i++)
		{
			galaxyInfo[i][0] = (i - int(i / 5) * 5)*int(w / 5) + 32 + rand() % (int(w / 5) - 64);
			galaxyInfo[i][1] = int(i / 5)*int(h / 4) + 32 + rand() % (int(h / 4) - 64);
			galaxyInfo[i][2] = rand() % 3;
			galaxyInfo[i][3] = rand() % 360;
			galaxyInfo[i][4] = 75 + rand() % 51;
			galaxyInfo[i][5] = 15 + rand() % 76;

			fwrite(&galaxyInfo[i][0], sizeof(int), 1, fG);
			fwrite(&galaxyInfo[i][1], sizeof(int), 1, fG);
			fwrite(&galaxyInfo[i][2], sizeof(int), 1, fG);
			fwrite(&galaxyInfo[i][3], sizeof(int), 1, fG);
			fwrite(&galaxyInfo[i][4], sizeof(int), 1, fG);
			fwrite(&galaxyInfo[i][5], sizeof(int), 1, fG);
			for (int j = 0; j < galaxyInfo[i][5]; j++)
			{
				systemInfo[i][j][0] = 1 + rand() % 10;
				systemInfo[i][j][1] = 44 + rand() % (w - 88);
				systemInfo[i][j][2] = 44 + rand() % (h - 88);
				systemInfo[i][j][3] = 1 + rand() % 5;

				fwrite(&systemInfo[i][j][0], sizeof(int), 1, fS);
				fwrite(&systemInfo[i][j][1], sizeof(int), 1, fS);
				fwrite(&systemInfo[i][j][2], sizeof(int), 1, fS);
				fwrite(&systemInfo[i][j][3], sizeof(int), 1, fS);
				for (int k = 0; k < systemInfo[i][j][0]; k++)
				{
					planetInfo[i][j][k][0] = (rand() % 360) - 180;
					planetInfo[i][j][k][1] = 1 + rand() % 6;
					planetInfo[i][j][k][2] = rand() % 2;
					if (planetInfo[i][j][k][2] == 0)
						planetInfo[i][j][k][2] = -1;

					fwrite(&planetInfo[i][j][k][0], sizeof(int), 1, fU);
					fwrite(&planetInfo[i][j][k][1], sizeof(int), 1, fU);
					fwrite(&planetInfo[i][j][k][2], sizeof(int), 1, fU);
				}
			}
		}
		fclose(fU);
		fclose(fG);
		fclose(fS);
	}
	void update(RenderWindow *window, Vector2f mouse, int galaxy, int starSystem)
	{
		int w = window->getSize().x, h = window->getSize().y;
		if (page)  drawUniverse(window, mouse, galaxy);
		else                   drawGalaxy(window, mouse, galaxy, starSystem);
		if (Back.getGlobalBounds().contains(mouse)){
			Back.setCharacterSize(24);
			Back.setPosition(39, (float)h - 45);
		}
		else{
			Back.setCharacterSize(22);
			Back.setPosition(42, (float)h - 44);
		}
		if (Page.getGlobalBounds().contains(mouse)){
			Page.setCharacterSize(24);
			Page.setPosition((float)w - 180, 12);
		}
		else{
			Page.setCharacterSize(18);
			Page.setPosition((float)w - 160, 15);
		}
		window->draw(Back);
		window->draw(Page);
	}
	void drawGalaxy(RenderWindow *window, Vector2f mouse, int galaxy, int starSystem)
	{
		for (int i = 0; i < galaxyInfo[galaxy][5]; i++)
		{
			CircleShape star(5);
			star.setOrigin(5, 5);
			switch (systemInfo[galaxy][i][3])
			{
			case 1: star.setFillColor(Color(128, 64, 0)); break;
			case 2: star.setFillColor(Color(128, 128, 255)); break;
			case 3: star.setFillColor(Color(255, 0, 0)); break;
			case 4: star.setFillColor(Color(255, 128, 0)); break;
			case 5: star.setFillColor(Color(255, 255, 255)); break;
			}
			star.setPosition((float)systemInfo[galaxy][i][1], (float)systemInfo[galaxy][i][2]);
			window->draw(star);
			if (star.getGlobalBounds().contains(mouse))
			{
				shape.setRadius(20);
				shape.setOrigin(20, 20);
				shape.setPosition((float)systemInfo[galaxy][i][1], (float)systemInfo[galaxy][i][2]);
				window->draw(shape);
			}
		}
		currentSystem.setPosition((float)systemInfo[galaxy][starSystem][1], (float)systemInfo[galaxy][starSystem][2]);
		window->draw(currentSystem);
	}
	void drawUniverse(RenderWindow *window, Vector2f mouse, int galaxy)
	{
		for (unsigned __int8 i = 0; i < 20; i++)
		{
			sg[galaxyInfo[i][2]].setPosition((float)galaxyInfo[i][0], (float)galaxyInfo[i][1]);
			sg[galaxyInfo[i][2]].setRotation((float)galaxyInfo[i][3]);
			sg[galaxyInfo[i][2]].setScale((float)galaxyInfo[i][4] / 100, (float)galaxyInfo[i][4] / 100);
			window->draw(sg[galaxyInfo[i][2]]);
			if (sg[galaxyInfo[i][2]].getGlobalBounds().contains(mouse))
			{
				shape.setRadius(32);
				shape.setOrigin(32, 32);
				shape.setPosition((float)galaxyInfo[i][0], (float)galaxyInfo[i][1]);
				window->draw(shape);
			}
		}
		currentGalaxy.setPosition((float)galaxyInfo[galaxy][0], (float)galaxyInfo[galaxy][1]);
		window->draw(currentGalaxy);
	}
	void changePage()
	{
		if (page)
			Page.setString("Show universe");
		else
			Page.setString("Show galaxy");
		page = !page;
	}
};