//James Hall c00007006
#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 

#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h> 
#include <time.h> 
#include <string>
#include <fstream>
#include <vector>


int main() {
	std::string line;

	//place example.txt in the same folder as this code is in.
	std::ifstream myfile("textDoc.txt");
	std::vector<int> numArr;

	if (myfile.is_open())
	{
		while (std::getline(myfile, line))
		{
			int countDigit = 0;
			int i = 0;
			while (line.at(i) != ',') {
				countDigit++;
				i++;
			}
			int noOfEl = std::stoi(line.substr(0, countDigit));
			std::cout << "There are " << noOfEl << " elements in the graph." << std::endl;

			int start = line.find(' ') + 1;
			int max = std::stoi(line.substr(start, line.substr(start).find(',')));
			int increment = 0;
			//Fill Vector
			for (int i = start; i < line.length(); i += increment) {
				increment = line.substr(i, line.substr(i).find(',')).length() + 1;
				numArr.push_back(std::stoi(line.substr(i, line.substr(i).find(','))));
			}
			//Print Horizontal
			for (int i = 0; i < numArr.size(); i++)
			{
				int c = numArr[i];
				if (c > max)
				{
					max = c;
				}
				for (int bar = 0; bar < c; bar++) {
					std::cout << '0';
				}
				std::cout << std::endl;
			}
			std::cout << std::endl;

			for (int i = 0; i < max; i++)
			{
				for (int bar = 0; bar < numArr.size(); bar++) {
					int c = numArr[bar];
					if (i + c >= max) {
						std::cout << "0 ";
					}
					else {
						std::cout << "  ";
					}
				}
				std::cout << std::endl;
			}
			std::cout << std::endl;
		}
		myfile.close();
	}
	else
	{
		std::cout << "Unable to open file";
	}


	//create Window

	sf::RenderWindow window(sf::VideoMode(1290, 600), "Bar Chart");

	sf::RectangleShape simpleRectangle;
	float width = 20;
	float height = 50;

	simpleRectangle.setSize(sf::Vector2f(width, height));

	simpleRectangle.setFillColor(sf::Color::Red);

	simpleRectangle.setPosition(0, 0);



	// set timePerFrame to 1 60th of a second. 60 frames per second

	sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);

	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	// the clock object keeps the time.
	sf::Clock clock;

	clock.restart();

	while (window.isOpen())
	{
		// check if the close window button is clicked on.
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//add to the time since last update and restart the clock
		timeSinceLastUpdate += clock.restart();

		//update every 60th of a second
		//only when the time since last update is greater than 1/60 update the world.

		if (timeSinceLastUpdate > timePerFrame)
		{

			window.clear();

			sf::Color colArr[] = { sf::Color::Red, sf::Color::Yellow, sf::Color::Cyan, sf::Color::Green, sf::Color::Magenta };
			int highest = numArr[0];
			for (int i = 0; i < numArr.size(); i++) {
				if (numArr[i] > highest) {
					highest = numArr[i];
				}
			}
			for (int i = 0; i < numArr.size(); i++)
			{
				int c = numArr[i];
				simpleRectangle.setSize(sf::Vector2f(1290 / (numArr.size() + 5), 10000));
				simpleRectangle.setFillColor(colArr[i % 5]);
				simpleRectangle.setPosition((i + 2) * (1290 / (numArr.size() + 3)), 600 - c * (600 / highest));
				window.draw(simpleRectangle);
			}
			window.display();

			// reset the timeSinceLastUpdate to 0 
			timeSinceLastUpdate = sf::Time::Zero;
		}
	}
	return 0;
}