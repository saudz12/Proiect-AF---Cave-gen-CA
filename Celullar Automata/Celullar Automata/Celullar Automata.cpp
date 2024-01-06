#include "Header.h"

int main()
{
	//40 80 45 5 
	int width, height, noise;
	unsigned int generations;
	std::cout << "Please imput the HEIGHT, WIDTH, NOISE and NUMBER OF GENERATIONS: ";
	std::cin >> height >> width >> noise >> generations;
	cellularAutomata(height, width, noise, generations);
	
	//ShellExecuteA(NULL, "open", "file:///C:/Users/Dell/Desktop/cave%20generation%20p5.js/index.html", NULL, NULL, SW_SHOWNORMAL);

	return 0;
}
