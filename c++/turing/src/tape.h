#ifndef TAPE_H
#define TAPE_H

#include "types.h"

#include "instruction.h"

class Cell {
 private:
  int value;
  Cell *cellToTheRight;
  Cell *cellToTheLeft;
 public:
  Cell(void);
  int getValue(void);
  Cell *getCellToTheRight(void);
  Cell *getCellToTheLeft(void);
  int  read(void);
  void write(int value);
};

class Tape {
 private:
  Cell *currentCell;
 public:
  Tape(void);
  void print(void);
  int  read(void);
  void write(int value);
  void move(moveAction_t moveAction);
};

#endif
