#include <iostream>
#include "game.hpp"
#include "game.cpp"
using namespace std;
void play(ground &g)
{
  while(g.gameStatus())
  {
    char c = ' ';
    int x = 0, y = 0;
    cin >> c >> x >> y;
    g.processMove(x, y, c);
    system("clear");
    g.printGrid();
  }
}
void wrapUp(ground &g)
{
  cout << ((g.checkWin()) ? "Congratulations, You have won!\n"
                        : "You just dug up a mine... GAME OVER\n");
  cout << "Revealing the Board...\n";
  g.show();
}
int main()
{
  system("clear");
  cout << "Welcome to Minesweeper...\n" << "Enter the grid size: ";
  int n = 0;
  cin >> n;
  ground g(n);
  g.printGrid();
  char c = ' ';
  int x = 0, y = 0;
  cin >> c >> x >> y;
  while(c != 'D')
  {
    g.processMove(x, y, c);
    system("clear");
    g.printGrid();
    cin >> c >> x >> y;
  }
  g.makeGrid(x, y);
  system("clear");
  g.printGrid();
  play(g);
  wrapUp(g);
}
