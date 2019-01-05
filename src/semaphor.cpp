/*
 * semaohor.cpp
 *
 *  Created on: Aug 30, 2017
 *      Author: OS1
 */

#include "semaphor.h"
#include "kernsem.h"
#include "Def.h"

Semaphore::Semaphore(int init){
#ifndef BCC_BLOCK_IGNORE
	_LOCK;
#endif
myImpl=new KernelSem(init,this);
#ifndef BCC_BLOCK_IGNORE
	_UNLOCK;
#endif
}

Semaphore::~Semaphore(){
#ifndef BCC_BLOCK_IGNORE
	_LOCK;
#endif
	delete Semaphore::myImpl;
	Semaphore::myImpl=0;
#ifndef BCC_BLOCK_IGNORE
	_UNLOCK;
#endif
}

int Semaphore::wait(Time maxTimeToWait){
#ifndef BCC_BLOCK_IGNORE
	_LOCK;
#endif
	int q= Semaphore::myImpl->wait(maxTimeToWait);
#ifndef BCC_BLOCK_IGNORE
	_UNLOCK;
#endif
	return q;
}

void Semaphore::signal(){
#ifndef BCC_BLOCK_IGNORE
	_LOCK;
#endif
	Semaphore::myImpl->signal();
#ifndef BCC_BLOCK_IGNORE
	_UNLOCK;
#endif
}

int Semaphore::val()const{
	return Semaphore::myImpl->val();
}




