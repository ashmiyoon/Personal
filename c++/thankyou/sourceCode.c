#include <curses.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

const int nColors = 6;
const char* filledLetters = "THANKYOU@XOXO@";
const char* blankLetters  = ".',<-`~*>1\"";
//const char* blankLetters  = "0123456789abcd";

// Dictates the period of the sine wave moving across the screen
// 1.0 means one period per message length
const float periodsPerScreen = 0.8;
// Dictates the rate at which the sine wave shifts across the screen
// 1.0 means that 1 frame shifts the sine wave the equivalent of 1 x unit
const float movesPerFrame = 4.0;

const int nMessageLines = 22;
const char* message[nMessageLines] =
{
  "                                                               ",
  "  ##########  ##      ##      ###      ###     ##  ##     ##   ",
  "      ##      ##      ##     ## ##     ####    ##  ##   ###    ",
  "      ##      ##      ##    ##   ##    ## ##   ##  ##  ##      ",
  "      ##      ##########   #########   ##  ##  ##  ####        ",
  "      ##      ##      ##  ##       ##  ##   ## ##  ##  ##      ",
  "      ##      ##      ## ##         ## ##    ####  ##   ###    ",
  "      ##      ##      ####           ####     ###  ##     ##   ",
  "                                                               ",
  "        ##        ##   ######     ##        ##  ########       ",
  "          ##    ##   ###    ###   ##        ##   ######        ",
  "           ##  ##   ##        ##  ##        ##    ####         ",
  "            ####    ##        ##  ##        ##     ##          ",
  "             ##     ##        ##  ##        ##                 ",
  "             ##      ###    ###    ###    ###     ####         ",
  "             ##        ######        ######       ####         ",
  "                                                               ",
  "                         +---F-R-O-M--+                        ",
  "                         |Brandon|Yoon|                        ",
  "                         +------------+                        ",
  "                                                               ",
  "             (Press q to quit, press space to pause)           ",
};

char pauseFlag = 0x00;

void startCurses();

int main()
{
  startCurses();
  
  const int screenWidth = strlen(message[0]);
  const int screenHeight = sizeof(message) / sizeof(message[0]);

  for(int t = 0; ; t++)
  {
    for(int i = 0; i < screenHeight; i++)
    {
      int colorId = 7;
      char printedLtr = ' ';
      for(int j = 0; j < screenWidth; j++)
      {
        if(message[i][j] == ' ')
        {
          if(i >=
            round(screenHeight *
              0.5 * (1 + sin(2*3.1416*(j+movesPerFrame*t)*periodsPerScreen/screenWidth))
                 )
            )
          {
            printedLtr = filledLetters[(j + i + t) % strlen(filledLetters)];
            colorId = 8 + (i / 2) % nColors;
          }
          else
          {
            printedLtr =  blankLetters[(
              (int)round(strlen(blankLetters) * cos(j + 1.5*t) + strlen(blankLetters)/2) +
              (int)round(strlen(blankLetters) * sin(i + t))
              ) % strlen(blankLetters)];
            //printedLtr = ' ';
            colorId = 13 - (i / 2) % nColors;
            //colorId = 7;
          }
        }
        else if(message[i][j] == '#')
        {
          colorId = (j + i + t) % nColors + 1;
          printedLtr = filledLetters[(j + i + t) % strlen(filledLetters)];
        }
        else
        {
          printedLtr = message[i][j];
          colorId = 7;
        }
        attron(COLOR_PAIR(colorId));
        mvaddch(i, j, printedLtr);
        attroff(COLOR_PAIR(colorId));
      }
    }
    refresh();
    usleep(1000 * 33);
    char userInput = getch();
    if(userInput == 'q')
    {
      break;
    }
    else if(userInput == ' ')
    {
      if(pauseFlag)
      {
        nodelay(stdscr, TRUE);
        pauseFlag = 0x00;
      }
      else
      {
        nodelay(stdscr, FALSE);
        pauseFlag = 0xFF;
      }
    }
  }
  endwin();
}

void startCurses()
{
  initscr();
  cbreak();
  noecho();
  clear();
  nodelay(stdscr, TRUE);

  start_color();
  init_pair(1, COLOR_BLACK, COLOR_RED);
  init_pair(2, COLOR_BLACK, COLOR_YELLOW);
  init_pair(3, COLOR_BLACK, COLOR_GREEN);
  init_pair(4, COLOR_BLACK, COLOR_CYAN);
  init_pair(5, COLOR_BLACK, COLOR_BLUE);
  init_pair(6, COLOR_BLACK, COLOR_MAGENTA);

  init_pair(7, COLOR_WHITE, COLOR_BLACK);

  init_pair(8,  COLOR_RED,     COLOR_BLACK);
  init_pair(9,  COLOR_YELLOW,  COLOR_BLACK);
  init_pair(10, COLOR_GREEN,   COLOR_BLACK);
  init_pair(11, COLOR_CYAN,    COLOR_BLACK);
  init_pair(12, COLOR_BLUE,    COLOR_BLACK);
  init_pair(13, COLOR_MAGENTA, COLOR_BLACK);
}
