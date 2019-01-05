/*
 * kernsem.cpp
 *
 *  Created on: Aug 30, 2017
 *      Author: OS1
 */

#include "kernsem.h"
#include "Def.h"
#include "SCHEDULE.H"

ListSem* semaphores=new ListSem();

KernelSem::KernelSem(int init,Semaphore* sem){
	value=init;
	mySem=sem;
	Blocked=new List();
	semaphores->addsem(this);
}

KernelSem::~KernelSem(){
	semaphores->removesem(this);
	over=1;
	Blocked->overWait();
	over=0;
	mySem=0;
}

void KernelSem::signal(){
	if(value++<0)
		deblock();
}

int KernelSem::wait(Time maxTimeToWait){
    PCB::running->SemRet=1;
    value--;
    if(value<0)
    	block(maxTimeToWait);
        return PCB::running->SemRet;
}

void KernelSem::block(Time mt){
	if(mt>0)
	PCB::running->tsliceSem=mt;
	PCB::running->flagbs=1;
	PCB::running->flagr=0;
	Blocked->addpcb(PCB::running);
	dispatch();
}

void KernelSem::deblock(){
	PCB* t=Blocked->getFirst();
	if(t){
	t->flagbs=0;
	t->flagr=1;
	t->SemRet=1;
	Scheduler::put(t);
	}
}

int KernelSem::val(){
	return value;
}





