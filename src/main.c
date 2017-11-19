#include <stdio.h>
#include "../hdr/box.h"
#include "../hdr/esc.h"
#include "../hdr/getche.h"
#include "../hdr/inventory.h"
#include "../hdr/list.h"
#include "../hdr/manage.h"
#include "../hdr/tittle.h"
#include "../hdr/shop.h"

int main(void) {
  int key;
  int loop = 1;
  readInventory();
  while (loop != 0) {
    printf("%s%s", GO_TO_TOP, CLEAR);
    initBox(72, BOX_CFG);
    boxTop();
    boxMid();
    boxEnter();
    boxPrint("    Welcome to", LEFT, BODY);
    boxEnter();
    boxPrintTittle();
    boxEnter();
    boxEnter();
    boxPrint("'s': shop        ", RIGHT, BODY);
    boxPrint("'m': manage      ", RIGHT, BODY);
    boxPrint("'f': exit        ", RIGHT, BODY);
    boxEnter();
    boxMid();
    boxBot();
    key = getche();
    if(key == 's') shop();
    if(key == 'm') manage();
    if(key == 'f') loop = 0;
  }
  refreshInventory();
  destroy();
}
