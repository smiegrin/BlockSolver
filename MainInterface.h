#ifndef MAININTERFACE_H
#define MAININTERFACE_H
#include <iostream>
#include <SFML\Graphics.hpp>
#include "Solver.h"

class MainInterface {
private:
	static const int PAUSED = 0;
	static const int RUNNING = 1;
	static const int STEP = 2;
	static const int SOLVED = 4;
	static const int WAITING = 8;
	int status;
	int zoomSize;

	sf::RenderWindow *window;

	sf::RectangleShape *loadButton;
	sf::RectangleShape *testBlockButton;
	sf::RectangleShape *stepButton;
	sf::RectangleShape *playPauseButton;
	sf::RectangleShape *boardSpace;

	sf::Font font;

	Solver* solver;

	void manageClick(int, int);
public:
	MainInterface();
	void run();
};
#endif