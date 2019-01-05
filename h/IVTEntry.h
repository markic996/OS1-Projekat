/*
 * IVTEntry.h
 *
 *  Created on: Aug 30, 2017
 *      Author: OS1
 */

#ifndef IVTENTRY_H_
#define IVTENTRY_H_

typedef unsigned char IVTNo;
typedef void interrupt (*entryInterrupt)(...);


class IVTEntry {

	friend class KernelEv;

	KernelEv* KerEv;
	int ivtNumber;
	entryInterrupt oldRoutine;


public:
	static IVTEntry* IVTable[];

	IVTEntry(IVTNo ivtNo, entryInterrupt newRout);
	~IVTEntry();
	void signal();
	void callOldR();

};

#endif /* IVTENTRY_H_ */
