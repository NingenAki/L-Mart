#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

/* This snippet mimics Windows <conio.h> getche() for Linux */

int getche(void)
{
  struct termios oldattr, newattr;
  int ch;
  tcgetattr( STDIN_FILENO, &oldattr ); // Capture current configurations
  newattr = oldattr;
  newattr.c_lflag &= ~( ICANON | ECHO); // Added knock down keybuffer
  tcsetattr( STDIN_FILENO, TCSANOW, &newattr ); // Sets new configs
  system("stty -echo"); // Disables Echo
  ch = getchar();
  system("stty echo"); // Enables Echo
  tcsetattr( STDIN_FILENO, TCSANOW, &oldattr ); // Return to old configs
  return ch;
}
