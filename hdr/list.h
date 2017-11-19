#ifndef LIST_HEADER
  #define LIST_HEADER

  typedef struct item{
    char *id;
    float price;
    int n;
  }Item;

  Item *newItem();
  void setId(Item *item, char *s);
  void setPrice(Item *item, float f);
  void setN(Item *item, int i);
  char *getId(int i);
  float getPrice(int i);
  int getN(int i);

  void initList ();
  void insertList(Item *item);
  Item *getItem();
  Item *searchItem(char *id);
  int listLen();
  void back();
  void next();
  void destroy();
#endif
