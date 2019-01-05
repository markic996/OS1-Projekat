/*
 * kernel.cpp
 *
 *  Created on: Aug 30, 2017
 *      Author: OS1
 */

#include "kernel.h"
#include "thread.h"
#include "SCHEDULE.H"
#include "Def.h"
#include "list.h"
#include "timer.h"
#include <dos.h>
#include "idle.h"


  PCB* PCB::running=0;


  PCB::PCB (StackSize stackSize, Time timeSlice,Thread* th)
  {
#ifndef BCC_BLOCK_IGNORE
	_LOCK;
#endif
	  if(stackSize>65536)stackSize=64536;

	  flago=flagbw=flagbs=flagr=numofstarts=0;
	  blockedwtc=new List();
	  myThread=th;
      StackSize sss=stackSize/sizeof(unsigned);
	  stack=new unsigned[sss];
	  id=++posid;
	  tslice=timeSlice;
	  SemRet=1;
	  tsliceSem=65535;

	  stack[sss - 1] = 0x200;
	  #ifndef BCC_BLOCK_IGNORE
	  stack[sss - 2] = FP_SEG(PCB::wrapper);
	  stack[sss - 3] = FP_OFF(PCB::wrapper);
	  sp = FP_OFF(stack + sss - 12);
	  ss = FP_SEG(stack + sss - 12);
	  bp = FP_OFF(stack + sss - 12);
	  #endif

	  if(flagidle==1){
	  	   flagidle=0;
	  	   idlepcb1=this;
	  	}
	  else{
	    counterIdle=counterIdle+1;
	  	threads->addpcb(this);
	  	}
#ifndef BCC_BLOCK_IGNORE
	_UNLOCK;
#endif
  }

  void PCB::start(){
#ifndef BCC_BLOCK_IGNORE
	_LOCK;
#endif
      if(numofstarts==0){
    	  numofstarts=1;
    	  flagr=1;
    	  Scheduler::put(this);
      }
#ifndef BCC_BLOCK_IGNORE
	_UNLOCK;
#endif
  }

  void PCB::waitToComplete(){
#ifndef BCC_BLOCK_IGNORE
	_LOCK;
#endif
	  if((!flago)&&(this!=idlepcb1)&&(this!=PCB::running)){
          blockedwtc->addpcb(PCB::running);
		  PCB::running->flagr=0;
		  PCB::running->flagbw=1;
		  dispatch();
	  }
#ifndef BCC_BLOCK_IGNORE
	_UNLOCK;
#endif
  }

  PCB::~PCB(){
	  delete[] stack;
	  delete blockedwtc;
	  if(this!=idlepcb1)
	  threads->removebyID(this->getId());
  }

  ID PCB::getId(){
	  return id;
  }

  ID PCB::getRunningID(){
	  return running->getId();
  }

  Thread * PCB::getThreadByID(ID id){
	  return threads->findpcb(id)->myThread;
  }

  void PCB::wrapper(){
	  PCB::running->myThread->run();
#ifndef BCC_BLOCK_IGNORE
	_LOCK;
#endif
	  PCB::running->blockedwtc->overWait();
	  PCB::running->flago=1;
	  PCB::running->flagr=0;
	  counterIdle=counterIdle-1;
#ifndef BCC_BLOCK_IGNORE
	_UNLOCK;
#endif
	  dispatch();
  }

  ID PCB::posid=0;



