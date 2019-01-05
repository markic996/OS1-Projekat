/*
 * listsem.cpp
 *
 *  Created on: Aug 30, 2017
 *      Author: OS1
 */


#include "Def.h"
#include "listsem.h"
#include "kernsem.h"
#include "list.h"

ListSem::~ListSem(){
#ifndef BCC_BLOCK_IGNORE
	_LOCK;
#endif
	Elem* pom=0;
	while(pom){
		pom=first;
		first=first->next;
		delete pom->p;
		pom->p=0;
		pom->next=0;
		delete pom;
	}
	first=last=0;
#ifndef BCC_BLOCK_IGNORE
	_UNLOCK;
#endif
}

void ListSem::addsem(KernelSem* p){
#ifndef BCC_BLOCK_IGNORE
	_LOCK;
#endif
	if(first==0){
	first=new Elem(p);
	last=first;
	}
	else{
		last->next=new Elem(p);
		last=last->next;
	}
#ifndef BCC_BLOCK_IGNORE
	_UNLOCK;
#endif
}

void ListSem::removesem(KernelSem* p){
#ifndef BCC_BLOCK_IGNORE
	_LOCK;
#endif
	Elem* pom=first;
	Elem* pr=0;
	while(p!=pom->p){
		pr=pom;
		pom=pom->next;
	}
	if(pr==0)first=first->next;
	else pr->next=pom->next;
	if(pom==last)last=pr;
	pom->next=0;
	pom->p=0;
	delete pom;
#ifndef BCC_BLOCK_IGNORE
	_UNLOCK;
#endif
}


void ListSem::FindTimeOver(){
#ifndef BCC_BLOCK_IGNORE
	_LOCK;
#endif
	Elem*pom= first;
	while(pom){
		pom->p->Blocked->FindTO();
		pom=pom->next;
	}
#ifndef BCC_BLOCK_IGNORE
	_UNLOCK;
#endif
}




