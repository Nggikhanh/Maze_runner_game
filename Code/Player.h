#ifndef _PLAYER_
#define _PLAYER_
#include <SFML/Graphics.hpp>
#include"Constants.h"

using namespace sf;
extern bool vWall[MSIZE +1][MSIZE +1];
extern bool hWall[MSIZE +1][MSIZE +1];

class player
{
public:
	int size = area;
	bool movable[4] = { false,false,false,false };
	
	int x ;
	int y ;
	float UDtowall,RDtowall, DDtowall, LDtowall;
	const float OFFSET = area + thickness;
	int offsetx,offsety;
	RectangleShape pl1,bullet;
	CircleShape Spowerup;
	int Powerupx;
	int Powerupy;

	bool powerup, goingdown = false, goingup = false, goingR = false, goingL = false, shooting = false;
	bool side[4] = { 0,0,0,0 };

	


	
	player();
	void draw(RenderWindow* window);
	void handleMove(RenderWindow* window);
	void moving();
	void towall();
	void collision();
	void powerupM();
	void prep();
	
};


#endif