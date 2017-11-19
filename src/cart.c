#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../hdr/box.h"
#include "../hdr/esc.h"
#include "../hdr/getche.h"
#include "../hdr/list.h"

typedef struct node{
  struct node *next;
  Item *item;
}Node;

Node *cart;

void initCart(){
  cart = NULL;
}

void insertCart(){
  Node *new = (Node *)malloc(sizeof(Node)), *p = cart, *q;
  new->item = newItem();
  setId(new->item, getId(0));
  setPrice(new->item, getPrice(0));
  setN(new->item, 1);
  setN(getItem(), getN(0)-1);
  new->next = NULL;

  // Case empty
  if(cart == NULL){
    cart = new;
    return;
  }
  while(p != NULL){
    /* breaks the loop when it finds something that should be after new */
    if(strcmp(new->item->id, p->item->id) < 0){
      new->next = p;
      if(p == cart){
        /* here we're actually inserting first, so we don't need to worry with what is behind */
        cart = new;
        return;
      }
      break;
    }

    /* If found something with the same id we just add to it, discarting the new->price, if they were different the first to be added to the cart will be baseline */
    if(strcmp(new->item->id, p->item->id) == 0){
      free(new->item->id);
      free(new->item);
      free(new);
      if(p->item->n < 99) setN(p->item, p->item->n + 1);
      else setN(getItem(), getN(0)+1);
      return;
    }
    p = p->next;
  }
  //we attach that whitch is before
  q = cart;
  while(q->next != p) q = q->next;
  q->next = new;
}

float totalCart(){
  float r = 0;
  Node *p = cart;
  while(p != NULL){
    r += p->item->price * p->item->n;
    p = p->next;
  }
  return r;
}

int buyCart(){
  char filename[] = "../txt/compra00.txt";
  int i = 1;
  Node *p;
  // Check to find a filename not in use
  FILE *file = fopen(filename, "r");
  while(file != NULL && i < 100){
    fclose(file);
    filename[13] = i/10 + '0';
    filename[14] = i%10 + '0';
    file = fopen(filename, "r");
    i++;
  }
  if(i==100 && file != NULL){
    //filename: "../txt/compra99.txt"
    fclose(file);
    return 0;
  }
  file = fopen(filename, "w");
  while(cart != NULL) {
    fprintf(file, "%s\n", cart->item->id);
    fprintf(file, "        %4ix ", cart->item->n);
    fprintf(file, "%7.2f\n", cart->item->price);
    p = cart;
    cart = cart->next;
    free(p->item->id);
    free(p->item);
    free(p);
  }
  fprintf(file, "\nTOTAL: %.2f\n", totalCart());
  fclose(file);
  return 1;
}

// Popup with your cart info
void printCart(){
  Node *p;
  int loop = 1, i;
  moveUp(12);
  moveRight(25);
  printf("%s", SAVE_POS);
  initBox(26, BOX_CFG);
  while(loop != 0){
    int len, d = 1, size = 14;
    char r[size+1];
    memset(r, '\0', size+1);
    boxTop();
    dropToNextLine(&d);
    boxPrint("YOUR CART", CENTER, TITTLE);
    dropToNextLine(&d);
    boxMid();
    p = cart;
    while(p != NULL){
      len = strlen(p->item->id);
      if(len > size){
        memset(r, '.', size);
        strncpy(r, p->item->id, size-3);
      }
      else {
        memset(r, ' ', size);
        strncpy(r, p->item->id, len);
      }
      dropToNextLine(&d);
      boxPrint(r, LEFT, LIST);
      climbBack(&d);
      moveRight(size+1);
      printf("%s %2ix%7.2f%s", LIST,  p->item->n, p->item->price, STR_DEFAULT);
      p = p->next;
    }
    dropToNextLine(&d);
    boxEnter();
    dropToNextLine(&d);
    boxPrint("TOTAL:", LEFT, FOOTER);
    climbBack(&d);
    moveRight(8);
    printf("%s%17.2f%s", FOOTER,  totalCart(), STR_DEFAULT);
    dropToNextLine(&d);
    boxBot();
    if(getche() == ' ') loop = 0;
  }
}

void emptyCart(){
  Node *p;
  Item *s;
  while(cart != NULL) {
    s = searchItem(cart->item->id);
    setN(s, s->n + cart->item->n);
    p = cart;
    cart = cart->next;
    free(p->item->id);
    free(p->item);
    free(p);
  }
}
