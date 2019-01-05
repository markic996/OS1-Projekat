/*
 * Thread.cpp
 *
 *  Created on: Aug 30, 2017
 *      Author: OS1
 */


#include "Thread.h"
#include "kernel.h"
#include "Def.h"
#include "timer.h"


void Thread::waitToComplete(){
	myPCB->waitToComplete();
}


void Thread::start(){
	myPCB->start();
}


Thread::~Thread(){
	waitToComplete();
#ifndef BCC_BLOCK_IGNORE
	_LOCK;
#endif
	delete myPCB;
#ifndef BCC_BLOCK_IGNORE
	_UNLOCK;
#endif
}


ID Thread::getId(){
	return myPCB->getId();
}


ID Thread::getRunningId(){
	return PCB::getRunningID();
}


Thread* Thread::getThreadById(ID id){
	return PCB::getThreadByID(id);
}


Thread::Thread(StackSize stackSize, Time timeSlice):
		myPCB(new PCB(stackSize,timeSlice,this)){}


#ifndef BCC_BLOCK_IGNORE
void dispatch(){
	asm cli;
	required_switch=1;
	timer();
	asm sti;
}
#endif




