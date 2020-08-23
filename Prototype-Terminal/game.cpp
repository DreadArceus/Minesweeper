#include <iostream>
#include <cmath>
#include "game.hpp"
using namespace std;
ground::ground(int n)
{
  grid.resize(n);
  visibilityGrid.resize(n);
  for(int i = 0; i < grid.size(); i++)
  {
    vector<int> loc(n, 0);
    visibilityGrid[i] = grid[i] = loc;
  }
  finished = false;
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
      || grid[coords.first][coords.second] == -1
      || columnCounter[coords.second] >= n/2
      || rowCounter[coords.first] >= n/2)
    {
      num++;
      continue;
    }
    grid[coords.first][coords.second] = -1;
    rowCounter[coords.first]++;
    columnCounter[coords.second]++;
  }
  //Rest of the grid:
  for(int i = 0; i < grid.size(); i++)
  {
    for(int j = 0; j < grid[0].size(); j++)
    {
      if(grid[i][j] == -1)
      {
        continue;
      }
      if(i != 0)
      {
        grid[i][j] += (grid[i-1][j] == -1)
                      + (j != 0 && grid[i-1][j-1] == -1)
                      + (j != grid.size() - 1 &&grid[i-1][j+1] == -1);
      }
      if(i != grid.size() - 1)
      {
        grid[i][j] += (grid[i+1][j] == -1)
                      + (j != 0 && grid[i+1][j-1] == -1)
                      + (j != grid.size() - 1 && grid[i+1][j+1] == -1);
      }
      if(j != 0)
      {
        grid[i][j] += (grid[i][j-1] == -1);
      }
      if(j != grid.size() - 1)
      {
        grid[i][j] += (grid[i][j+1] == -1);
      }
    }
  }
  processMove(x, y, 'D');
}

void ground::printGrid()
{
  cout << "    " << ((grid.size() > 10) ? " " : "");
  for(int x = 0; x < grid.size(); x++)
  {
    cout << x << (((grid.size() > 10 && x < 9) || grid.size() <= 10) ? "   " : "  ");
  }
  cout << "\n";
  for(int x = 0; x < grid.size(); x++)
  {
    int y = 0;
    cout << ((grid.size() > 10) ? " " : "") << "  -";
    for(int i = 0; i < 2 * grid.size(); i++)
    {
      cout << "--";
    }
    cout << "\n";
    cout << ((grid.size() > 10 && x < 10) ? " " : "") << x << " ";
    for(int i = 0; i < 2 * grid.size() + 1; i++)
    {
      if(i % 2 == 0)
      {
        cout << "|";
      }
      else if(visibilityGrid[x][y++] == 1)
      {
        if(grid[x][y-1] == -1)
        {
          cout << "*";
        }
        else
        {
          cout << grid[x][y-1];
        }
      }
      else if(visibilityGrid[x][y-1] == -1)
      {
        cout << "!";
      }
      else
      {
        cout << " ";
      }
      cout << " ";
    }
    cout << "\n";
  }
  cout << ((grid.size() > 10) ? " " : "") << "  -";
  for(int i = 0; i < 2 * grid.size(); i++)
  {
    cout << "--";
  }
  cout << "\n";
}

bool ground::checkWin()
{
  for(int i = 0; i < grid.size(); i++)
  {
    for(int j = 0; j < grid.size(); j++)
    {
      if(grid[i][j] != -1 && visibilityGrid[i][j] != 1)
      {
        return false;
      }
    }
  }
  return true;
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
    if(grid[x][y] == -1)
    {
      finished = true;
    }
    else
    {
      finished = checkWin();
    }
  }
  else
  {
    visibilityGrid[x][y] = -1;
  }
}

void ground::show()
{
  for(int x = 0; x < grid.size(); x++)
  {
    int y = 0;
    cout << "-";
    for(int i = 0; i < 2 * grid.size(); i++)
    {
      cout << "--";
    }
    cout << "\n";
    for(int i = 0; i < 2 * grid.size() + 1; i++)
    {
      if(i % 2 == 0)
      {
        cout << "|";
      }
      else
      {
        if(grid[x][y++] == -1)
        {
          cout << "*";
        }
        else
        {
          cout << grid[x][y-1];
        }
      }
      cout << " ";
    }
    cout << "\n";
  }
  for(int i = 0; i < 2 * grid.size() + 1; i++)
  {
    cout << "--";
  }
  cout << "\n";
}
