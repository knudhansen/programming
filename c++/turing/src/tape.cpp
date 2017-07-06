#include "tape.h"

#include <stdlib.h>
#include <stdio.h>

#include "types.h"

#define TAPE_PRINT_WIDTH 10

Cell::Cell(void) {
  this->value = 0;
  this->cellToTheRight = NULL;
  this->cellToTheLeft = NULL;
}
int Cell::getValue(void) {
  return this->value;
}
Cell *Cell::getCellToTheRight(void) {
  if (cellToTheRight == NULL) {
    cellToTheRight = new Cell();
    cellToTheRight->cellToTheLeft = this;
  }
  return cellToTheRight;
}
Cell *Cell::getCellToTheLeft(void) {
  if (cellToTheLeft == NULL) {
    cellToTheLeft = new Cell();
    cellToTheLeft->cellToTheRight = this;
  }
  return cellToTheLeft;
}
int Cell::read(void) {
  return this->value;
}
void Cell::write(int value) {
  this->value = value;
}

Tape::Tape(void) {
  this->currentCell = new Cell();
}

void Tape::print(void) {
  Cell *cell = currentCell;
  int i;

  for (i = 0 ; i > -TAPE_PRINT_WIDTH; i--) {
    cell = cell->getCellToTheLeft();
  }

  printf(" ");
  for (int j = i; j < TAPE_PRINT_WIDTH; j++) {
    if (j != 0) {
      printf("    ");
    } else {
      printf(" v  ");
    }
  }
  printf("\n");
  printf("|");
  for (int j = i; j < TAPE_PRINT_WIDTH; j++) {
    if (j != 0) {
      printf(" %d |", cell->getValue());
    } else {
      printf("|%d||", cell->getValue());
    }
    cell = cell->getCellToTheRight();
  }
  printf("\n");
  printf(" ");
  for (int j = i; j < TAPE_PRINT_WIDTH; j++) {
    if (j != 0) {
      printf("    ");
    } else {
      printf(" ^  ");
    }
  }
  printf("\n");
}
int Tape::read(void) {
  return currentCell->read();
}
void Tape::write(int value) {
  currentCell->write(value);
}
void Tape::move(moveAction_t moveAction) {
  if (moveAction == MOVE_RIGHT) {
    currentCell = currentCell->getCellToTheRight();
  } else if (moveAction == MOVE_LEFT) {
    currentCell = currentCell->getCellToTheLeft();
  }
}
    
