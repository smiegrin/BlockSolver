#ifndef MAININTERFACE_H
#define MAININTERFACE_H
#include <iostream>
#include <SFML\Graphics.hpp>

class MainInterface {
private:
	sf::RenderWindow *window;
	sf::RectangleShape *loadButton;

	void manageClick(int, int);
public:
	MainInterface();
	void run();
};
#endif