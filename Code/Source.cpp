#include<SFML/Graphics.hpp>
#include<stack>
#include<iostream>
#include<random>
#include<string>
#include"Maze.h"
#include"Player.h"

using namespace std;
using namespace sf;


bool vWall[MSIZE +1][MSIZE +1];
bool hWall[MSIZE +1][MSIZE +1];


int main() {
	char start='N';
	cout << "The objective of the game is to reach the end point coloured green" << endl;
	cout << "Press 'W' to go up, 'D' to go right, 'S' to go down, 'A' to go left, 'Space' to shoot" << endl;
	cout << "The red triangle is a power up which alow you to shoot down walls" << endl << endl;
	cout << "You can change the setting of the game in Constants.h"<<endl;
	cout << "Press Y to start the game, N to quit"<<endl;
	cin >> start;

	if (start = 'Y')
	{
		

		srand(time(NULL));

		Maze maze;
		maze.prep();
		maze.logic();
		player player;
		player.prep();
		RenderWindow window(VideoMode(1000, 1000), "maze");
		while (window.isOpen()) {
			sf::Event event;
			while (window.pollEvent(event)) {
				if (event.type == Event::Closed) {
					window.close();
				}
			}

			player.collision();
			player.handleMove(&window);
			player.moving();
			player.towall();
			player.powerupM();
			if (player.x == (MSIZE - 1) * area + MSIZE * thickness && player.y == (MSIZE - 1) * area + MSIZE * thickness)//reach the end
			{
				player.prep();
				maze.prep();
				maze.logic();
			}
			
			window.clear();

			maze.draw(window);
			player.draw(&window);

			window.display();

		}
	}
	else 
		return 0;
	
}