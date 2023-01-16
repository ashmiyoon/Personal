#include <iostream>
#include <vector>
#include <ctime>
#include <unistd.h>

class Grid
{
private:
  std::vector<std::vector<bool>> cellVec;
  int maxX;
  int maxY;
public:
  Grid(int maxX, int maxY, percentChance)
  : maxX(maxX), maxY(maxY)
  {
    for(int i = 0; i < maxX; i++)
    {
      std::vector<bool> v(maxY);
      for(int j = 0; j < maxY; j++)
      {
        v[j] = (rand() % 100 <= percentChance);
      }
      cellVec.push_back(v);
    }
  }

  inline bool cell(int x, int y)
  {
    if(x >= 0 && x < maxX && y >= 0 && y < maxY)
      return cellVec[x][y];
    else
      return false;
  }

  void update()
  {
    std::vector<std::vector<bool>> nextGen(maxX, std::vector<bool>(maxY, false));
    for(int x = 0; x < (int)cellVec.size(); x++)
    {
      for(int y = 0; y < (int)cellVec[x].size(); y++)
      {
        // Count neighbors
        int nNeighbors = 0;
        for(int dx = -1; dx <= 1; dx++)
        {
          for(int dy = -1; dy <= 1; dy++)
          {
            if(cell(x + dx, y + dy) == true)
              nNeighbors += 1;
            else
              nNeighbors += 0;
          }
        }
        if(cell(x, y) == true) // Make sure to not count self as a neighbor square
          nNeighbors -= 1;

        if(cell(x, y) == true)
        {
          // Cell survives
          if(nNeighbors == 2 || nNeighbors == 3)
            nextGen[x][y] = true;
          // Cell dies
          else
            nextGen[x][y] = false;
        }
        else
        {
          // Neighboring cells reproduce
          if(nNeighbors == 3)
            nextGen[x][y] = true;
        }
      }
    }
    cellVec = nextGen;
  }

  void display()
  {
    for(int j = 0; j < maxY; j++)
    {
      for(int i = 0; i < maxX; i++)
      {
        std::cout << (cell(i, j) ? "[]" : "  ");
      }
      std::cout << std::endl;
    }
  }
};

int main()
{
  srand(time(NULL));
  Grid game(36, 22);
  for(int i = 0; ; i++)
  {
    std::cout << "Round " << i << std::endl;
    game.display();
    //getch();
    usleep(1000*1000);
    game.update();
  }
}
