#include <iostream>
#include <vector>
using namespace std;
vector<vector<int>> exampleGrid = { {-1, 3, 3, 3, -1},
                                    {2, -1, -1, -1, 3},
                                    {2, 4, -1, 4, -1},
                                    {2, -1, 3, 3, 2},
                                    {-1, 2, 2, -1, 1} };
vector<vector<bool>> initialiseVisible()
{
  vector<vector<bool>> v(exampleGrid.size());
  for(int i = 0; i < v.size(); i++)
  {
    vector<bool> loc(v.size(), 0);
    v[i] = loc;
  }
  return v;
}
void printCurrent(vector<vector<bool>> v)
{
  for(int i = 0; i < v.size(); i++)
  {
    for(int j = 0; j < v[0].size(); j++)
    {
      cout << ((v[i][j]) ? exampleGrid[i][j] : 0) << " ";
    }
    cout << "\n";
  }
}
void processMoves(int n)
{
  vector<vector<bool>> visible = initialiseVisible();
  printCurrent(visible);
  while(n--)
  {
    int x = 0, y = 0;
    cin >> x >> y;
    visible[x][y] = 1;
    printCurrent(visible);
  }
}
int main()
{
  int n = 0;
  cin >> n;
  processMoves(n);
}
