//
// Created by Sebastian Bond on 09/13/2019.
//

#ifndef PROJECT6_GETCH_H
#define PROJECT6_GETCH_H

//(personal: to have getch())//
#ifdef _MSC_VER //visual c++ needs getch correctly defined, and _MSC_VER is defined under visual c++ only!
#include <conio.h> //getch
#define getch() _getch()
#else
// https://stackoverflow.com/questions/7469139/what-is-the-equivalent-to-getch-getche-in-linux
#include <unistd.h>
#include <termios.h>
#include <cstring>

char getch(void)
{
  char buf = 0;
  struct termios old;
  memset(&old, 0, sizeof(termios));
  fflush(stdout);
  if(tcgetattr(0, &old) < 0)
    perror("tcsetattr()");
  old.c_lflag &= ~ICANON;
  old.c_lflag &= ~ECHO;
  old.c_cc[VMIN] = 1;
  old.c_cc[VTIME] = 0;
  if(tcsetattr(0, TCSANOW, &old) < 0)
    perror("tcsetattr ICANON");
  if(read(0, &buf, 1) < 0)
    perror("read()");
  old.c_lflag |= ICANON;
  old.c_lflag |= ECHO;
  if(tcsetattr(0, TCSADRAIN, &old) < 0)
    perror("tcsetattr ~ICANON");
  printf("%c\n", buf);
  return buf;
}
#endif
//                           //

#endif // PROJECT6_GETCH_H
