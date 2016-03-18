#include "MainInterface.h"
#include "Block.h"
#include "FileManager.h"

MainInterface::MainInterface() {
	window = new sf::RenderWindow(sf::VideoMode(800,500), "Block Solver", sf::Style::Titlebar | sf::Style::Close);
	
	//make "Load" button
	loadButton = new sf::RectangleShape(sf::Vector2f(100,50));
	loadButton->setPosition(sf::Vector2f(700,450));
	loadButton->setFillColor(sf::Color::Green);

	//make "Test Block" button
	testBlockButton = new sf::RectangleShape(sf::Vector2f(100,50));
	testBlockButton->setPosition(sf::Vector2f(600,450));
	testBlockButton->setFillColor(sf::Color::Color(127,127,127,255));
}

void MainInterface::manageClick(int x, int y) {
	Block *block = 0;
	
	if (x > testBlockButton->getPosition().x &&
		x < testBlockButton->getPosition().x + testBlockButton->getSize().x &&
		y > testBlockButton->getPosition().y &&
		y < testBlockButton->getPosition().y + testBlockButton->getSize().y)
	{
		Block* block = FileManager::loadBlock();
		do {
			block->printInfo();
			system("pause");
		} while (block->rotate() != 0);
	}

	if (block != 0) block->printInfo();
}

void MainInterface::run() {
	while (window->isOpen()) {
		sf::Event event;
		while (window->pollEvent(event)) {
			if (event.type == sf::Event::Closed) window->close();
			if (event.type == sf::Event::MouseButtonPressed) manageClick(event.mouseButton.x, event.mouseButton.y);
		}

		window->clear(sf::Color(63,63,63,255));
		window->draw(*loadButton);
		window->draw(*testBlockButton);
		window->display();
	}
}