#include "instruction.h"

#include <stdlib.h>

Action::Action(void){
}
Action::Action(int writeAction, moveAction_t moveAction, Instruction *instruction) {
  this->writeAction = writeAction;
  this->moveAction = moveAction;
  this->nextInstruction = instruction;
}
int Action::getWriteAction(void) {
  return this->writeAction;
}
moveAction_t Action::getMoveAction(void) {
  return this->moveAction;
}
Instruction *Action::getNextInstruction(void) {
  return this->nextInstruction;
}

Instruction::Instruction(void) {
}
void Instruction::setActions(Action *action0, Action *action1) {
  this->action0 = action0;
  this->action1 = action1;
}
Action *Instruction::getAction(int value) {
  if (value == 0) {
    return this->action0;
  } else if (value == 1) {
    return this->action1;
  }
  return NULL;
}
