#ifndef ESC_HEADER
  #define ESC_HEADER
  // ESC codes used for adding color and manipulating the output

  #define GO_TO_TOP "\033[H" // Moves cursor to top of visible terminal
  #define CLEAR "\033[0J" // Clears output after cursor
  #define SAVE_POS "\033[s" // Saves cursor position
  #define GO_TO_S "\033[u" // Moves cursor to saved position

  #define STR_DEFAULT "\033[0m" // Clears text formatting

  #define BOX_CFG "\033[34;1m" // Turns text bright blue
  #define TITTLE "\033[36;1m" // Turns text bright cyan
  #define BODY ""
  #define LIST ""
  #define LIST_INVALID "\033[30;1m" // Turns text grey
  #define LIST_SELECT "\033[1m\033[4m\033[46m" // Makes text bold, underlined and turns text background cyan
  #define LIST_SELECT_INVALID "\033[4m\033[40;1m\033[31m" // Makes text bodl, underlined, turns it red and turns text background grey
  #define FOOTER "\033[34;1m" // Turns text bright blue

  // Functions that move cursor, based on esc codes
  void dropToNextLine(int *d);
  void climbBack(int *d);
  void moveUp(int d);
  void moveDown(int d);
  void moveRight(int d);
#endif
