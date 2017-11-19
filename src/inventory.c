
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "../hdr/list.h"

void readInventory(){
  FILE *file = fopen("../txt/estoque.txt", "r");
  if(file == NULL) {
    initList();
    return;
  }
  char sBuff[255];
  float fBuff;
  int iBuff, i=0;
  Item *new;
  initList();
  while(fscanf(file, "%255[^\n]\n", sBuff) >= 0) {
    fscanf(file, "%f", &fBuff);
    fscanf(file, "%i", &iBuff);
    if(i==0) {
      /* I still don't know why it reads the same item twice,
      but now it only inserts it once, so problem fixed */
      new = newItem();
      setId(new, sBuff);
      setPrice(new, fBuff);
      setN(new, iBuff);
      insertList(new);
      i = 1;
    } else i = 0;
  }
  fclose(file);
}

void refreshInventory(){
  FILE *file = fopen("../txt/estoque.txt", "w");
  int i;
  for(i=0; i<listLen(); i++){
    if(getN(0) > 0){
      fprintf(file, "%s\n", getId(0));
      fprintf(file, "%7.2f\n", getPrice(0));
      fprintf(file, "%i\n", getN(0));
    }
    next();
  }
  fclose(file);
}
