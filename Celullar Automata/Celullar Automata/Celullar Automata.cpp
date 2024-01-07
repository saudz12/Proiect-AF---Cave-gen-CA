#include "Header.h"

int main()
{
	int width, height, noise;
	std::string mode;
	unsigned int generations;
	std::cout << "Please imput the HEIGHT, WIDTH, NOISE(0-100), NUMBER OF GENERATIONS(>= 0), and mode(type 'debug' for stages or anything else for normal run:\n ";
	std::cin >> height >> width >> noise >> generations >> mode;
	if (noise > 100 || noise < 0 || generations < 0) {
		std::cout << "invalid input";
		return -1;
	}
	if (mode == "debug")
		cellularAutomataDebug(height, width, noise, generations);
	else
		cellularAutomata(height, width, noise, generations);
	return 0;
}
