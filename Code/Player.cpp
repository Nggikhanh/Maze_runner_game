#pragma once
#include <chrono>
#include <thread>
#include "Player.h"



using namespace sf;
using namespace std;
using namespace std::this_thread;
using namespace std::chrono;

player::player()
{
	
}
void player::prep()
{
	x = thickness; y = thickness;
	offsetx = 0; offsety = 0;

	powerup = false;
	Spowerup.setRadius(area/2+thickness); 
	Spowerup.setPointCount(3);
	Powerupx = (rand() % MSIZE) * OFFSET ;
	Powerupy = (rand() % MSIZE) * OFFSET+ thickness;
}


void player::towall()
{

	for (int i = 0; i <= offsety; i++)
	{
		UDtowall = y;
		if (hWall[offsetx][offsety - i])
		{
			UDtowall = (i) * (area + thickness);
			break;
		}
	}

			
	for (int i = 0; i <= MSIZE; i++) {
		RDtowall = 1000 - x;

		if (vWall[offsetx + i][offsety])
		{
			RDtowall = (i) * (area + thickness);
			break;
		}
	}
	for (int i = 0; i <= MSIZE; i++)
	{
		DDtowall = 1000 - y;
		if (hWall[offsetx][offsety + i])
			{
			DDtowall = (i) * (area + thickness);
			break;
			}
	}
				
		for (int i = 0; i <= offsetx; i++)
			if (vWall[offsetx-i][offsety])
			{
				LDtowall = (i) * (area + thickness);
				break;
			}
			else
				LDtowall = x;
			
	
	
}

void player::powerupM()
{
	if (offsetx == Powerupx/OFFSET&&offsety==(Powerupy-thickness)/OFFSET)
		powerup = true;
}

void player::draw(RenderWindow* window)
{
	
	pl1.setFillColor(Color::Cyan);
	pl1.setSize(sf::Vector2f(size, size));
	pl1.setPosition(x, y);
	Spowerup.setPosition(Powerupx, Powerupy);
	Spowerup.setFillColor(Color::Red);

	
	if (!powerup)
		window->draw(Spowerup);
	window->draw(pl1);  
	bullet.setFillColor(sf::Color(255, 255, 255));

	while (shooting && side[0])
	{
		bullet.setSize(sf::Vector2f(area/5, UDtowall));
		bullet.setPosition(x + area/4, y - UDtowall);
		window->draw(bullet);
		shooting = false;

		//powerup
		if (powerup)
		{		
			int yposition = offsety - UDtowall / (area+thickness);
			hWall[offsetx][yposition] = false;
		}
		
		sleep_for(nanoseconds(DELAY));
	}
	while (shooting && side[1])
	{
		bullet.setSize(sf::Vector2f(RDtowall-area, area / 5));
		bullet.setPosition(x + area, y +  area /4);
		window->draw(bullet);
		shooting = false;

		//powerup
		if (powerup)
		{
			int xposition = offsetx + RDtowall / (area + thickness);
			vWall[xposition][offsety] = false;
		}
		sleep_for(nanoseconds(DELAY));
	}
	while (shooting && side[2])
	{
		bullet.setSize(sf::Vector2f(area / 5, DDtowall-area));
		bullet.setPosition(x + area /4, y + area);
		window->draw(bullet);
		shooting = false;

		//powerup
		if (powerup)
		{
			int yposition = offsety + DDtowall / (area + thickness);
			hWall[offsetx][yposition] = false;
		}

		sleep_for(nanoseconds(DELAY));
	}
	while (shooting && side[3])
	{
		bullet.setSize(sf::Vector2f(LDtowall, area / 5));
		bullet.setPosition(x-LDtowall, y + area /4);
		window->draw(bullet);
		shooting = false;

		//powerup
		if (powerup)
		{
			int xposition = offsetx - LDtowall / (area + thickness);
			vWall[xposition][offsety] = false;
		}
		sleep_for(nanoseconds(DELAY));
	}
}
void player::collision() 
{
	
	if ((offsetx >= MSIZE || offsety >= MSIZE )&& (pl1.getPosition().x < 1000 - 2*OFFSET && pl1.getPosition().y < 1000 - 2 * OFFSET && offsetx > 1 && offsety > 1))
	{
		for (int i = 0; i < 4; i++)
		{
			movable[i] = true;
		}
		if (offsetx == MSIZE || offsetx < 1)
		{
			movable[3] = false;
		}
		if (offsety == MSIZE || offsety < 1)
		{
			movable[0] = false;
		}
	}
	
	
	
		if (!hWall[offsetx][offsety] && offsety >=1)
			movable[0] = true;
		if (!vWall[offsetx + 1][offsety] && pl1.getPosition().x < 1000 - 2 * OFFSET)
			movable[1] = true;
		if (!hWall[offsetx][offsety + 1] && pl1.getPosition().y < 1000 - 2 * OFFSET)
			movable[2] = true;
		if (!vWall[offsetx][offsety] && offsetx >= 1)
			movable[3] = true;
		

}
void player::handleMove(RenderWindow* window)
{

	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		window->close();

	}
	if (Keyboard::isKeyPressed(Keyboard::W) && movable[0])
	{
		goingup = true;
		for (int i = 0; i < 4; i++)
		{
			side[i] = false;
		}
		for (int i = 0; i < 4; i++)
		{
			movable[i] = false;
		}
		side[0] = true;
	}
	if (Keyboard::isKeyPressed(Keyboard::S) && movable[2])
	{
		goingdown = true;
		for (int i = 0; i < 4; i++)
		{
			side[i] = false;
		}
		for (int i = 0; i < 4; i++)
		{
			movable[i] = false;
		}
		side[2] = true;
	}
	if (Keyboard::isKeyPressed(Keyboard::D) && movable[1])
	{
		goingR = true;
		for (int i = 0; i < 4; i++)
		{
			side[i] = false;
		}
		for (int i = 0; i < 4; i++)
		{
			movable[i] = false;
		}
		side[1] = true;
	}
	if (Keyboard::isKeyPressed(Keyboard::A) && movable[3])
	{
		goingL = true;
		for (int i = 0; i < 4; i++)
		{
			side[i] = false;
		}
		for (int i = 0; i < 4; i++)
		{
			movable[i] = false;
		}
		side[3] = true;
	}

	if (Keyboard::isKeyPressed(Keyboard::Space) && x > 0)
	{
		shooting = true;
	}
}
void player::moving()
{
	while (goingdown)
	{
		x = pl1.getPosition().x; y = pl1.getPosition().y + OFFSET;
		offsety++;
		goingdown = false;
		sleep_for(nanoseconds(DELAY*2));

	}
	while (goingup)
	{
		x = pl1.getPosition().x; y = pl1.getPosition().y - OFFSET;
		offsety--;
		goingup = false;
		sleep_for(nanoseconds(DELAY*2));

	}
	while (goingR)
	{
		x = pl1.getPosition().x + OFFSET; y = pl1.getPosition().y;
		offsetx++;
		goingR = false;
		sleep_for(nanoseconds(DELAY*2));


	}
	while (goingL)
	{
		x = pl1.getPosition().x - OFFSET; y = pl1.getPosition().y;
		offsetx--;
		goingL = false;
		sleep_for(nanoseconds(DELAY*2));


	}
	
}