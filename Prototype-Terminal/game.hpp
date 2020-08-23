#ifndef GAME_HPP
#define GAME_HPP
#include <vector>
using namespace std;
class ground
{
public:
  ground(int n);
  void makeGrid(int x, int y);
  void printGrid();
  void processMove(int x, int y, char operation);
  void show();
  bool gameStatus() {return !finished;}
  bool checkWin();
private:
  vector<vector<int>> grid;
  vector<vector<int>> visibilityGrid;
  bool finished;
};
#endif
