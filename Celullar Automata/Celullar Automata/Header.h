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

void generateCave(cave& myCave, const int& height, const int& width);

void fillMap(cave& myCave, const int& height, const int& width, const unsigned int& noise);

void initMap(cave& myCave, const int& height, const int& width);

std::queue<point> getFLoodedCave(const cave& myCave, cave& auxCave, int x, int y, const int& height, const int& width);

std::queue<point> getMaxCavern(const cave& myCave, const int& height, const int& width);

void floodFilling(cave& myCave, const int& height, const int& width);

void cellularAutomata(int height, int width, unsigned int noise, int generations);

void getMap(const cave& myCave, const int& height, const int& width);

void copyCave(const cave& cave1, cave& cave2, const int& height, const int& width);

//! Steps:
//! Generates a cave of respective WIDTH and HEIGHT, filled with %NOISE walls which are represented by 1s
//! By the rule of cellular automata, if a wall has less than 4 walls as neighbours it becomes a space, 
//! and if a space has moppre than 5 walls it becomes a wall. If neither, it stays the same.
//! This procces is repeated GENERATIONS times to smoothen the cave to our desire.
//! Spaces that are too filled or too empty shall be filled with blocks(check fuull empty/filled 3x3 or almost empty/filled 4x4).
//! For fixing isolated caves, FLOOD FILLING will be used to get rid of all the caves besides the biggest one.
//! If the largest cave is ont of a desired size(recommended to be in between [noise-5, noise+5].
//! For 3D, there is not much change just it is a cube. Same rules apply , but with slightly different values.
//! For rendering the tri-dimensional cave we will use UNITY(pass a binary file containing the blueprint of the cave or something like that) 
//! or we will make a renderer. - optional
//! Furthermore, for the clarity of code move everything to a class - optional