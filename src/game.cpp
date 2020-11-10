#include "game.hpp"

game::game()
{
      for (int i = 0; i < num; i++)
        for (int j = 0; j < num; j++)
        {
            if (i == 0 || i == num - 1 || j == 0 || j == num - 1) //border
                grid[i][j] = 0;
            else
                grid[i][j] = 1;
        }

    for (int i = 0; i < num; i++)
        for (int j = 0; j < num; j++)
        {
            dj.visited[i][j] = false; //all cells are unvisited
            filled[i][j] = 0;         //all cells are empty
        }
  
}

void game::start()
{
    

    RenderWindow window(VideoMode(1000,900),"Grid");

    //Loading the font
    font.loadFromFile("arial.ttf");
    Text move("Moves:", font, 15);
    Text m(" ", font, 15);
    //Texture for empty cells
    if (!path.loadFromFile("media/bg.jpg", sf::IntRect(500, 400, 30, 30)))
    {
        cout << "Unable to load image!";
    }
    //texture for obstacles
    if (!black.loadFromFile("media/bg.jpg", sf::IntRect(400, 400, 30, 30)))
    {
        cout << "Unable to load image!";
    }
    //background
    if (!background.loadFromFile("media/bg.jpg"))
    {
        cout << "Unable to load image!";
    }
    //txture for knight
    if (!texPlayer.loadFromFile("media/knight.png"))
    {
        cout << "Unable to load image!";
    }
    //texture for princess
    if (!texPrincess.loadFromFile("media/princess.png", sf::IntRect(0, 0, 110, 170)))
    {
        cout << "Unable to load image!";
    }

    bg.setTexture(background);
    bg.setScale(1000 / bg.getGlobalBounds().width, 900 / bg.getGlobalBounds().height);

    player.pSprite(texPlayer);
    // player.setTextureRect(sf::IntRect(5, 5, 40, 40));

    princess.setTexture(texPrincess);
    princess.setTextureRect(sf::IntRect(30, 30, 80, 130));
    princess.setScale(0.35f, 0.35f);

    paths.setTexture(path);

    obstacle.setTexture(black);

    //cell visited using djkstr algorithm
    CircleShape visitedcell(10);
    visitedcell.setFillColor(Color(200, 200, 140));

    //Shortest path using dijkstra algorthm
    CircleShape sPath(10);
    sPath.setFillColor(Color::Yellow);

    CircleShape hint(35); //button dijkstra
    hint.setFillColor(Color::Green);

       for (int i = 0; i < 400; i++)
    {
        int a=rand()%30,b=rand()%30;
        if (!((a==posY&&b==posX)||(a==destY&&b==destX)))
        {
             grid[a][b]=0;
        }
        
       
    }

    while (window.isOpen())
    {
        dtime = clock.restart().asSeconds();
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Space)
                window.close();

            if (grid[posX][posY] == 1)
            {

                //movement of player
                if (event.type == Event::KeyPressed)
                {
                    if (event.key.code == sf::Keyboard::Left)
                    {
                        if (grid[posX][posY - 1] == 1)
                        {
                            player.moveLeft();
                            posY = posY - 1;
                            moves--;
                        }
                    }
                    else if (event.key.code == sf::Keyboard::Right)
                    {
                        if (grid[posX][posY + 1] == 1)
                        {
                            player.moveRight();
                            posY = posY + 1;
                            moves--;
                        }
                    }
                    else if (event.key.code == sf::Keyboard::Up)
                    {
                        if (grid[posX - 1][posY] == 1)
                        {
                            player.moveUp();
                            posX = posX - 1;
                            moves--;
                        }
                    }
                    else if (event.key.code == sf::Keyboard::Down)
                    {
                        if (grid[posX + 1][posY] == 1)
                        {
                            player.moveDown();
                            posX = posX + 1;
                            moves--;
                        }
                    }
                    player.setSpeed(3, sf::milliseconds(80));
                }
            }

// if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) //Move Up
//             player.moveUp();

//         else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) //Move Down
//             player.moveDown();

//         else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) //Move Right
//             player.moveRight();

//         else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) //Move Left
//             player.moveLeft();

//         //SPRINT
//         if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
//             player.setSpeed(0.35, sf::milliseconds(50));
//         else
            // player.setSpeed(0.20, sf::milliseconds(80));


            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
            {
                int X = event.mouseButton.x;
                int Y = event.mouseButton.y;
                int row = Y / 30; //Reversed notion of row & column
                int col = X / 30;

                cout << "Cell " << row << " , " << col << " state is: " << grid[row][col] << endl;
                if (X > 900 && X < 975 && Y > 30 && Y < 100)
                {
                    //calling dijkstra function
                    dj.run(posX, posY, destX, destY, grid);
                }
            }
        }

        if (moves <= 0)
        {
            window.close();
            gameOver();
        }

        if (posX == destX && posY == destY)
        {
            window.close();
            Supriya();
        }

        window.clear();
        window.draw(bg);
        hint.setPosition(930, 30);

        //launch dijkstrab algorithm
        window.draw(hint);

        //number of moves recorded
        move.setPosition(940, 40);
        move.setFillColor(Color::Black);
        m.setPosition(950, 60);
        m.setFillColor(Color::Black);
        window.draw(move);

        //to conert int to string
        stringstream ss, ss1;
        ss1 << dj.pathD.size();

        ss << moves;
        m.setString(ss.str());
        window.draw(m);

        if (!dj.pathD.empty())
        {
            for (int i = 0; i < dj.pathD.size(); i++)
            {
                sPath.setPosition(dj.pathD[i].second * 30 + 5, dj.pathD[i].first * 30 + 5); //Reversed notion of row & column
                window.draw(sPath);                                                         //final pathD
                filled[dj.pathD[i].first][dj.pathD[i].second] = 1;
            }
        }

        filled[destX][destY] = 1;
        for (int i = 0; i <= 29 * 30; i += 30)
            for (int j = 0; j <= 29 * 30; j += 30)
            {

                if (grid[i / 30][j / 30] == 0)
                {
                    //draw the obstacles
                    obstacle.setPosition(j, i);
                    window.draw(obstacle);
                }

                else if (dj.visited[i / 30][j / 30] == true && filled[i / 30][j / 30] == 0)
                {
                    //visited cells in using dijkstra algorithm
                    visitedcell.setOutlineThickness(2);
                    visitedcell.setOutlineColor(Color::Black);
                    visitedcell.setPosition(j + 5, i + 5);
                    window.draw(visitedcell);
                }

                //if not obstacles,no used in dijkstra algorithm draw the empty path
                if (grid[i / 30][j / 30] == 1 && dj.visited[i / 30][j / 30] == false && filled[i / 30][j / 30] == 0)
                {
                    paths.setPosition(j, i);
                    window.draw(paths);
                }
            }
            // player.getSprite().setPosition(posY*30, posX*30);
        window.draw(player.getSprite()); //source

        princess.setPosition(destY * 30, destX * 30 - 10);

        window.draw(princess); //destination
        cout<<player.getSprite().getPosition().x;
        cout<<"       "<<player.getSprite().getPosition().x<<endl;


        window.display();
    }
}

void game:: gameOver(){
    cout<<"You are out of the moves, so Game Over!";

}

void game:: Supriya()
{
    cout<<"Congratulations!!! You are on the next level to find the next princess.";
}

game::~game()
{
}
