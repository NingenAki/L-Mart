#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "../hdr/box.h"
#include "../hdr/cart.h"
#include "../hdr/esc.h"
#include "../hdr/getche.h"
#include "../hdr/list.h"
#include "../hdr/shop.h"
#include "../hdr/tittle.h"

void msg(const char *s){
  moveUp(7); // Move cursor seven lines up
  boxPrint(s, RIGHT, BODY);
  moveDown(7); // Brings it back down
  sleep(1); //Stops for 1 second
}

void printListLn(char *r, int a, int m, int i, char *s){
  int d = 1;
  boxPrint(r, a, s);
  printf("%s", GO_TO_S);
  moveRight(m);
  printf("%s%7.2f%s", s, getPrice(i), STR_DEFAULT);
  dropToNextLine(&d);
}

void printList(int size, int a){
  if(listLen() < 0) return;
  int len, i, n=0, m;
  char r[size+1];
  memset(r, '\0', size+1);
  if (listLen() >= 3) n++;
  if (listLen() >= 5) n++;
  if(a == LEFT) m = size + 1;
  else if(a == CENTER) m = (getBoxSize() + size)/2 + 1;
  else m = getBoxSize() - size - 7;
  for(i = -n; i<=n; i++){
    printf("%s", SAVE_POS);
    len = strlen(getId(i));
    if(len > size){
      memset(r, '.', size);
      strncpy(r, getId(i), size-3);
    }
    else {
      memset(r, ' ', size);
      strncpy(r, getId(i), len);
    }
    if(i != 0) {
      if(getN(i)>0) printListLn(r, a, m, i, LIST);
      else printListLn(r, a, m, i, LIST_INVALID);
    }
    else {
      if(getN(i)>0) printListLn(r, a, m, i, LIST_SELECT);
      else printListLn(r, a, m, i, LIST_SELECT_INVALID);
    }
  }
}

void shop(){
  int key;
  int loop = 1;
  initCart();
  while (loop != 0){
    initBox(72, BOX_CFG);
    printf("%s%s", GO_TO_TOP, CLEAR);
    boxTop();
    boxEnter();
    boxPrintTittle();
    boxEnter();
    boxMid();
    boxEnter();
    printList(20, LEFT);
    boxEnter();
    boxMid();
    boxPrint("'^': move up | 'v': move down | 'k': add to cart", CENTER, FOOTER);
    boxPrint("'m': show cart | ' ': hide cart", CENTER, FOOTER);
    boxPrint("'c': buy cart | 'a': empty cart", CENTER, FOOTER);
    boxPrint("'f': exit", CENTER, FOOTER);
    boxBot();
    printf(FOOTER);
    key = getche();
    printf(STR_DEFAULT);
    if(key == 27){ //esc codes
      if(getche()==91){ //arrows
        key = getche();
        if(key == 66) next(); //down
        if(key == 65) back(); //up
      }
    }
    if(key == 'k' && getN(0) > 0) {
      insertCart();
      msg("item added to cart");
    }
    if(key == 'c' && totalCart() > 0) {
      if(buyCart() == 0){
        emptyCart();
        msg("your txt folder is full");
      }
      else msg("you bought the cart");
    }
    if (key == 'm') printCart();
    if(key == 'a') {
      emptyCart();
      msg("your cart is now empty");
    }
    if(key == 'f') loop = 0;
  }
  emptyCart();
}
