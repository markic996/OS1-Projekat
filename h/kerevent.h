/*
 * kerevent.h
 *
 *  Created on: Aug 30, 2017
 *      Author: OS1
 */

#ifndef KEREVENT_H_
#define KEREVENT_H_


#include "event.h"
#include "kernel.h"
#include "IVTEntry.h"
#include "SCHEDULE.h"


class KernelEv{

public:
	KernelEv (IVTNo ivtNo,Event* ev);
	~KernelEv ();

	void wait  ();
	void signal();

protected:
	friend class Event;
private:
	Event* myEvent;
	IVTNo ivtnumber;
	PCB* myPCB;
	unsigned flagblc;

};


#endif /* KEREVENT_H_ */
