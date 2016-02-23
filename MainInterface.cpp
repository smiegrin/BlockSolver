#include "MainInterface.h"
#include "Block.h"
#include "FileManager.h"

MainInterface::MainInterface() {
	window = new sf::RenderWindow(sf::VideoMode(800,500), "Block Solver", sf::Style::Titlebar | sf::Style::Close);
	shape1 = new sf::CircleShape(100.f);
	shape1->setFillColor(sf::Color::Green);
}

void MainInterface::manageClick(int x, int y) {
	Block *block = 0;
	if (x < 200 && y < 200) block = FileManager::loadBlock();
	if (block != 0) std::cout << block->getDepth() << " " << block->getHeight() << " " << block->getDepth() << std::endl;
}

void MainInterface::run() {
	while (window->isOpen()) {
		sf::Event event;
		while (window->pollEvent(event)) {
			if (event.type == sf::Event::Closed) window->close();
			if (event.type == sf::Event::MouseButtonPressed) manageClick(event.mouseButton.x, event.mouseButton.y);
		}

		window->clear();
		window->draw(*shape1);
		window->display();
	}
}