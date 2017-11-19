#ifndef BOX_HEADER
  #define BOX_HEADER

  #define LEFT -1
  #define CENTER 0
  #define RIGHT 1

  #define BOX_H "═"
  #define BOX_V "║"
  #define BOX_DR "╔"
  #define BOX_DL "╗"
  #define BOX_UR "╚"
  #define BOX_UL "╝"
  #define BOX_VR "╠"
  #define BOX_DH "╦"
  #define BOX_VL "╣"
  #define BOX_UH "╩"
  #define BOX_VH "╬"

  void initBox(int size, char *boxCfg);
  void boxEnter();
  void boxTop();
  void boxMid();
  void boxBot();
  void boxPrint(const char *s, int align, char *strcfg);
  int getBoxSize();
#endif
