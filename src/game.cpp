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
            dj.filled[i][j] = 0;      //all cells are empty
        }
}

void game::start()
{

    RenderWindow window(VideoMode(1000, 900), "Grid");

    star.loadFromFile("sound/menu.wav");
    starsound.setBuffer(star);

     ride.loadFromFile("sound/textNoise.wav");
    rsound.setBuffer(ride);

    killed.loadFromFile("sound/attacked.wav");
    killsound.setBuffer(killed);

    attacked.loadFromFile("sound/killed.wav");
    attsound.setBuffer(attacked);

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

    //ememy texture
    if (!emy.loadFromFile("media/enemy.png", sf::IntRect(0, 0, 256, 2056)))
    {
        cout << "Unable to load image!";
    }

    //ememy texture
    if (!imm.loadFromFile("media/immunity.png"))
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

    enemy.setTexture(emy);
    enemy.setTextureRect(sf::IntRect(0, 500, 256, 346));
    enemy.setScale(0.15f, 0.2f);

    immunity.setTexture(imm);
    immunity.setScale(0.075f, 0.075f);

    paths.setTexture(path);

    obstacle.setTexture(black);

    //cell visited using dijkstra algorithm
    CircleShape visitedcell(10);
    visitedcell.setFillColor(Color(200, 200, 140));

    //Shortest path using dijkstra algorthm
    CircleShape sPath(10);
    sPath.setFillColor(Color::Yellow);

    CircleShape coin(35); //button dijkstra
    coin.setFillColor(Color::Green);

    CircleShape hint(35); //button dijkstra
    hint.setFillColor(Color::Green);

    CircleShape rules(35); //button dijkstra
    rules.setFillColor(Color::Green);

    // Thread thread(std::bind(&comments,"asdsfdf"));                        

    //Creating the obstacles
    for (int i = 0; i < 400; i++)
    {
        int a = rand() % 30, b = rand() % 30;
        if (!((a == posY && b == posX) || (a == destY && b == destX)))
        {
            grid[a][b] = 0;
        }
    }

    //Creating the immunity
    for (int i = 0; i < 20; i++)
    {
        int a = rand() % 30, b = rand() % 30;
        if (!((a == posY && b == posX) || (a == destY && b == destX)) && !(grid[a][b] == 2 || grid[a][b] == 3 || grid[a][b] == 0))
        {
            grid[a][b] = 4;
        }
    }

    //Creating the enemy
    for (int i = 0; i < 20; i++)
    {
        int a = (rand() + 50) % 30, b = (rand() + 50) % 30;
        if (!((a == posY && b == posX) || (a == destY && b == destX)))
        {
            if (grid[a][b] == 1 && (a > 4 || b > 4))
            {
                grid[a][b] = 2;
            }
            if (grid[a][b] == 2)
            {
                if (grid[a + 1][b + 1] == 1)
                {
                    grid[a + 1][b + 1] = 3;
                }

                if (grid[a + 1][b - 1] == 1)
                {
                    grid[a + 1][b - 1] = 3;
                }

                if (grid[a - 1][b + 1] == 1)
                {
                    grid[a - 1][b + 1] = 3;
                }

                if (grid[a - 1][b - 1] == 1)
                {
                    grid[a - 1][b - 1] = 3;
                }
            }
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

            //if you are stuck in jungle without path to move on, press enter and destroy adjascent four walls decreasing moves by 8
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Enter)
            {
                grid[posX - 1][posY] = 1;
                grid[posX + 1][posY] = 1;
                grid[posX][posY + 1] = 1;
                grid[posX][posY + 1] = 1;
                moves -= 8;
                comments("media/c.png");
                killsound.play();
            }

            if (!grid[posX][posY] == 0 && hints != 0)
            {

                //movement of player
                if (event.type == Event::KeyPressed)
                {
                    if (event.key.code == sf::Keyboard::Left)
                    {
                        if (!grid[posX][posY - 1] == 0)
                        {
                            player.moveLeft();
                            posY = posY - 1;
                            rsound.play();
                            moves--;
                        }
                    }
                    else if (event.key.code == sf::Keyboard::Right)
                    {
                        if (!grid[posX][posY + 1] == 0)
                        {
                            player.moveRight();
                            posY = posY + 1;
                            rsound.play();
                            moves--;
                        }
                    }
                    else if (event.key.code == sf::Keyboard::Up)
                    {
                        if (!grid[posX - 1][posY] == 0)
                        {
                            player.moveUp();
                            posX = posX - 1;
                            rsound.play();
                            moves--;
                        }
                    }
                    else if (event.key.code == sf::Keyboard::Down)
                    {
                        if (!grid[posX + 1][posY] == 0)
                        {
                            player.moveDown();
                            posX = posX + 1;
                            rsound.play();
                            moves--;
                        }
                    }
                    player.setSpeed(10, sf::milliseconds(80));
                }
            }

            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
            {
                int X = event.mouseButton.x;
                int Y = event.mouseButton.y;
                int row = Y / 30; //Reversed notion of row & column
                int col = X / 30;

                cout << "Cell " << row << " , " << col << " state is: " << grid[row][col] << endl;
                if (X > 900 && X < 975 && Y > 120 && Y < 190)
                {
                    if (hints == 1)
                    {
                        if (moves < 10)
                        {
                            cout << "You cant use hint! ";
                        }
                        dj.run(posX, posY, destX, destY, grid);
                        moves -= 10;
                        hints--;
                    }
                    else
                    {
                        dj.destroy();
                        if (dj.failed == true)
                        {
                            hints++;
                        }
                        else
                        {
                            hints += 10;
                            cout << "you can use hints only one time";
                        }
                    }
                }
            }
        }

        if (moves <= 0)
        {
            window.close();
            gameOver();
        }

        if (life <= 0)
        {
            window.close();
            gameOver();
            cout << "You are killed by enemy, try again!!!";
        }
        if (posX == destX && posY == destY)
        {
            window.close();
            Supriya();
        }

        window.clear();
        window.draw(bg);

        window.draw(player.getSprite()); //source

        coin.setPosition(930, 40);
        window.draw(coin);

        //launch dijkstra algorithm
        hint.setPosition(930,120);
        window.draw(hint);

        rules.setPosition(930,200);
        window.draw(rules);

        //number of moves recorded
        move.setPosition(940, 40);
        move.setFillColor(Color::Black);
        m.setPosition(950, 60);
        m.setFillColor(Color::Black);
        window.draw(move);

        //to conert int to string
        stringstream ss;
        // ss1 << dj.pathD.size();

        ss << moves;
        m.setString(ss.str());
        window.draw(m);

        dj.filled[destX][destY] = 1;
        for (int i = 0; i <= 29 * 30; i += 30)
            for (int j = 0; j <= 29 * 30; j += 30)
            {

                if (grid[i / 30][j / 30] == 0)
                {
                    //draw the obstacles
                    obstacle.setPosition(j, i);
                    window.draw(obstacle);
                }

                if (grid[i / 30][j / 30] == 2)
                {

                    //draw the immunity
                    enemy.setPosition(j, i);
                    window.draw(enemy);

                    // dj.run(posX, posY, i/30, j/30, grid);
                }

                if (grid[i / 30][j / 30] == 4)
                {

                    //draw the immunity
                    immunity.setPosition(j, i);
                    window.draw(immunity);

                    // dj.run(posX, posY, i/30, j/30, grid);
                }
                //Gaining the immunity i.e increasing the moves by 2
                if (grid[i / 30][j / 30] == 4 && posY == j / 30 && posX == i / 30)
                {

                    grid[i / 30][j / 30] = 1;
                    moves += 2;
                    comments("media/d.png");
                    starsound.play();
                }

                //You killed the enemy and gain the lives
                if (grid[i / 30][j / 30] == 2 && posY == j / 30 && posX == i / 30)
                {
                    int a=i/30,b=j/30;

                    grid[i / 30][j / 30] = 1;
                    life++;
                    comments("media/b.png");
                    killsound.play();

                     if (grid[a + 1][b + 1] == 3)
                {
                    grid[a + 1][b + 1] = 1;
                }

                if (grid[a + 1][b - 1] == 3)
                {
                    grid[a + 1][b - 1] = 1;
                }

                if (grid[a - 1][b + 1] == 3)
                {
                    grid[a - 1][b + 1] = 1;
                }

                if (grid[a - 1][b - 1] == 3)
                {
                    grid[a - 1][b - 1] = 1;
                }

                    
                }

                //enemy attacked you
                if (grid[i / 30][j / 30] == 3 && posY == j / 30 && posX == i / 30)
                {

                    cout << "Enemy attacked you!!!";
                    life--;
                    player.pSprite(texPlayer);
                    grid[i / 30][j / 30] = 1;
                    comments("media/a.png");
                    attsound.play();

                }

                else if (dj.visited[i / 30][j / 30] == 1 && dj.filled[i / 30][j / 30] == 0)
                {
                    //visited cells in using dijkstra algorithm
                    visitedcell.setOutlineThickness(2);
                    visitedcell.setOutlineColor(Color::Black);
                    visitedcell.setPosition(j + 5, i + 5);
                    window.draw(visitedcell);
                }

                //if not obstacles,no used in dijkstra algorithm draw the empty path
                if ((grid[i / 30][j / 30] == 1 || grid[i / 30][j / 30] == 3) && !(dj.visited[i / 30][j / 30] == 1) && dj.filled[i / 30][j / 30] == 0)
                {
                    paths.setPosition(j, i);
                    window.draw(paths);
                }
            }

        if (!dj.pathD.empty())
        {
            for (int i = 0; i < dj.pathD.size(); i++)
            {
                sPath.setPosition(dj.pathD[i].second * 30 + 5, dj.pathD[i].first * 30 + 5); //Reversed notion of row & column
                paths.setPosition(dj.pathD[i].second * 30 + 5, dj.pathD[i].first * 30 + 5);
                window.draw(paths);
                window.draw(sPath); //final pathD
                dj.filled[dj.pathD[i].first][dj.pathD[i].second] = 1;
            }
        }

        // player.getSprite().setPosition(posY*30, posX*30);

        window.draw(player.getSprite()); //source
        

        princess.setPosition(destY * 30, destX * 30 - 10);

        window.draw(princess); //destination
        // cout << player.getSprite().getPosition().x;
        // cout << "       " << player.getSprite().getPosition().x << endl;

        window.display();
    }
}

void game::gameOver()
{
    cout << "You are out of the moves, so Game Over!";
    sf::RenderWindow window;
window.create(sf::VideoMode(1000, 900), "");

  sf::Texture texture;
    if (!texture.loadFromFile("media/gameover.png"))
{
    // error...
}
sf::Sprite sprite;
sprite.setTexture(texture);
// sprite.setScale(f,0.7f);

        window.clear();
        window.draw(sprite);
        window.display();
         sf::sleep(sf::milliseconds(9000));
        // usleep(9000000);
         window.close();
}

void game::Supriya()
{
    cout << "Congratulations!!! You are on the next level to find the next princess.";
}

game::~game()
{
}

void game::comments(string image)
{

sf::RenderWindow window;
window.setPosition(Vector2i(690,720));
window.create(sf::VideoMode(300, 150), "",sf::Style::None);

  sf::Texture texture;
    if (!texture.loadFromFile(image))
{
    // error...
}
sf::Sprite sprite;
sprite.setTexture(texture);
sprite.setScale(0.7f,0.7f);

        window.clear();
        window.draw(sprite);
        window.display();
         sf::sleep(sf::milliseconds(900));
        // usleep(9000000);
         window.close();

}
