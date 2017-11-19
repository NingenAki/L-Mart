#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../hdr/box.h"
#include "../hdr/esc.h"
#include "../hdr/getche.h"
#include "../hdr/list.h"
#include "../hdr/manage.h"
#include "../hdr/tittle.h"

int section = 0, i = 0;
int max=0;

typedef struct node{
  Item *item;
  int i;
  struct node *next;
}Node;

Node *list;

void populateList(){
  Node *new;
  Item *curr = getItem();
  list = NULL;
  if(curr == NULL) return;
  do{
    new = (Node *)malloc(sizeof(Node));
    new->item = getItem();
    new->i = max;
    new->next = list;
    list = new;
    max++;
    next();
  }while (curr != getItem());
}

void destroyList(){
  Node *p;
  while(list!=NULL) {
    p = list;
    list = list->next;
    free(p);
  }
}

void boxPrintListLn(Node *p, char *r, int a, int m, int n, char *s1, const char *s2, const char *s3){
  boxPrint(r, a, s1);
  moveUp(1);
  moveRight(m);
  printf("%s%7.2f%s\n",  s2, p->item->price, STR_DEFAULT);
  moveUp(1);
  moveRight(n);
  printf("%s%4i%s\n", s3, p->item->n, STR_DEFAULT);
}

void boxPrintList(int size, int a){
  if(listLen() < 0) return;
  int len, n, m;
  char r[size+1];
  Node *p = list;
  if(list == NULL) return;
  memset(r, '\0', size+1);
  m = (getBoxSize()-8)/2+1;
  n = getBoxSize() - 3;
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
    if(section == 0) {
      if(p->i == i) boxPrintListLn(p, r, a, m, n, LIST_SELECT, LIST_INVALID, LIST_INVALID);
      else boxPrintListLn(p, r, a, m, n, LIST, LIST_INVALID, LIST_INVALID);
    }
    else if(section == 1){
      if(p->i == i) boxPrintListLn(p, r, a, m, n, LIST_INVALID, LIST_SELECT, LIST_INVALID);
      else boxPrintListLn(p, r, a, m, n, LIST_INVALID, LIST, LIST_INVALID);
    }
    else{
      if(p->i == i) boxPrintListLn(p, r, a, m, n, LIST_INVALID, LIST_INVALID, LIST_SELECT);
      else boxPrintListLn(p, r, a, m, n, LIST_INVALID, LIST_INVALID, LIST);
    }
    p = p->next;
  }
}

void popUp(const char *s){
  int d = 1;
  dropToNextLine(&d);
  boxPrint(s, CENTER, TITTLE);
  dropToNextLine(&d);
  boxMid();
  dropToNextLine(&d);
  boxEnter();
  dropToNextLine(&d);
  boxBot();
  d--;
  climbBack(&d);
  moveRight(1);
  printf("%s", FOOTER);
}

void set(Node *p){
  float f;
  int n;
  char s[33];
  memset(s, 0, 33);
  moveUp(13);
  moveRight(25);
  printf("%s", SAVE_POS);
  initBox(32, BOX_CFG);
  boxTop();
  if(section == 1) {
    popUp("Set New Price");
    scanf("%f", &f);
    setPrice(p->item, f);
  }
  if(section == 2) {
    popUp("Set New Quantity");
    scanf("%i", &n);
    setN(p->item, n);
  }
  if(section == 0){
    popUp("Set New Id");
    scanf("%32[^\n]s", s);
    setId(p->item, s);
  }
}

void manage(){
  Node *p;
  int key;
  int loop = 1;
  populateList();
  while (loop != 0){
    initBox(72, BOX_CFG);
    printf("%s%s", GO_TO_TOP, CLEAR);
    boxTop();
    boxEnter();
    boxPrintTittle();
    boxPrint("the manager's section     ", RIGHT, TITTLE);
    boxEnter();
    boxMid();
    boxEnter();
    boxPrintList(20, LEFT);
    boxEnter();
    boxMid();
    boxPrint("'^': move up | 'v': move down", CENTER, FOOTER);
    boxPrint("'>': move right | '<': move left", CENTER, FOOTER);
    boxPrint("'a': add one | 't': take one | 's': set", CENTER, FOOTER);
    boxPrint("'n': new item", CENTER, FOOTER);
    boxPrint("'f': exit", CENTER, FOOTER);
    boxBot();
    p = list;
    while(p->i!=i)p = p->next;
    printf("%s", FOOTER);
    key = getche();
    printf("%s", STR_DEFAULT);
    if(key == 27){ //esc codes
      if(getche()==91){ //arrows
        key = getche();
        if(key == 66) i--; //down
        if(key == 65) i++; //up
        if(key == 68 && section > 0) section--; //left
        if(key == 67 && section < 2) section++; //right
        if(i<0) i = max-1;
        if(i==max) i = 0;
      }
    }
    if(key == 'a') {
      if(section == 1) setPrice(p->item, p->item->price +1);
      if(section == 2) setN(p->item, p->item->n +1);
    }
    if(key == 't') {
      if(section == 1) setPrice(p->item, p->item->price -1);
      if(section == 2) setN(p->item, p->item->n -1);
    }
    if(key == 'n') {
      insertList(newItem());
      back();
      Node *new = (Node *)malloc(sizeof(Node));
      new->item = getItem();
      new->i = max;
      new->next = list;
      list = new;
      max++;
      next();
    }
    if(key == 'f') loop = 0;
    if(key == 's') set(p);
  }
  max = 0;
  i = 0;
  destroyList();
}
