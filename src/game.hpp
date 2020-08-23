#ifndef GAME_HPP
#define GAME_HPP

#include <vector>

using namespace std;

class ground
{
public:
  ground(int n, vector<sf::Sprite> sp);
  void makeGrid(int x, int y);
  void play();
  void processMove(int x, int y, char operation);
  void processEnd();
  bool checkWin();
private:
  vector<sf::Sprite> sp;
  vector<vector<int>> grid;
  vector<vector<int>> visibilityGrid;
  bool started, ended, finished;
};

#endif
