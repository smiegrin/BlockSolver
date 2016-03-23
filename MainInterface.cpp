#include "MainInterface.h"
#include "Block.h"
#include "FileManager.h"

MainInterface::MainInterface() {
	window = new sf::RenderWindow(sf::VideoMode(800,500), "Block Solver", sf::Style::Titlebar | sf::Style::Close);
	status = WAITING;
	zoomSize = 0;
	solver = 0;

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

	//prepare Board display
	boardSpace = new sf::RectangleShape(sf::Vector2f(0,0));
	boardSpace->setFillColor(sf::Color::Transparent);
	boardSpace->setOutlineColor(sf::Color::Black);
	boardSpace->setOutlineThickness(3);
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
		if (solver != NULL) {
			//set up new display mode
			Board* board = solver->getBoard();
			int bWidth = board->getWidth();
			int bHeight = board->getHeight();
			int bDepth = board->getDepth();
			if (bWidth < bHeight) {
				zoomSize = 400/bHeight;
			}
			else zoomSize = 400/bWidth;
			boardSpace->setSize(sf::Vector2f(bWidth*zoomSize, bHeight*zoomSize));
			status = PAUSED;
		}
	}

	//step solver
	if (x > stepButton->getPosition().x &&
		x < stepButton->getPosition().x + stepButton->getSize().x &&
		y > stepButton->getPosition().y &&
		y < stepButton->getPosition().y + stepButton->getSize().y)
	{
		if (status != WAITING && status != RUNNING) solver->step();
	}

	//run/stop solver
	if (x > playPauseButton->getPosition().x &&
		x < playPauseButton->getPosition().x + playPauseButton->getSize().x &&
		y > playPauseButton->getPosition().y &&
		y < playPauseButton->getPosition().y + playPauseButton->getSize().y)
	{
		if (status == RUNNING) {
			status = PAUSED;
		}
		if (status == PAUSED) {
			status = RUNNING;
		}
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
		window->draw(*boardSpace);
		//draw board
		if (solver != 0) {
		int v = solver->getBoard()->getHeight() - 1;
			for (v; v >= 0; v--) {
				int u = solver->getBoard()->getWidth() - 1;
				for (u; u >= 0; u--) {
					sf::RectangleShape temp = sf::RectangleShape(sf::Vector2f(zoomSize,zoomSize));
					temp.setFillColor(solver->colorAt(u,v,0));
					temp.setOutlineColor(sf::Color::Black);
					temp.setOutlineThickness(3);
					temp.setPosition(u*zoomSize, v*zoomSize);
					window->draw(temp);
				}
			}
		}
		window->draw(*loadButton);
		window->draw(*testBlockButton);
		window->draw(*stepButton);
		window->draw(*playPauseButton);
		window->display();
	}
}