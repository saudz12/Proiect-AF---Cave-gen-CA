#include "Header.h" 

//Get the number of walls in the 3x3 space surrounding a cell

int getNeigbours(const cave& myCave, const int& x, const int& y, const int& height, const int& width) {
	int adjWalls = 0;
	for(int i = x-1; i <= x+1; i++){
		for (int j = y - 1; j <= y + 1; j++) {
			if (i < 0 || i >= height || j < 0 || j >= width) continue;
			if (myCave[i][j] == true) adjWalls++;
		}
	}
	return adjWalls;
}

//Will use to get rid of unconnected caves

int get2x2Neigbours(const cave& myCave, const int& x, const int& y, const int& height, const int& width) {
	int adjWalls = 0;
	for (int i = x - 2; i <= x + 2; i++) {;
		for (int j = y - 2; j <= y + 2; j++) {
			if (i < 0 || i >= height || j < 0 || j >= width) {
				adjWalls++;
				continue;
			}
			if (myCave[i][j] == true) adjWalls++;
		}
	}
	return adjWalls;
}

//Get new type of cell after the rulsed of cellular aotomata

bool newTtpe(cave& myCave, const int& x, const int& y, const int& height, const int& width) {
	int adj = getNeigbours(myCave, x, y, height, width);
	int fix = get2x2Neigbours(myCave, x, y, height, width);
	bool currState = myCave[x][y];
	if (x == 0 || y == 0 || x == height - 1 || y == width - 1) return true;
	if (currState == true && adj < 5) return false;
	if (currState == false && adj >= 5) return true;
	return currState;
	
}

bool fineType(cave& myCave, const int& x, const int& y, const int& height, const int& width) {
	int adj = getNeigbours(myCave, x, y, height, width);
	int fix = get2x2Neigbours(myCave, x, y, height, width);
	bool currState = myCave[x][y];
	if (x == 0 || y == 0 || x == height - 1 || y == width - 1) return true;
	return adj >= 5 || fix <= 2;
}

//Update cave by the rules implied by cellular automata 

void generateCave(cave& myCave, const int& height, const int& width) {
	cave newCave;
	initMap(newCave, height, width);
	for (int h = 0; h < height; h++)
		for (int w = 0; w < width; w++){
			newCave[h][w] = newTtpe(myCave, h, w, height, width);
		}
	copyCave(newCave, myCave, height, width);
	return;
}

//Removes isolated walls

void fineTuning(cave& myCave, const int& height, const int& width) {
	cave newCave;
	initMap(newCave, height, width);
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++) {
			newCave[i][j] = fineType(myCave, i, j, height, width);
		}
	copyCave(newCave, myCave, height, width);
	return;
}

//initial fill of map; 'noise' value means what % of the 'cave' is filled with 'walls'. If random value is smaller than the noise value, then the tile becomes a wall(1). Otherwise it stays as an ampty space(0)

void fillMap(cave& myCave, const int& height, const int& width, const unsigned int& noise) {
	srand((unsigned)time(NULL));
	for(int h = 0; h < height; h++){
		for (int w = 0; w < width; w++) {
			myCave[h][w] = false;
			if (h == 0 || h == height - 1 || w == 0 || w == width - 1) myCave[h][w] = true;
			if (rand() % 100 < noise) myCave[h][w] = true;
		}
	}
	return;
}

//initializing an obiect of 'cave' type

void initMap(cave& myCave, const int& height, const int& width) {
	myCave.resize(height);
	for (int i = 0; i < height; i++) 
		myCave[i].resize(width);
	return;
}

//returns a cave that contains the point passed in the function

std::queue<point> getFLoodedCave(const cave& myCave, cave& auxCave, int i, int j, const int& height, const int& width){
	std::queue<point> toBeFlooded;
	std::queue<point> isFlooded;
	int x, y;
	toBeFlooded.push(point{i, j});
	while (!toBeFlooded.empty()) {
		x = toBeFlooded.front().x;
		y = toBeFlooded.front().y;
		if (x - 1 >= 0 && auxCave[x - 1][y] == false && myCave[x - 1][y] == false) {
			auxCave[x - 1][y] = true;
			toBeFlooded.push(point{x-1, y});
		}
		if (y - 1 >= 0 && auxCave[x][y - 1] == false && myCave[x][y - 1] == false) {
			auxCave[x][y - 1] = true;
			toBeFlooded.push(point{x, y-1});
		}
		if (y + 1 < width && auxCave[x][y + 1] == false && myCave[x][y + 1] == false) {
			auxCave[x][y + 1] = true;
			toBeFlooded.push(point{x, y+1});
		}
		if (x + 1 < height && auxCave[x + 1][y] == false && myCave[x + 1][y] == false) {
			auxCave[x + 1][y] = true;
			toBeFlooded.push(point{x+1, y});
		}
		auxCave[x][y] = true;
		isFlooded.push(point{x, y});
		toBeFlooded.pop();
	}
	/*std::queue<point> q1 = isFlooded; <-- uncomment to check if the queue is built properly
	while (!q1.empty()) {
		std::cout << "(" << q1.front().x << "," << q1.front().y << ") ";
		q1.pop();
	}
	std::cout << "\n///////////////////////////\n";*/
	return isFlooded;
}

//Find largest cavern

std::queue<point> getMaxCavern(const cave& myCave, const int& height, const int& width) {
	cave auxCave;
	initMap(auxCave, height, width);
	int maxSize = 0, size = 0;
	std::queue<point> maxCave;
	std::queue<point> currCave;
	copyCave(myCave, auxCave, height, width);
	for(int i = 1; i < height - 1; i++)
		for(int j = 1; j < width - 1; j++)
			if (myCave[i][j] == false && auxCave[i][j] == false) {
				currCave = getFLoodedCave(myCave, auxCave, i, j, height, width);
				size = currCave.size();
				if (size > maxSize) {
					maxSize = size;
					maxCave = currCave;
				}
			}
	return maxCave;
}

//Fill all the caverns besides the largest one

void floodFilling(cave& myCave, const int& height, const int& width) {
	std::queue<point> maxCave = getMaxCavern(myCave, height, width);
	std::cout << maxCave.size() << '\n';
	/*if (maxCave.size() < width * height / 3) {
		return false;
	}*/
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			myCave[i][j] = true;
	int x, y;
	while (!maxCave.empty()) {
		x = maxCave.front().x;
		y = maxCave.front().y;
		myCave[x][y] = false;
		maxCave.pop();
	}

	return;
}

//programu in sine

void cellularAutomata(int height, int width, unsigned int noise, int generations) {
	cave myCave;

	initMap(myCave, height, width);
	fillMap(myCave, height, width, noise % 100);


	std::cout << "INITIAL CAVE\n";
	getMap(myCave, height, width);
	system("pause");
	int k;
	for (k = 0; k < generations; k++) {
		fineTuning(myCave, height, width);
		system("cls");
		std::cout << "ITERATION " << k+1 << '\n';
		getMap(myCave, height, width);
		system("pause");
	}
	for(k = 0; k < generations; k++)
		generateCave(myCave, height, width);
	floodFilling(myCave, height, width);

	system("cls");
	getMap(myCave, height, width);

	return;
}

//prints the 'cave' on screen(console)

void getMap(const cave& myCave, const int& height, const int& width) {
	for (int h = 0; h < height; h++) {
		for (int w = 0; w < width; w++) {
			if (myCave[h][w]) std::cout << '#';
			else std::cout << '.';
		}
		std::cout << '\n';
	}
	return;
}

//copy cave 1 to cave 2

void copyCave(const cave& cave1, cave& cave2, const int& height, const int& width) {
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			cave2[i][j] = cave1[i][j];
	return;
}