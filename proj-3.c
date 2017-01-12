// Justin Chen
// CSE330
// Project 3

#include "sem.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

SemStruct *ReadSem, *WriteSem, *MutexSem; //initialize to 0,0,1
//int buffer[4];  //Bsize = 4
TCB_t* RunQ;
int rCount = 0, wCount = 0, rwCount = 0, wwCount = 0;  //count of Read, Write and waiting Read and Write
int globalcount = 0;
//Using the semaphores you have implemented, implement the Readers and Writers Problem.
// Design how you want to get the processes to print, such that you can see
//which process if doing what (reading, writing, waiting, or in the "remainder section"
//etc)
//Multiples proccessors can read simultaniously but only 1 proccessor can write at a time
//Read-Write problem has several variations:
//  - First reader-writer problem = no reader be kept waiting unless writer has permission
//    to use shared object. (no readers wait for other readers)
//  - Second reader-writer problem = once a writer is ready, the writer performs its writer
//    as soon as possible. (If a writer is ready, no new readers may start reading)
//  - Third reader-writer prolem

 void Reader1();
 void Reader2();
 void Reader3();
 void Reader4();
 void Writer1();
 void Writer2();

int main()  {

  WriteSem = malloc(sizeof(struct SemStruct));
  ReadSem = malloc(sizeof(struct SemStruct));
  MutexSem = malloc(sizeof(struct SemStruct));

  InitQueue(&RunQ);
  InitSem(WriteSem, 1); //initialize the WriteSem to 1 b/c there can only be 1 write operator at a time
  InitSem(ReadSem, 4);  //initialize the ReadSem to # of ReadSem because there can be 4 read operators at the same time
  InitSem(MutexSem, 1); //initialize the MutexSem to 1

   start_thread(Writer1);
   start_thread(Reader1);
   start_thread(Reader2);
   start_thread(Writer2);
   start_thread(Reader3);
   start_thread(Reader4);

   run();
  return 0;
}

void Reader1() {
  while(1) {
    //Reader Entry
    P(MutexSem);
    if(wwCount > 0 || wCount > 0) {
      rwCount++;
      V(MutexSem);
      P(ReadSem);
      rwCount--;
    }
    rCount++;
    if(rwCount>0)
      V(ReadSem);
    else
      V(MutexSem);

    printf("Reader1 reads globalcount %d\n", globalcount);
    sleep(1);

    //Reader Exit
    P(MutexSem);
    rCount--;
    if(rCount == 0 && wwCount > 0)
      V(WriteSem);
    else
      V(MutexSem);
  }
}

void Reader2() {
  while(1) {
    //Reader Entry
    P(MutexSem);
    if(wwCount > 0 || wCount > 0) {
      rwCount++;
      V(MutexSem);
      P(ReadSem);
      rwCount--;
    }
    rCount++;
    if(rwCount>0)
      V(ReadSem);
    else
      V(MutexSem);

    printf("Reader2 reads globalcount %d\n", globalcount);
    sleep(1);

    //Reader Exit
    P(MutexSem);
    rCount--;
    if(rCount == 0 && wwCount > 0)
      V(WriteSem);
    else
      V(MutexSem);
  }
}

void Reader3() {
  while(1) {
    //Reader Entry
    P(MutexSem);
    if(wwCount > 0 || wCount > 0) {
      rwCount++;
      V(MutexSem);
      P(ReadSem);
      rwCount--;
    }
    rCount++;
    if(rwCount>0)
      V(ReadSem);
    else
      V(MutexSem);

    printf("Reader3 reads globalcount %d\n", globalcount);
    sleep(1);

    //Reader Exit
    P(MutexSem);
    rCount--;
    if(rCount == 0 && wwCount > 0)
      V(WriteSem);
    else
      V(MutexSem);
  }
}

void Reader4() {
  while(1) {
    //Reader Entry
    P(MutexSem);
    if(wwCount > 0 || wCount > 0) {
      rwCount++;
      V(MutexSem);
      P(ReadSem);
      rwCount--;
    }
    rCount++;
    if(rwCount>0)
      V(ReadSem);
    else
      V(MutexSem);

    printf("Reader4 reads globalcount %d\n", globalcount);
    sleep(1);

    //Reader Exit
    P(MutexSem);
    rCount--;
    if(rCount == 0 && wwCount > 0)
      V(WriteSem);
    else
      V(MutexSem);
  }
}

void Writer1() {
  while(1) {
    //Writer Entry
    P(MutexSem);
    if(rCount>0 || wCount>0)  {
      wwCount++;
      V(MutexSem);
      P(WriteSem);
      wwCount--;
    }
    wCount++;
    V(MutexSem);

    printf("Writer1 adds 2 to %d =", globalcount);
    globalcount = globalcount + 2;
    printf(" %d\n", globalcount);
    sleep(1);

    //Writer Exists
    P(MutexSem);
      wCount--;
      if(rwCount>0) {
        V(ReadSem);
      } else if(wwCount>0) {
        V(WriteSem);
      }
  }
}

void Writer2() {
  while(1) {
    //Writer Entry
    P(MutexSem);
    if(rCount>0 || wCount>0)  {
      wwCount++;
      V(MutexSem);
      P(WriteSem);
      wwCount--;
    }
    wCount++;
    V(MutexSem);

    printf("Writer2 adds 10 to %d =", globalcount);
    globalcount = globalcount + 10;
    printf(" %d\n", globalcount);
    sleep(1);

    //Writer Exists
    P(MutexSem);
      wCount--;
      if(rwCount>0) {
        V(ReadSem);
      } else if(wwCount>0) {
        V(WriteSem);
      }
  }
}
