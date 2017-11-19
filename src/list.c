#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../hdr/list.h"

typedef struct node{
  struct node *next, *back;
  Item *item;
}Node;

Node *curr;

Item *newItem(){
  char *s = "Stuff";
  Item *new = (Item *)malloc(sizeof(Item));
  new->id = (char *)malloc(sizeof(s));
  strcpy(new->id, s);
  new->price = 1.99;
  new->n = 1;
  return new;
}

void setId(Item *item, char *s){
  free (item->id);
  item->id = (char *)malloc(sizeof(s));
  strcpy(item->id, s);
}

void setPrice(Item *item, float f){
  if(f <= 0) item->price = 0.01;
  else if(f >= 10000) item->price = 9999.99;
  else item->price = f;
}

void setN(Item *item, int i){
  if(i<=0) item->n = 0;
  else if(i>=1000) item->n = 999;
  else item->n = i;
}

char *getId(int i){
  if(i == -2) return curr->back->back->item->id;
  if(i == -1) return curr->back->item->id;
  if(i == 0) return curr->item->id;
  if(i == 1) return curr->next->item->id;
  if(i == 2) return curr->next->next->item->id;
  return NULL;
}

float getPrice(int i){
  if(i == -2) return curr->back->back->item->price;
  if(i == -1) return curr->back->item->price;
  if(i == 0) return curr->item->price;
  if(i == 1) return curr->next->item->price;
  if(i == 2) return curr->next->next->item->price;
  return 0;
}

int getN(int i){
  if(i == -2) return curr->back->back->item->n;
  if(i == -1) return curr->back->item->n;
  if(i == 0) return curr->item->n;
  if(i == 1) return curr->next->item->n;
  if(i == 2) return curr->next->next->item->n;
  return 0;
}

void initList (){
  curr = NULL;
}

void insertList(Item *item){
  Node *new = (Node *)malloc(sizeof(Node));
  new->item = item;
  if(curr == NULL){
    new->next = new;
    new->back = new;
    curr = new;
    return;
  }
  new->next = curr;
  new->back = curr->back;
  curr->back->next = new;
  curr->back = new;
}

Item *getItem(){
  if(curr != NULL)return curr->item;
  return NULL;
}

Item *searchItem(char *id){
  if(curr == NULL) return NULL;
  if(strcmp(id, getId(0)) == 0) return curr->item;
  Node *p = curr->next;
  while (p != curr){
    if(strcmp(id, p->item->id) == 0) return p->item;
    p = p->next;
  }
  return NULL;
}

int listLen(){
  if(curr == NULL) return 0;
  int len = 1;
  Node *p = curr;
  while (p->next != curr){
    len++;
    p = p->next;
  }
  return len;
}

void back(){
  if(curr == NULL) return;
  curr = curr->back;
}

void next(){
  if(curr == NULL) return;
  curr = curr->next;
}

void destroy() {
  if(curr == NULL) return;
  Node *p = curr->next;
  while(p != curr){
    free(p->item->id);
    free(p->item);
    p = p->next;
    free(p->back);
  }
  free(p->item->id);
  free(p->item);
  free(p);
  curr = NULL;
}
