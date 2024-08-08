#include"Maze.h"

using namespace std;
using namespace sf;

void Maze::prep() {
	for (int i = 0; i < MSIZE; i++) {
		for (int j = 0; j < MSIZE; j++) {
			A[i][j] = notVisited;
		}
	}
	for (int i = 0; i < MSIZE+1; i++) {
		for (int j = 0; j < MSIZE+1; j++) {

			vWall[i][j] = true;
			hWall[i][j] = true;
		}
	}
	hwall.setSize(Vector2f(area, thickness));
	vwall.setSize(Vector2f(thickness, area));
	end.setSize(Vector2f(area, area));
	end.setFillColor(Color::Green);
	end.setPosition(Vector2f((MSIZE-1) * area+ MSIZE * thickness, (MSIZE - 1) * area + MSIZE * thickness));
}
void Maze::logic() {
	adj.push(make_pair(0, 0));
	A[0][0] = isVisited;

	visited = 1;
	while (visited < MSIZE * MSIZE) {

		// up neighbour
		if (adj.top().second > 0 && A[adj.top().first][adj.top().second - 1] == notVisited)
			neighbours.push_back(1);
		// right neighbour
		if (adj.top().first < MSIZE - 1 && A[adj.top().first + 1][adj.top().second] == notVisited)
			neighbours.push_back(2);
		// down neighbour
		if (adj.top().second < MSIZE - 1 && A[adj.top().first][adj.top().second + 1] == notVisited)
			neighbours.push_back(3);
		// left neighbour
		if (adj.top().first > 0 && A[adj.top().first - 1][adj.top().second] == notVisited)
			neighbours.push_back(4);

		// Are there any neighbours available?
		if (!neighbours.empty()) {
			int next_cell_dir = neighbours[rand() % neighbours.size()];
			neighbours.clear();
			switch (next_cell_dir)
			{
			case 1: // up
				A[adj.top().first][adj.top().second - 1] = isVisited;
				A[adj.top().first][adj.top().second] = isVisited;
				hWall[adj.top().first][adj.top().second] = false;
				adj.push(make_pair((adj.top().first), (adj.top().second - 1)));

				break;

			case 2: // right
				A[adj.top().first + 1][adj.top().second] = isVisited;
				A[adj.top().first][adj.top().second] = isVisited;
				vWall[adj.top().first + 1][adj.top().second] = false;
				adj.push(make_pair((adj.top().first + 1), (adj.top().second)));


				break;


			case 3: // down
				A[adj.top().first][adj.top().second + 1] = isVisited;
				A[adj.top().first][adj.top().second] = isVisited;
				hWall[adj.top().first][adj.top().second + 1] = false;
				adj.push(make_pair((adj.top().first), (adj.top().second + 1)));


				break;


			case 4: // left
				A[adj.top().first - 1][adj.top().second] = isVisited;
				A[adj.top().first][adj.top().second] = isVisited;
				vWall[adj.top().first][adj.top().second] = false;
				adj.push(make_pair((adj.top().first - 1), (adj.top().second)));



				break;
			default:
				break;
			}

			visited++;
		}
		else {
			adj.pop();
		}
	}
}

void Maze::draw(RenderWindow& window)
{
	for (int i = 0; i <= MSIZE; ++i) {
		for (int j = 0; j <= MSIZE; ++j) {
			if (j == MSIZE)
			{
				vwall.setPosition(i * (area + thickness), j * area + (j + 1) * (thickness));

			}

			if (i == MSIZE)
			{
				hwall.setPosition(i * area + (i + 1) * (thickness), j * (thickness + area));
			}

			if (i != MSIZE) {
				hwall.setPosition(i * area + (i + 1) * (thickness), j * (thickness + area));
				if (hWall[i][j] == false) {
					hwall.setFillColor(Color::Black);
					window.draw(hwall);
				}
				else {
					hwall.setFillColor(Color::White);
					window.draw(hwall);
				}
			}
			if (j != MSIZE) {
				vwall.setPosition(i * (area + thickness), j * area + (j + 1) * (thickness));
				if (vWall[i][j] == false) {
					vwall.setFillColor(Color::Black);
					window.draw(vwall);
				}
				else {
					vwall.setFillColor(Color::White);
					window.draw(vwall);
				}
			}

		}
	}
	window.draw(end);
}