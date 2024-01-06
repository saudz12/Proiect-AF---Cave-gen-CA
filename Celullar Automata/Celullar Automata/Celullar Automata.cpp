#include "Header.h"

int main()
{
	int width, height, noise;
	std::string mode;
	unsigned int generations;
	std::cout << "Please imput the HEIGHT, WIDTH, NOISE, NUMBER OF GENERATIONS, and mode(type 'debug' for stages or anything else for normal run:\n ";
	std::cin >> height >> width >> noise >> generations >> mode;
	if (mode == "debug")
		cellularAutomataDebug(height, width, noise, generations);
	else
		cellularAutomata(height, width, noise, generations);
	return 0;
}
