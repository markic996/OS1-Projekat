/*
 * timer.cpp
 *
 *  Created on: Aug 30, 2017
 *      Author: OS1
 */

#include "timer.h"
#include "Def.h"
#include "kernel.h"
#include "SCHEDULE.H"
#include "kernsem.h"
#include "idle.h"
#include "Thread.h"
#include "IVTEntry.h"


unsigned tsp;
unsigned tss;
unsigned tbp;

unsigned oldTimerOFF;
unsigned oldTimerSEG;

void tick();

void interrupt timer(){
	tick();

	if (!required_switch) {
		counter--;
		semaphores->FindTimeOver();
#ifndef BCC_BLOCK_IGNORE
			asm int 60h;
		#endif
	}
		if ((counter == 0) || required_switch) {
			if(lock_flag){
			required_switch=0;
#ifndef BCC_BLOCK_IGNORE
			asm {
				mov tsp, sp
				mov tss, ss
				mov tbp, bp
			}
#endif

			PCB::running->sp = tsp;
			PCB::running->ss = tss;
			PCB::running->bp=tbp;

			if((PCB::running->flagr==1) && (PCB::running!=idlepcb1))
			Scheduler::put(PCB::running);

			PCB::running=Scheduler::get();
			if((PCB::running==0) && (counterIdle!=0))PCB::running=idlethr->idlepcb;

			tsp = PCB::running->sp;
			tss = PCB::running->ss;
			tbp = PCB::running->bp;

			counter = PCB::running->tslice;

#ifndef BCC_BLOCK_IGNORE
			asm {
				mov sp, tsp
				mov ss, tss
				mov bp, tbp
			}
#endif
		}
			else required_switch=1;
		}
}


void init(){
	idlethr=new Idle();
	idlethr->start();
#ifndef BCC_BLOCK_IGNORE
	asm{
			cli
			push es
			push ax

			mov ax,0
			mov es,ax

			mov ax, word ptr es:0022h
			mov word ptr oldTimerSEG, ax
			mov ax, word ptr es:0020h
			mov word ptr oldTimerOFF, ax

			mov word ptr es:0022h, seg timer
			mov word ptr es:0020h, offset timer

			mov ax, oldTimerSEG
			mov word ptr es:0182h, ax
			mov ax, oldTimerOFF
			mov word ptr es:0180h, ax

			pop ax
			pop es
			sti
		}
#endif
}


void restore(){
#ifndef BCC_BLOCK_IGNORE
	asm {
			cli
			push es
			push ax

			mov ax,0
			mov es,ax

			mov ax, word ptr oldTimerSEG
			mov word ptr es:0022h, ax
			mov ax, word ptr oldTimerOFF
			mov word ptr es:0020h, ax

			pop ax
			pop es
			sti
		}

	_LOCK;
	delete threads;
	delete semaphores;
	delete idlethr;
	for(int i=0;i<256;i++)
		delete IVTEntry::IVTable[i];
	_UNLOCK;
#endif
}




