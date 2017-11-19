#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../hdr/box.h"

#define STR_DEFAULT "\033[0m" // Esc code for clearing text formatting

char *BOX_CFG;// We expect it to be an esc code formatting the box lines
int BOX_SIZE; // The inner lenght of a line of the box
int emptySpaces; // Number of spaces left to fill the box

void initBox(int size, char *boxCfg){
	if(size>=8) BOX_SIZE = size;
	else BOX_SIZE = 72;
	emptySpaces = BOX_SIZE;
	BOX_CFG = boxCfg;
}

/* Function so we don't give external code direct access to this variable */
int getBoxSize(){
	return BOX_SIZE;
}

void fillBox(){
	printf("%s", STR_DEFAULT);
	while(emptySpaces>0) {
	  printf(" ");
	  emptySpaces--;
	}
	emptySpaces = BOX_SIZE;
}

// Prints an empty line of the box: "║     ║"
void boxEnter() {
	printf("%s%s%s", STR_DEFAULT, BOX_CFG, BOX_V);
	fillBox();
	printf("%s%s%s\n", BOX_CFG, BOX_V, STR_DEFAULT);
}

// Prints top of the box: "╔═════╗"
void boxTop() {
	printf("%s%s%s", STR_DEFAULT, BOX_CFG, BOX_DR);
	int i;
	for(i=0; i<BOX_SIZE; i++) printf(BOX_H);
	printf("%s%s\n", BOX_DL, STR_DEFAULT);
}

// Prints mid line of the box: "╠═════╣"
void boxMid() {
	printf("%s%s%s", STR_DEFAULT, BOX_CFG, BOX_VR);
	int i;
	for(i=0; i<BOX_SIZE; i++) printf(BOX_H);
	printf("%s%s\n", BOX_VL, STR_DEFAULT);
}

// Prints bottom of the box: "╚═════╝"
void boxBot() {
	printf("%s%s%s", STR_DEFAULT, BOX_CFG, BOX_UR);
	int i;
	for(i=0; i<BOX_SIZE; i++) printf(BOX_H);
	printf("%s%s\n", BOX_UL, STR_DEFAULT);
}

/*
Prints text within a line of the box "║txt  ║ depending on align it can be to the left as shown, centralized "║ txt ║" or to the right "║  txt║", its values are defined on header
*/
void boxPrint(const char *s, int align, char *strcfg){
	/* strcfg should be esc code for formatting the inner text */
	printf("%s%s%s", STR_DEFAULT, BOX_CFG, BOX_V);

	/* Checks if we'll need another line and calls it recursively */
	if(strlen(s)>BOX_SIZE){
		char aux[BOX_SIZE+1], aux2[strlen(s)-BOX_SIZE];
		memset(aux, '\0', BOX_SIZE+1);
		strncpy(aux, s, BOX_SIZE);
		printf("%s%s%s", STR_DEFAULT, strcfg, aux);
		printf("%s%s%s\n", STR_DEFAULT, BOX_CFG, BOX_V);
		boxPrint(strcpy(aux2, s + BOX_SIZE), align, strcfg);
		return;
	}

  /* Getting here means our string will fit in a line */
	if(align == CENTER) {
		emptySpaces = BOX_SIZE - strlen(s);
		int md = emptySpaces/2;
		printf("%s", STR_DEFAULT);
		while(emptySpaces>md) {
		  printf(" ");
		  emptySpaces--;
		}
		printf("%s%s", strcfg, s);
		fillBox();
		printf("%s%s%s\n", BOX_CFG, BOX_V, STR_DEFAULT);
		return;
	}
	if(align == LEFT){
		emptySpaces = BOX_SIZE - strlen(s);
		printf("%s%s%s", STR_DEFAULT, strcfg, s);
		fillBox();
		printf("%s%s%s\n", BOX_CFG, BOX_V, STR_DEFAULT);
		return;
	}
	// here align == RIGHT as it's the only one left
	emptySpaces = BOX_SIZE - strlen(s);
	fillBox();
	printf("%s%s%s%s%s%s\n",strcfg, s, STR_DEFAULT, BOX_CFG, BOX_V, STR_DEFAULT);
}
