#include <iostream>
using namespace std;
void makeGrid(int n)
{
  for(int z = 0; z < n; z++)
  {
    for(int i = 0; i < 2 * n + 1; i++)
    {
      cout << "--";
    }
    cout << "\n";
    for(int i = 0; i < 2 * n + 1; i++)
    {
      cout << ((i % 2 == 0) ? "| " : "* ");
    }
    cout << "\n";
  }
  for(int i = 0; i < 2 * n + 1; i++)
  {
    cout << "--";
  }
}
int main()
{
  int n = 0;
  cin >> n;
  makeGrid(n);
}
