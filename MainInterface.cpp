#include "MainInterface.h"
#include "Block.h"
#include "FileManager.h"

MainInterface::MainInterface() {
	window = new sf::RenderWindow(sf::VideoMode(800,500), "Block Solver", sf::Style::Titlebar | sf::Style::Close);
	
	//make "Load" button
	loadButton = new sf::RectangleShape(sf::Vector2f(100,50));
	loadButton->setPosition(sf::Vector2f(450,300));
	loadButton->setFillColor(sf::Color::Green);
}

void MainInterface::manageClick(int x, int y) {
	Block *block = 0;
	
	if (x > loadButton->getPosition().x &&
		x < loadButton->getPosition().x + loadButton->getSize().x &&
		y > loadButton->getPosition().y &&
		y < loadButton->getPosition().y + loadButton->getSize().y) 
		block = FileManager::loadBlock();

	if (block != 0) block->printInfo();
}

void MainInterface::run() {
	while (window->isOpen()) {
		sf::Event event;
		while (window->pollEvent(event)) {
			if (event.type == sf::Event::Closed) window->close();
			if (event.type == sf::Event::MouseButtonPressed) manageClick(event.mouseButton.x, event.mouseButton.y);
		}

		window->clear();
		window->draw(*loadButton);
		window->display();
	}
}