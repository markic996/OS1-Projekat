/*
 * event.cpp
 *
 *  Created on: Aug 30, 2017
 *      Author: OS1
 */


#include "event.h"
#include "Def.h"
#include "kerevent.h"

Event::Event(IVTNo ivtNo):myImpl(new KernelEv(ivtNo,this)){
}

Event::~Event(){
#ifndef BCC_BLOCK_IGNORE
	_LOCK;
#endif
	myImpl->myEvent=0;
	delete myImpl;
#ifndef BCC_BLOCK_IGNORE
	_UNLOCK;
#endif
	myImpl=0;
}

void Event::wait(){
#ifndef BCC_BLOCK_IGNORE
	_LOCK;
#endif
	myImpl->wait();
#ifndef BCC_BLOCK_IGNORE
	_UNLOCK;
#endif
}

void Event::signal(){
#ifndef BCC_BLOCK_IGNORE
	_LOCK;
#endif
	myImpl->signal();
#ifndef BCC_BLOCK_IGNORE
	_UNLOCK;
#endif
}
