/*
 * kernel.h
 *
 *  Created on: Aug 30, 2017
 *      Author: OS1
 */

#ifndef KERNEL_H_
#define KERNEL_H_


#include "Thread.h"
#include "list.h"

class List;

class PCB{

public:

	unsigned* stack;
	unsigned ss;
	unsigned sp;
	unsigned bp;

	Thread* myThread;

	unsigned short flago;
	unsigned short flagbw;
	unsigned short flagbs;
	unsigned short flagr;
	unsigned short numofstarts;

	int SemRet;

	Time tslice;
	Time tsliceSem;

    List* blockedwtc;
	static PCB* running;

	PCB (StackSize stackSize , Time timeSlice,Thread* th);
	void start();
	void waitToComplete();
	virtual ~PCB();
	ID getId();

    static ID getRunningID();
    static Thread * getThreadByID(ID id);
	static void wrapper();

private:
	 static ID posid;
            ID id;
};




#endif /* KERNEL_H_ */
