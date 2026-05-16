#include <SFML/Graphics.hpp>
using namespace sf;
class Planets{
public:
	Sprite *ps, ss;
	Texture *pt, *st;
	Planets()
	{
		st = new Texture; 
	}
	void setNumberOfPlanets(int n, int** type)
	{
		Image *pi, si;

		pi = new Image[n];
		pt = new Texture[n];
		ps = new Sprite[n];
		si.loadFromFile("images/Star1.png");
		si.createMaskFromColor(Color(255, 255, 255));
		st->loadFromImage(si);
		ss.setTexture(*st);
		ss.setOrigin((float)st->getSize().x / 2, (float)st->getSize().y / 2);
		ss.setPosition(0, 0);

		for (int i = 0; i < n; i++)
		{
			std::ostringstream s;
			s << "images/Planet" << type[i][1] << ".png";
			pi[i].loadFromFile(s.str());
			pi[i].createMaskFromColor(Color(255, 255, 255));
			pt[i].loadFromImage(pi[i]);
			ps[i].setTexture(pt[i]);
			ps[i].setOrigin((float)ps[i].getTextureRect().width / 2, (float)ps[i].getTextureRect().height / 2);
		}
	}
};
