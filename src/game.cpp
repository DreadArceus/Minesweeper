#include <iostream>
#include <cmath>
#include "game.hpp"

using namespace std;

ground::ground(int n, vector<sf::Sprite> sp)
{
  grid.resize(n);
  visibilityGrid.resize(n);
  for(int i = 0; i < grid.size(); i++)
  {
    vector<int> loc(n, 0);
    visibilityGrid[i] = grid[i] = loc;
  }
  started = ended = finished = false;
  //saving the sprites for later drawing
  this->sp = sp;
}

void ground::makeGrid(int x, int y)
{
  visibilityGrid = grid; //Resets initial mine marks

  //Mines:
  srand(time(0));
  int n = grid.size();
  int num = (n * n) / 5;
  vector<int> columnCounter(n, 0);
  vector<int> rowCounter(n, 0);
  while(num--)
  {
    pair<int, int> coords = {rand() % n, rand() % n};
    if(pow(x - coords.first, 2) + pow(y - coords.second, 2) <= 2
      || grid[coords.first][coords.second] == 9
      || columnCounter[coords.second] >= n/2
      || rowCounter[coords.first] >= n/2)
    {
      num++;
      continue;
    }
    grid[coords.first][coords.second] = 9;
    rowCounter[coords.first]++;
    columnCounter[coords.second]++;
  }

  //Rest of the grid:
  for(int i = 0; i < grid.size(); i++)
  {
    for(int j = 0; j < grid[0].size(); j++)
    {
      if(grid[i][j] == 9)
      {
        continue;
      }
      if(i != 0)
      {
        grid[i][j] += (grid[i-1][j] == 9)
                      + (j != 0 && grid[i-1][j-1] == 9)
                      + (j != grid.size() - 1 &&grid[i-1][j+1] == 9);
      }
      if(i != grid.size() - 1)
      {
        grid[i][j] += (grid[i+1][j] == 9)
                      + (j != 0 && grid[i+1][j-1] == 9)
                      + (j != grid.size() - 1 && grid[i+1][j+1] == 9);
      }
      grid[i][j] += (j != 0 && grid[i][j-1] == 9)
                    + (j != grid.size() - 1 && grid[i][j+1] == 9);
    }
  }
}

void ground::play()
{
  int lenX = sp[0].getGlobalBounds().width, lenY = sp[0].getGlobalBounds().height;

  //create the window
	sf::RenderWindow rw(sf::VideoMode(grid.size() * lenX, grid.size() * lenY), "Minesweeper");
	rw.setFramerateLimit(60);

	//run as long as window is open
	while(rw.isOpen())
	{
    //checks if a mine has been set off
    if(ended)
    {
      processEnd();
      ended = false; //to avoid repeated end processing
      finished = true;
    }
		//check all events that were triggered between the iterations of the loop
		sf::Event event;
		while(rw.pollEvent(event))
		{
			//if the event is requesting closing the window, close it (subsequently the program terminates)
			if(event.type == sf::Event::Closed)
			{
				rw.close();
			}
      else if(!finished && event.type == sf::Event::MouseButtonPressed)
      {
        int cX = event.mouseButton.x, cY = event.mouseButton.y;
        int j = cX/lenX, i = cY/lenY;
        if(event.mouseButton.button == sf::Mouse::Right)
        {
          processMove(i, j, 'M');
        }
        else if(event.mouseButton.button == sf::Mouse::Left)
        {
          if(!started)
          {
            makeGrid(i, j);
            started = true;
          }
          processMove(i, j, 'D');
        }
      }
		}

		//clear the window with black color (prevents frames from overlapping)
		rw.clear(sf::Color::Black);

		//Drawing the unfiltered full grid
    for(int i = 0; i < grid.size(); i++)
    {
      for(int j = 0; j < grid.size(); j++)
      {
        if (visibilityGrid[i][j] == 0)
        {
          sp[10].setPosition(j * lenX, i * lenY);
          rw.draw(sp[10]);
        }
        else if(visibilityGrid[i][j] == -1)
        {
          sp[11].setPosition(j * lenX, i * lenY);
          rw.draw(sp[11]);
        }
        else
        {
          if(visibilityGrid[i][j] == 4)
          {
            sp[grid[i][j]].setColor(sf::Color::Red);
          }
          else if(visibilityGrid[i][j] == 3)
          {
            sp[grid[i][j]].setColor(sf::Color::Green);
          }
          else if(visibilityGrid[i][j] == 2)
          {
            sp[grid[i][j]].setColor(sf::Color::Yellow);
          }
          sp[grid[i][j]].setPosition(j * lenX, i * lenY);
          rw.draw(sp[grid[i][j]]);
          sp[grid[i][j]].setColor(sf::Color::White);
        }
      }
    }
    //end the current frame
    rw.display(); //mandatory to use display because of the underlying double-buffering.
  }
}

void ground::processMove(int x, int y, char operation)
{
  if(operation == 'D')
  {
    visibilityGrid[x][y] = 1;
    if(grid[x][y] == 0)
    {
      for(int i = x - 1; i < x + 2; i++)
      {
        for(int j = y - 1; j < y + 2; j++)
        {
          if(i >= 0 && j >= 0 && j < grid.size() && i < grid.size()
            && visibilityGrid[i][j] == 0)
          {
            processMove(i, j, 'D');
          }
        }
      }
    }
    if(grid[x][y] == 9)
    {
      ended = true;
      cout << "You lost, Better luck next time..." << endl;
    }
  }
  else
  {
    if(visibilityGrid[x][y] == 0)
    {
      visibilityGrid[x][y] = -1;
    }
    else if(visibilityGrid[x][y] == -1)
    {
      visibilityGrid[x][y] = 0;
    }
  }
  if(checkWin())
  {
    ended = true;
    cout << "Congratulations, you have won!" << endl;
    return;
  }
}

void ground::processEnd()
{
  for(int i = 0; i < grid.size(); i++)
  {
    for(int j = 0; j < grid.size(); j++)
    {
      if(visibilityGrid[i][j] == 0)
      {
        visibilityGrid[i][j] = 2;
      }
      else if(visibilityGrid[i][j] == -1)
      {
        if(grid[i][j] == 9)
        {
          visibilityGrid[i][j] = 3;
        }
        else
        {
          visibilityGrid[i][j] = 4;
        }
      }
      else if(visibilityGrid[i][j] == 1 && grid[i][j] == 9)
      {
        visibilityGrid[i][j] = 4;
      }
    }
  }
}

bool ground::checkWin()
{
  bool w1 = true, w2 = true;
  for(int i = 0; i < grid.size(); i++)
  {
    for(int j = 0; j < grid.size(); j++)
    {
      if(grid[i][j] != 9 && visibilityGrid[i][j] != 1)
      {
        w1 = false;
      }
      if(grid[i][j] == 9 && visibilityGrid[i][j] != -1)
      {
        w2 = false;
      }
      if(visibilityGrid[i][j] == -1 && grid[i][j] != 9)
      {
        w2 = false;
      }
    }
  }
  return w1||w2;
}