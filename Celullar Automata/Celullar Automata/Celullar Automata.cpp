#include "Header.h"

int main()
{
	//40 80 45 5 
	int width, height, noise;
	unsigned int generations;
	std::cout << "Please imput the HEIGHT, WIDTH, NOISE and NUMBER OF GENERATIONS: ";
	std::cin >> height >> width >> noise >> generations;
	cellularAutomata(height, width, noise, generations);
	return 0;
}
