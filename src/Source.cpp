// #include <SFML/Graphics.hpp>
// #include <iostream>
// #include <string>
// #include <algorithm>

// //Initial Declarations of SFML components
// sf::RenderWindow renderWindow(sf::VideoMode(1000, 900), "Arthur- The Gladiator (Level 3)");
// sf::Font font;
// sf::Event event;
// sf::Texture boxTexture, bgTexture;

// std::vector<int> randomInts;

// //Random Initialization of Numbers
// void findRandomInt(int first, int last, std::vector<int> &randomList)
// {
// 	for (int i = first; i <= last; i++)
// 	{
// 		randomList.push_back(i);
// 	}
// 	int swapIndex;
// 	for (int i = 0; i < randomList.size(); i++)
// 	{
// 		std::cout << rand() << std::endl;
// 		swapIndex = rand() % randomList.size();
// 		std::swap(randomList[i], randomList[swapIndex]);
// 	}
// }

// //Creating the Vector Pair of Boxes and Numbers
// void setVector(std::vector<int> randomList)
// {

// 	//Rendering the Window
// 	while (renderWindow.isOpen())
// 	{

// 		while (renderWindow.pollEvent(event))
// 		{

// 			if (event.type == sf::Event::EventType::Closed)
// 				renderWindow.close();

// 			if (event.type == sf::Event::EventType::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
// 			{
// 				int X = event.mouseButton.x;
// 				int Y = event.mouseButton.y;

// 				if (X > 750 && X < 1000 && Y > 30 && Y < 60)
// 				{
// 					//sort in ascending order
// 					std::sort(randomList.begin(), randomList.end());
// 				}

// 				if (X > 750 && X < 1000 && Y > 30 && Y < 60)
// 				{
// 					//sort in descending order
// 					//now it is in ascending order
// 					std::sort(randomList.begin(), randomList.end());
// 				}
// 			}
// 		}

// 		sf::Sprite bgSprite(bgTexture), boxSprite(boxTexture);
// 		std::vector<std::pair<sf::Sprite, sf::Text>> boxSprites(40);

// 		bgSprite.scale(2.0f, 3.0f);
// 		boxSprite.scale(0.07f, 0.07f);

// 		sf::RectangleShape dSortButton(sf::Vector2f(250, 30));
// 		dSortButton.setFillColor(sf::Color::Green);
// 		dSortButton.setPosition(sf::Vector2f(490, 30));

// 		sf::RectangleShape aSortButton(sf::Vector2f(250, 30));
// 		aSortButton.setFillColor(sf::Color::Green);
// 		aSortButton.setPosition(sf::Vector2f(750, 30));

// 		sf::Text aSort("Sort in Ascending order", font, 20);
// 		aSort.setPosition(sf::Vector2f(775, 35));
// 		aSort.setFillColor(sf::Color::Black);

// 		sf::Text dSort("Sort in Descending order", font, 20);
// 		dSort.setPosition(sf::Vector2f(515, 35));
// 		dSort.setFillColor(sf::Color::Black);

// 		int coordY = 200;
// 		int a = 0;
// 		for (int j = 0; j < 5; j++)
// 		{
// 			int coordX = 20;
// 			for (int i = 0; i < boxSprites.size() / 5; i++)
// 			{
// 				boxSprites[a].first = boxSprite;
// 				boxSprites[a].first.setPosition(coordX, coordY);

// 				sf::Text message(std::to_string(randomList[a]), font);
// 				boxSprites[a].second = message;
// 				boxSprites[a].second.scale(0.8f, 0.8f);
// 				boxSprites[a].second.setPosition(coordX + 35, coordY + 35);
// 				coordX += 100;
// 				a++;
// 			}
// 			coordY += 140;
// 		}
// 		renderWindow.clear();
// 		renderWindow.draw(bgSprite);
		
// 		//drawing the boxes
// 		for (int i = 0; i < 40; i++)
// 		{
// 			renderWindow.draw(boxSprites[i].first);
// 			renderWindow.draw(boxSprites[i].second);
// 		}
// 		renderWindow.draw(dSortButton);
// 		renderWindow.draw(aSortButton);
// 		renderWindow.draw(dSort);
// 		renderWindow.draw(aSort);
// 		renderWindow.display();
// 	}
// }

// int main()
// {
// 	//Loading the Components
// 	if (!bgTexture.loadFromFile("images/dungeon.jpg"))
// 	{
// 		std::cout << "Error Displaying Background Image" << std::endl;
// 	};
// 	if (!boxTexture.loadFromFile("images/box.png"))
// 	{
// 		std::cout << "Error Displaying Boxes" << std::endl;
// 	};
// 	if (!font.loadFromFile("fonts/numberFont.ttf"))
// 	{
// 		std::cout << "Error Displaying Font" << std::endl;
// 	}

// 	//Find the random values to be displayed
// 	findRandomInt(1, 40, randomInts);
// 	for (int i = 0; i < randomInts.size(); i++)
// 	{
// 		std::cout << i + 1 << ": " << randomInts[i] << std::endl;
// 	}

// 	//Calls the function for rendering
// 	setVector(randomInts);
// }