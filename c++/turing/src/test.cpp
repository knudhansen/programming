#include <stdlib.h>
#include <stdio.h>

#include "types.h"

#include "instruction.h"
#include "tape.h"

Instruction *executeInstruction(Tape *tape, Instruction *instruction);
Instruction *executeAction(Tape *tape, Action *action);

int main (int argc, char *argv[]) {

  Tape *tape = new Tape();

  Instruction *instruction0 = NULL;
  Instruction *instruction1 = new Instruction();
  Instruction *instruction2 = new Instruction();

  instruction1->setActions(new Action(1, MOVE_LEFT, instruction2),new Action(1, MOVE_RIGHT, instruction0));
  instruction2->setActions(new Action(1, MOVE_LEFT, instruction0),new Action(1, MOVE_RIGHT, instruction0));

  Instruction *instruction = instruction1;

  tape->print();
  while ( NULL != (instruction = executeInstruction(tape, instruction)) ) {
    tape->print();
  }
  printf("final state:\n");
  tape->print();
}

Instruction *executeInstruction(Tape *tape, Instruction *instruction) {
  return executeAction(tape, instruction->getAction(tape->read()));
}

Instruction *executeAction(Tape *tape, Action *action) {
  tape->write(action->getWriteAction());
  tape->move(action->getMoveAction());
  return action->getNextInstruction();
}
