#include "q.h"
extern TCB_t *RunQ;

void start_thread(void (*function)(void))
{ /* begin pseudo code
     allocate a stack (via malloc) of a certain size (choose 8192)
     allocate a TCB (via malloc)
     call init_TCB with appropriate arguments
     call addQ to add this TCB into the “RunQ” which is a global header pointer
  	 end pseudo code
*/
	struct TCB_t *TCB = NULL;
	void *stack = malloc(8192);
	TCB = (TCB_t*) malloc(sizeof(TCB_t));
	init_TCB(TCB, function, stack, 8192);
	AddQueue(&RunQ, TCB);
}

void run()
{
	ucontext_t parent;	// gets a place to store the main context
	getcontext(&parent);	// magic sauce
	swapcontext(&parent, &(RunQ->context));	//start the first thread
}

void yield()
{
	TCB_t *temp = RunQ;
	RotateQ(&RunQ);	//Rotate RunQ
	swapcontext(&(temp->context), &(RunQ->context));
}
