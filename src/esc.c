#include <stdio.h>
#include "../hdr/esc.h"

#define MOVE_UP "\033[F"
#define MOVE_DN "\033[E"
#define MOVE_RG "\033[C"
#define DROP "\033[B"

void dropToNextLine(int *d){
  int i;
  printf("%s", GO_TO_S);
  for(i=0;i<*d;i++) printf("%s", DROP);
  *d = *d + 1;
}

void climbBack(int *d){
  int i;
  *d = *d - 1;
  printf("%s", GO_TO_S);
  for(i=0;i<*d;i++) printf("%s", DROP);
  *d = *d + 1;
}

void moveUp(int d){
  int i;
  for(i=0;i<d;i++) printf("%s", MOVE_UP);
}

void moveDown(int d){
  int i;
  for(i=0;i<d;i++) printf("%s", MOVE_UP);
}

void moveRight(int d){
  int i;
  for(i=0;i<d;i++) printf("%s", MOVE_RG);
}
