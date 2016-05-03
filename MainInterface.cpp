#include <ctime>
#include "MainInterface.h"
#include "Block.h"
#include "FileManager.h"
#include <queue>

//constructor for main interface
MainInterface::MainInterface() {
	//ready window
	window = new sf::RenderWindow(sf::VideoMode(800,500), "Block Solver", sf::Style::Titlebar | sf::Style::Close);
	status = WAITING;
	zoomSize = 0;
	solver = 0;

	//ready font
	textFont = sf::Font();
	if(!textFont.loadFromFile("arial.ttf")) throw;

	//make "Load" button
	loadButton = new sf::RectangleShape(sf::Vector2f(100,50));
	loadButton->setPosition(sf::Vector2f(500,450));
	loadButton->setFillColor(sf::Color::Color(127,127,127,255));
	loadText = sf::Text("Load",textFont,30);
	loadText.setColor(sf::Color::White);
	loadText.setPosition(550-loadText.getGlobalBounds().width/2, 475-loadText.getGlobalBounds().height/2);

	/*/ FEATURE make "Test Block" button
	testBlockButton = new sf::RectangleShape(sf::Vector2f(100,50));
	testBlockButton->setPosition(sf::Vector2f(600,450));
	testBlockButton->setFillColor(sf::Color::Color(127,127,127,255));*///hidden

	//make "Step" button
	stepButton = new sf::RectangleShape(sf::Vector2f(100,50));
	stepButton->setPosition(sf::Vector2f(350,450));
	stepButton->setFillColor(sf::Color::Color(127,127,127,255));
	stepText = sf::Text("Step",textFont,30);
	stepText.setColor(sf::Color::White);
	stepText.setPosition(400-stepText.getGlobalBounds().width/2, 475-stepText.getGlobalBounds().height/2);

	//make "Play/Pause" button
	playPauseButton = new sf::RectangleShape(sf::Vector2f(100,50));
	playPauseButton->setPosition(sf::Vector2f(200,450));
	playPauseButton->setFillColor(sf::Color::Color(127,127,127,255));
	playPauseText = sf::Text("",textFont,30);
	playPauseText.setColor(sf::Color::White);

	//make speed indicator
	speedometer = sf::Text("Speed :",textFont, 10);
	speedometer.setColor(sf::Color::White);
	speedometer.setPosition(sf::Vector2f(5,5));
}

//function used internally to discover what action to take uppon click event
//Preconditions: x and y are integers within the bounds of the display window.
void MainInterface::manageClick(int x, int y) {
	Block *block = 0;
	
	//test block
	/* FEATURE hidden
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
	}*/

	//load puzzle region
	if (x > loadButton->getPosition().x &&
		x < loadButton->getPosition().x + loadButton->getSize().x &&
		y > loadButton->getPosition().y &&
		y < loadButton->getPosition().y + loadButton->getSize().y)
	{
		if (status != RUNNING) solver = FileManager::loadPuzzle(); //don't load the puzzle unless the solver is paused.
		if (solver != NULL) {
			//set up new display mode
			Board* board = solver->getBoard();
			int bWidth = board->getWidth();
			int bHeight = board->getHeight();
			int bDepth = board->getDepth();

			//size the diplay to maximum
			if (800/(bWidth*bDepth+bDepth-1) > 400/bHeight) {//if the "aspect ratio" of the puzzle is taller than the window:
				zoomSize = 400/bHeight;
			}
			else zoomSize = 800/(bWidth*bDepth+bDepth-1);//if the "aspect ratio" is wider.
			
			//prepare Board display
			boardSpace = new sf::RectangleShape[bDepth];
			for (int i = bDepth-1; i >= 0; i--) {//initialize the "look" of the empty display
				*(boardSpace+i) = sf::RectangleShape(sf::Vector2f(0,0));
				(boardSpace+i)->setFillColor(sf::Color::Transparent);
				(boardSpace+i)->setOutlineColor(sf::Color::Black);
				(boardSpace+i)->setOutlineThickness(3);
				(boardSpace+i)->setSize(sf::Vector2f(bWidth*zoomSize, bHeight*zoomSize));
				(boardSpace+i)->setPosition(sf::Vector2f(400-(bWidth+1)*bDepth*zoomSize/2+(bWidth+1)*i*zoomSize + zoomSize/2,
														200-bHeight*zoomSize/2));
			}

			//prepare label for play/pause button
			playPauseText.setString("Solve");
			playPauseText.setPosition(250-playPauseText.getGlobalBounds().width/2, 475-playPauseText.getGlobalBounds().height/2);

			status = PAUSED;
		}
	}

	//step solver region
	if (x > stepButton->getPosition().x &&
		x < stepButton->getPosition().x + stepButton->getSize().x &&
		y > stepButton->getPosition().y &&
		y < stepButton->getPosition().y + stepButton->getSize().y)
	{
		if (status != WAITING && status != RUNNING) solver->step(); //step the solver once if it's not waiting for a puzzle or running automatically
	}

	//run/stop solver region
	if (x > playPauseButton->getPosition().x &&
		x < playPauseButton->getPosition().x + playPauseButton->getSize().x &&
		y > playPauseButton->getPosition().y &&
		y < playPauseButton->getPosition().y + playPauseButton->getSize().y)
	{
		if (status == RUNNING) {//if the solver is running, stop it
			playPauseText.setString("Solve");
			playPauseText.setPosition(250-playPauseText.getGlobalBounds().width/2, 475-playPauseText.getGlobalBounds().height/2);
			status = PAUSED;
		}
		else if (status == PAUSED) {//if the solver is puased, run it
			playPauseText.setString("Pause");
			playPauseText.setPosition(250-playPauseText.getGlobalBounds().width/2, 475-playPauseText.getGlobalBounds().height/2);
			status = RUNNING;
		}
	}
}

//Begins the bulk loop for the program
void MainInterface::run() {
	//establish timing setup for speedometer
	int reps = 0;
	clock_t lastClock = clock();
	std::queue<double long> timeBuffer = std::queue<double long>();
	for (int i = 0; i < 60; i++) timeBuffer.push(0);

	while (window->isOpen()) {//main loop runs while the window isn't closed
		sf::Event event;
		while (window->pollEvent(event)) {//check for events
			if (event.type == sf::Event::Closed) window->close(); //exit if the window get's "x'd out"
			if (event.type == sf::Event::MouseButtonPressed) manageClick(event.mouseButton.x, event.mouseButton.y);//user mouse input sent to internal function
		}

		if (status == RUNNING) {//if the solver is active, automatically step
			if(solver->step()) {
				FileManager::saveSolution(solver, reps);
				//FEATURE: puase solver if the option is implemented and checked
			}
			reps++;

			//update solver clock;
			double long temp = timeBuffer.front();
			timeBuffer.pop();
			lastClock = clock();
			timeBuffer.push(lastClock);
			speedometer.setString("Steps per second: " + std::to_string(60000/(lastClock - temp))); //calculates average time over 60 steps

		}
		else speedometer.setString("");//don't display the speedometer if the solver isn't running.

		
		//prepare for display sequence
		window->clear(sf::Color(63,63,63,255));
		//draw board
		if (solver != 0) {
			for (int i = 0; i < solver->getBoard()->getDepth(); i++) window->draw(*(boardSpace+i));//draw the base of the board

			int w = solver->getBoard()->getDepth() -1;
			for (w; w >= 0; w--){//for each level...
				int v = solver->getBoard()->getHeight() - 1;
				for (v; v >= 0; v--) {//for each row...
					int u = solver->getBoard()->getWidth() - 1;
					for (u; u >= 0; u--) {//for each column...
						//make a square that matches the color on the board at that position
						sf::RectangleShape temp = sf::RectangleShape(sf::Vector2f(zoomSize,zoomSize));
						temp.setFillColor(solver->colorAt(u,v,w));
						temp.setOutlineColor(sf::Color::Black);
						temp.setOutlineThickness(1);

						//move that square to the proper position on the screen
						temp.setPosition((400-(solver->getBoard()->getWidth()+1)*solver->getBoard()->getDepth()*zoomSize/2+(solver->getBoard()->getWidth()+1)*w*zoomSize + zoomSize/2)+u*zoomSize,
										200-(solver->getBoard()->getHeight())*zoomSize/2+v*zoomSize);
						
						//draw that square
						window->draw(temp);
					}
				}
			}
		}
		if (status != RUNNING) { //unless the solver is running, draw the "load" button
			window->draw(*loadButton);
			window->draw(loadText);
		}
		// FEATURE hidden //window->draw(*testBlockButton);
		if (status == PAUSED) { //if a puzzle is loaded but not being solved, display the "Step" button.
			window->draw(*stepButton);
			window->draw(stepText);
		}
		if (status != WAITING) { //if a puzzle is loaded at all, display the play/pause button
			window->draw(*playPauseButton);
			window->draw(playPauseText);
		}
		window->draw(speedometer);
		window->display();
		//std::cout<<reps<<std::endl;
	}
}