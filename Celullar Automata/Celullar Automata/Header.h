#include <iostream>
#include <fstream>
#include <random>
#include <fstream>
#include <time.h>
#include <stdlib.h>
#include <vector>
#include <stdio.h>
#include <time.h>
#include <queue>
#include <stack>

//kept as bool to use less memory(bool uses 1 byte, while int has 4), and used std::vector to not bother with memory management
typedef std::vector<std::vector<bool>> cave;

struct point { 
	int x = 0; 
	int y = 0; 
	point operator=(const point& p2) {
		x = p2.x;
		y = p2.y;
		return *this;
	}
};

int getNeigbours(const cave& myCave, const int& x, const int& y, const int& height, const int& width);

int get2x2Neigbours(const cave& myCave, const int& x, const int& y, const int& height, const int& width);

bool newTtpe(cave& myCave, const int& x, const int& y, const int& height, const int& width);

void fineTuning(cave& myCave, const int& height, const int& width);

void cleaning(cave& myCave, const int& height, const int& width);

void fillMap(cave& myCave, const int& height, const int& width, const unsigned int& noise);

void initMap(cave& myCave, const int& height, const int& width);

std::queue<point> getFLoodedCave(const cave& myCave, cave& auxCave, int x, int y, const int& height, const int& width);

std::queue<point> getMaxCavern(const cave& myCave, const int& height, const int& width);

void floodFilling(cave& myCave, const int& height, const int& width);

void cellularAutomata(int height, int width, unsigned int noise, int generations);

void configBlueprint(const cave& myCave, const int& height, const int& width, const unsigned int& noise, const int& generations);

void getMap(const cave& myCave, const int& height, const int& width);

void copyCave(const cave& cave1, cave& cave2, const int& height, const int& width);