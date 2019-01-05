/*
 * IVTEntry.cpp
 *
 *  Created on: Aug 30, 2017
 *      Author: OS1
 */

#include "IVTEntry.h"
#include "Thread.h"
#include "DOS.H"
#include "event.h"
#include "kerevent.h"
#include "Def.h"

IVTEntry* IVTEntry::IVTable[256];

IVTEntry::IVTEntry(IVTNo ivtNo, entryInterrupt newRoutine) {
#ifndef BCC_BLOCK_IGNORE
	_LOCK;
#endif
	ivtNumber = ivtNo;
	IVTable[ivtNumber] = this;
	KerEv = 0;
	oldRoutine = 0;
#ifndef BCC_BLOCK_IGNORE

	oldRoutine = getvect(ivtNumber);
	setvect(ivtNumber, newRoutine);

	_UNLOCK;
#endif
}

IVTEntry::~IVTEntry() {
#ifndef BCC_BLOCK_IGNORE
	_LOCK;
#endif
	IVTable[ivtNumber] = 0;
#ifndef BCC_BLOCK_IGNORE

	setvect(ivtNumber, oldRoutine);

	_UNLOCK;
#endif
}

void IVTEntry::signal() {
	if (KerEv != 0) {
		KerEv->signal();
	}
	dispatch();
}

void IVTEntry::callOldR() {
	oldRoutine();
}
