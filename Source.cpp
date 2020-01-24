#include <SFML/Graphics.hpp>
#include "DetectCollision.h"
using namespace sf;
int main()
{
	RenderWindow window(VideoMode(640, 640), "Perfect Collision Test", Style::Close);
	window.setFramerateLimit(120);

	//> Create 1st object as a Sprite
	Texture t1;
	t1.loadFromFile("Red.png");
	Sprite s1;
	s1.setTexture(t1);
	Image i1;
	i1.loadFromFile("Red.png");

	//> Then move it
	s1.setPosition(608.0f ,0.0f);

	//> Create 2nd object as a Sprite
	Texture t2;
	t2.loadFromFile("White.png");
	Sprite s2;
	s2.setTexture(t2);
	Image i2;
	i2.loadFromFile("White.png");

	//> Then move it
	s2.setPosition(0.0f, 608.0f);

	//> Create a string to display "isCollided: TRUE" or "isCollided: FALSE"
	Font displayFont;
	displayFont.loadFromFile("Helvetica.ttf");
	Text note;
	note.setFont(displayFont);
	note.setCharacterSize(24);
	note.setFillColor(Color(255,170,29));
	note.setStyle(Text::Regular);

	while (window.isOpen())
	{
		Event eve;
		while (window.pollEvent(eve))
		{
			if (eve.type == Event::Closed) window.close();
		}

		//> Move 1st object by WASD
		if (Keyboard::isKeyPressed(Keyboard::W))
		{
			s1.move(0.0f, -0.5f);
		}

		if (Keyboard::isKeyPressed(Keyboard::S))
		{
			s1.move(0.0f, +0.5f);
		}

		if (Keyboard::isKeyPressed(Keyboard::A))
		{
			s1.move(-0.5f, +0.0f);
		}

		if (Keyboard::isKeyPressed(Keyboard::D))
		{
			s1.move(+0.5f, +0.0f);
		}

		//> Move 2nd object by IJKL
		if (Keyboard::isKeyPressed(Keyboard::I))
		{
			s2.move(0.0f, -0.5f);
		}

		if (Keyboard::isKeyPressed(Keyboard::K))
		{
			s2.move(0.0f, +0.5f);
		}

		if (Keyboard::isKeyPressed(Keyboard::J))
		{
			s2.move(-0.5f, +0.0f);
		}

		if (Keyboard::isKeyPressed(Keyboard::L))
		{
			s2.move(+0.5f, +0.0f);
		}

		if (PixelPerfectCollision(s1, s2, i1, i2)) note.setString("Use WASD to move the RED object\nUse IJKL to move the WHITE object\nisCollided: TRUE");
		else note.setString("Use WASD to move the RED object\nUse IJKL to move the WHITE object\nisCollided: FALSE");

		window.clear(Color(44, 47, 51));
		window.draw(s1);
		window.draw(s2);
		window.draw(note);
		window.display();
	}

	return 0;
}