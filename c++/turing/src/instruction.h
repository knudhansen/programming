#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include "types.h"

class Instruction;

class Action {
 private:
  int writeAction;
  moveAction_t moveAction;
  Instruction *nextInstruction;
 public:
  Action(void);
  Action(int writeAction, moveAction_t moveAction, Instruction *instruction);
  int getWriteAction(void);
  moveAction_t getMoveAction(void);
  Instruction *getNextInstruction(void);
};

class Instruction {
 private:
  Action *action0;
  Action *action1;
 public:
  Instruction(void);
  void setActions(Action *action0, Action *action1);
  Action *getAction(int value);
};

#endif
