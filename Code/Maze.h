#pragma once
#ifndef _MAZE_
#define _MAZE_
#include<stack>
#include<random>
#include<string>
#include <SFML/Graphics.hpp>
#include"Constants.h"

using namespace std;
using namespace sf;


extern bool vWall[MSIZE+1][MSIZE +1];
extern bool hWall[MSIZE+1][MSIZE +1];

class Maze
{
public:
	
	//handle logic variables
	int visited = 0;
	bool notVisited = false;
	bool isVisited = true;
	stack<pair<int, int>> adj;
	vector<int> neighbours;
	bool A[MSIZE][MSIZE];

	//walls drawing variables

	RectangleShape hwall;
	RectangleShape vwall;
	RectangleShape end;

	Maze() {};
	void prep();
	void logic();
	void draw(RenderWindow& window);
};
#endif