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

//5x5

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

bool newTtpe(cave& myCave, const int& x, const int& y, const int& height, const int& width) {
	int adj = getNeigbours(myCave, x, y, height, width);
	int fix = get2x2Neigbours(myCave, x, y, height, width);
	bool currState = myCave[x][y];
	if (x == 0 || y == 0 || x == height - 1 || y == width - 1) return true;
	if (currState == true && adj < 5) return false;
	if (currState == false && adj >= 5) return true;
	return currState;
	
}

void cleaning(cave& myCave, const int& height, const int& width) {
	cave newCave;
	initMap(newCave, height, width);
	for (int h = 0; h < height; h++)
		for (int w = 0; w < width; w++) {
			newCave[h][w] = newTtpe(myCave, h, w, height, width);
		}
	copyCave(newCave, myCave, height, width);
	return;
}


bool fineType(cave& myCave, const int& x, const int& y, const int& height, const int& width) {
	int adj = getNeigbours(myCave, x, y, height, width);
	int fix = get2x2Neigbours(myCave, x, y, height, width);
	bool currState = myCave[x][y];
	if (x == 0 || y == 0 || x == height - 1 || y == width - 1) return true;
	return adj >= 5 || fix <= 2;
}

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

void initMap(cave& myCave, const int& height, const int& width) {
	myCave.resize(height);
	for (int i = 0; i < height; i++) 
		myCave[i].resize(width);
	return;
}

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

void horizontalBlanking(cave& myCave, const int& height, const int& width) {
	if (!(height >= 50 && width >= 100 || height >= 100 && width >= 50))
		return;
	for (int i = 25; i <= height - 25; i += 25)
		for (int j = 5; j <= width - 5; j++)
			myCave[i][j] = myCave[i - 1][j] = myCave[i + 1][j] = false;
}

//programu in sine

void cellularAutomata(int height, int width, unsigned int noise, int generations) {
	cave myCave;

	initMap(myCave, height, width);
	fillMap(myCave, height, width, noise % 100);
	horizontalBlanking(myCave, height, width);
	int k;
	for (k = 0; k < generations; k++) {
		fineTuning(myCave, height, width);
	}
	for (k = 0; k < generations; k++) {
		cleaning(myCave, height, width);
	}
	if(generations > 0)
		floodFilling(myCave, height, width);

	system("cls");
	getMap(myCave, height, width);
	configBlueprint(myCave, height, width, noise, generations);
	afisareFis(myCave, height, width);
	system("pause");
	return;
}

//debug

void cellularAutomataDebug(int height, int width, unsigned int noise, int generations) {
	cave myCave;

	initMap(myCave, height, width);
	fillMap(myCave, height, width, noise % 100);
	horizontalBlanking(myCave, height, width);
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
	for (k = 0; k < generations; k++) {
		cleaning(myCave, height, width);
		system("cls");
		std::cout << "ITERATION " << generations + k << '\n';
		getMap(myCave, height, width);
		system("pause");
	}
	if(generations > 0)
		floodFilling(myCave, height, width);

	system("cls");
	getMap(myCave, height, width);
	configBlueprint(myCave, height, width, noise, generations);
	afisareFis(myCave, height, width);
	system("pause");
}

//unused

void finalCleaning(cave& myCave, const int& height, const int& width) {
	cave auxCave;
	initMap(auxCave, height, width);
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++) {
			if (i == 0 || j == 0 || i == height - 1 || j == width - 1) {
				auxCave[i][j] = true;
				continue;
			}
			if (myCave[i][j] == true && getNeigbours(myCave, i, j, height, width) <= 2)
				auxCave[i][j] = false;
			else
				auxCave[i][j] = myCave[i][j];
		}
	copyCave(auxCave, myCave, height, width);
}

//blueprint 

void configBlueprint(const cave& myCave, const int& height, const int& width, const unsigned int& noise, const int& generations) {
	std::ofstream fout("blueprint.txt");
	fout << height << " " << width << " " << noise << " " << generations;
	for (int h = 0; h < height; h++) {
		fout << '\n';
		for (int w = 0; w < width; w++)
			fout << myCave[h][w];
	}
	fout.close();
}

//afisare in fisier

void afisareFis(const cave& myCave, const int& height, const int& width) {
	std::ofstream fout("afis.txt");
	for (int h = 0; h < height; h++) {
		for (int w = 0; w < width; w++)
			if (myCave[h][w] == true)
				fout << "#";
			else
				fout << ".";
		fout << '\n';
	}
	fout.close();
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