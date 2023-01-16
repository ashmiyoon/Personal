#include <curses.h>

class Wordle {
public:
  int cycle;
  char grid[6][5];

  Wordle(const char* word)
  : word(word),
    cycle(0)
  {
    ;
  }

  void write()
  {
    //
  }
};

void startCurses()
{
  initscr();
  cbreak();
  noecho();
  clear();
}

int main()
{
  ;
}
