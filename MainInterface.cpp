#include "MainInterface.h"
#include "Block.h"
#include "FileManager.h"

MainInterface::MainInterface() {
	window = new sf::RenderWindow(sf::VideoMode(800,500), "Block Solver", sf::Style::Titlebar | sf::Style::Close);
	status = WAITING;

	//make "Load" button
	loadButton = new sf::RectangleShape(sf::Vector2f(100,50));
	loadButton->setPosition(sf::Vector2f(700,450));
	loadButton->setFillColor(sf::Color::Color(0,255,0,255));

	//make "Test Block" button
	testBlockButton = new sf::RectangleShape(sf::Vector2f(100,50));
	testBlockButton->setPosition(sf::Vector2f(600,450));
	testBlockButton->setFillColor(sf::Color::Color(127,127,127,255));

	//make "Step" button
	stepButton = new sf::RectangleShape(sf::Vector2f(100,50));
	stepButton->setPosition(sf::Vector2f(500,450));
	stepButton->setFillColor(sf::Color::Color(255,255,0,255));

	//make "Play/Pause" button
	playPauseButton = new sf::RectangleShape(sf::Vector2f(100,50));
	playPauseButton->setPosition(sf::Vector2f(400,450));
	playPauseButton->setFillColor(sf::Color::Color(0,0,255,255));


}

void MainInterface::manageClick(int x, int y) {
	Block *block = 0;
	
	//test block
	if (x > testBlockButton->getPosition().x &&
		x < testBlockButton->getPosition().x + testBlockButton->getSize().x &&
		y > testBlockButton->getPosition().y &&
		y < testBlockButton->getPosition().y + testBlockButton->getSize().y)
	{
		Block* block = FileManager::loadBlock();
		if (block == NULL) return;
		do {
			block->printInfo();
			system("pause");
		} while (block->rotate() != 0);
	}

	//load puzzle
	if (x > loadButton->getPosition().x &&
		x < loadButton->getPosition().x + loadButton->getSize().x &&
		y > loadButton->getPosition().y &&
		y < loadButton->getPosition().y + loadButton->getSize().y)
	{
		if (status != RUNNING) solver = FileManager::loadPuzzle();
	}

	//step solver
	if (x > stepButton->getPosition().x &&
		x < stepButton->getPosition().x + stepButton->getSize().x &&
		y > stepButton->getPosition().y &&
		y < stepButton->getPosition().y + stepButton->getSize().y)
	{

	}

	//run/stop solver
	if (x > playPauseButton->getPosition().x &&
		x < playPauseButton->getPosition().x + playPauseButton->getSize().x &&
		y > playPauseButton->getPosition().y &&
		y < playPauseButton->getPosition().y + playPauseButton->getSize().y)
	{

	}
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
		window->draw(*stepButton);
		window->draw(*playPauseButton);
		window->display();
	}
}