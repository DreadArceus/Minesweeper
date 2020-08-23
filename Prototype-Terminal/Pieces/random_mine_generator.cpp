#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;
vector<pair<int, int>> placeMines(int n)
{
  vector<pair<int, int>> mines;
  srand(time(0));
  int num = (n * n) / 6;
  while(num--)
  {
    pair<int, int> coordinates = {rand() % n, rand() % n};
    mines.push_back(coordinates);
  }
  return mines;
}
int main()
{
  static constexpr int n = 20;
  vector<pair<int, int>> v = placeMines(n);
  for(int i = 0; i < v.size(); i++)
  {
    cout << v[i].first << " " << v[i].second << "\n";
  }
  return 0;
}
//8 * 10 = 80 --> 10 (Easy)
//14 * 18 = 252 --> 40 (Medium)
//20 * 24 = 480 --> 99 (Hard)
