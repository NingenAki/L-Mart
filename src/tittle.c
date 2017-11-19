#include <stdio.h>
#include "../hdr/box.h"
#include "../hdr/esc.h"

void boxPrintTittle(){
  int bs = getBoxSize();
  if(bs < 45){
    boxPrint("Lojas Estruturadas S/A", CENTER, TITTLE);
    return;
  }
  int i, j;
  char *tittle[] = {
    "▒▒╗      ▒▒▒╗   ▒▒▒╗ ▒▒▒▒▒╗ ▒▒▒▒▒▒╗ ▒▒▒▒▒▒▒▒╗",
    "▒▒║      ▒▒▒▒╗ ▒▒▒▒║▒▒╔══▒▒╗▒▒╔══▒▒╗╚══▒▒╔══╝",
    "▒▒║▒▒▒▒▒╗▒▒╔▒▒▒▒╔▒▒║▒▒▒▒▒▒▒║▒▒▒▒▒▒╔╝   ▒▒║   ",
    "▒▒║╚════╝▒▒║╚▒▒╔╝▒▒║▒▒╔══▒▒║▒▒╔══▒▒╗   ▒▒║   ",
    "▒▒▒▒▒▒▒╗ ▒▒║ ╚═╝ ▒▒║▒▒║  ▒▒║▒▒║  ▒▒║   ▒▒║   ",
    "╚══════╝ ╚═╝     ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝   ╚═╝   "
  };
  printf("%s", STR_DEFAULT);
  for(i=0; i<(sizeof(tittle)/sizeof(char *)); i++){
    printf("%s%s%s", BOX_CFG, BOX_V, STR_DEFAULT);
    for(j=0; j<(bs-45)/2; j++) printf(" ");
    printf("%s%s%s", TITTLE, tittle[i], STR_DEFAULT);
    for(j=(bs-(bs-45)/2-45); j>0; j--) printf(" ");
    printf("%s%s%s\n", BOX_CFG, BOX_V, STR_DEFAULT);
  }
}
