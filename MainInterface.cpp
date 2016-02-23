#include "MainInterface.h"

MainInterface::MainInterface() {
	window = new sf::RenderWindow(sf::VideoMode(800,500), "Block Solver", sf::Style::Titlebar | sf::Style::Close);
	shape1 = new sf::CircleShape(100.f);
	shape1->setFillColor(sf::Color::Green);
}

void MainInterface::run() {
	while (window->isOpen()) {
		sf::Event event;
		while (window->pollEvent(event)) {
			if (event.type == sf::Event::Closed) window->close();
		}

		window->clear();
		window->draw(*shape1);
		window->display();
	}
}