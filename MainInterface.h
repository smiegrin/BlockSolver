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
	static const int SOLVED = 3;
	static const int WAITING = 4;
	int status;

	sf::RenderWindow *window;

	sf::RectangleShape *loadButton;
	sf::RectangleShape *testBlockButton;
	sf::RectangleShape *stepButton;
	sf::RectangleShape *playPauseButton;

	sf::Font font;

	Solver* solver;

	void manageClick(int, int);
public:
	MainInterface();
	void run();
};
#endif