#include "threads.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct SemStruct  {
  //initializes a value field and queue of TCBs
  int value;
  TCB_t *queue;
}SemStruct;

void InitSem(SemStruct *seminput, int num) {  //initializes semaphore
  InitQueue(&(seminput->queue));  //initializes queue inside seminput
  seminput->value = num; // sets value to num
}
//Wait
void P(SemStruct *seminput) { //decrements the semaphore, if val < 0, blocks the process in the queue associated
  seminput->value--;  // decrements by 1
  if(seminput->value < 0) {
    TCB_t *temp = DelQueue(&RunQ); //deletes node from RunQ and sets to temp
    AddQueue(&(seminput->queue), temp); //adds temp to Semaphore Queue
    swapcontext(&(temp->context),&(RunQ->context));  // swap from one thread to next
    //block runQ
  }
}
//signal
void V(SemStruct *seminput) { //increments the semaphore, if val = 0 || neg, takes a PCB out of the semaphore queue and puts it in the run queue
  seminput->value++;  // increments by 1
    if(seminput->value <= 0)  {
      TCB_t* temp = DelQueue(&(seminput->queue));  // takes PCB out of semaphoreQ
      AddQueue(&RunQ, temp);  // adds the PCB to RunQ
    }
  yield();  // yields to the next possible process
}
