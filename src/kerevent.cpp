/*
 * kerevent.cpp
 *
 *  Created on: Aug 30, 2017
 *      Author: OS1
 */


#include "kernel.h"
#include "kerevent.h"
#include "Def.h"



KernelEv::KernelEv(IVTNo ivtNo,Event* ev){
#ifndef BCC_BLOCK_IGNORE
	_LOCK;
#endif
	myEvent=ev;
	ivtnumber=ivtNo;
	myPCB=PCB::running;
	flagblc=0;
	IVTEntry::IVTable[ivtnumber]->KerEv=this;
#ifndef BCC_BLOCK_IGNORE
	_UNLOCK;
#endif
}


KernelEv::~KernelEv(){
	myPCB=0;
	IVTEntry::IVTable[ivtnumber]->KerEv=0;
}


void KernelEv::signal(){
	if(flagblc==1){
		flagblc=0;
		myPCB->flagr=1;
		Scheduler::put(myPCB);
	}
}

void KernelEv::wait(){
	if(PCB::running==myPCB){
		if(flagblc==0){
			flagblc=1;
			PCB::running->flagr=0;
			dispatch();
		}
	}
}
