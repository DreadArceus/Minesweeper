#include <iostream>
#include <vector>
using namespace std;
vector<vector<int>> initialiseGround(int n)
{
  vector<vector<int>> v(n);
  for(int i = 0; i < n; i++)
  {
    vector<int> loc(n, 0);
    v[i] = loc;
  }
  return v;
}
void putMines(int n, vector<vector<int>> &ground)
{
  for(int i = 0; i < n; i++)
  {
    int x = 0, y = 0;
    cin >> x >> y;
    ground[x][y] = -1;
  }
}
void calculateNumbers(vector<vector<int>> &ground)
{
  for(int i = 0; i < ground.size(); i++)
  {
    for(int j = 0; j < ground[0].size(); j++)
    {
      if(ground[i][j] == -1)
      {
        continue;
      }
      if(i != 0)
      {
        ground[i][j] += (ground[i-1][j] == -1)
                      + (j != 0 && ground[i-1][j-1] == -1)
                      + (j != ground.size() - 1 &&ground[i-1][j+1] == -1);
      }
      if(i != ground.size() - 1)
      {
        ground[i][j] += (ground[i+1][j] == -1)
                      + (j != 0 && ground[i+1][j-1] == -1)
                      + (j != ground.size() - 1 && ground[i+1][j+1] == -1);
      }
      if(j != 0)
      {
        ground[i][j] += (ground[i][j-1] == -1);
      }
      if(j != ground.size() - 1)
      {
        ground[i][j] += (ground[i][j+1] == -1);
      }
    }
  }
}
int main()
{
  int n = 0;
  cin >> n;
  vector<vector<int>> ground = initialiseGround(n);
  int m = 0;
  cin >> m;
  putMines(m, ground);
  calculateNumbers(ground);
  for(int i = 0; i < ground.size(); i++)
  {
    for(int j = 0; j < ground[0].size(); j++)
    {
      cout << ground[i][j] << " ";
    }
    cout << "\n";
  }
}
