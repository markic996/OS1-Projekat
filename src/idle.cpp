/*
 * idle.cpp
 *
 *  Created on: Aug 30, 2017
 *      Author: OS1
 */

#include "idle.h"
#include "Def.h"
#include "kernel.h"

Idle::Idle():Thread(512,1){
	idlepcb=idlepcb1;
}

Idle::~Idle(){
	idlepcb=0;
}

void Idle::run(){
	while(1){}
}

void Idle::start(){
#ifndef BCC_BLOCK_IGNORE
	_LOCK;
#endif
	this->idlepcb->flagr=1;
#ifndef BCC_BLOCK_IGNORE
	_UNLOCK;
#endif
}





