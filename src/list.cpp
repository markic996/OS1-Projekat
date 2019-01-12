
/*
 * list.cpp
 *
 *  Created on: Aug 30, 2017
 *      Author: OS1
 */

#include "list.h"
#include "SCHEDULE.H"
#include "Def.h"
#include "Thread.h"
#include "timer.h"

List* threads=new List();

List::List(PCB* p){
#ifndef BCC_BLOCK_IGNORE
	_LOCK;
#endif
    first=last=new Elem(p);
#ifndef BCC_BLOCK_IGNORE
	_UNLOCK;
#endif
}

void List::addpcb(PCB* p){
#ifndef BCC_BLOCK_IGNORE
	_LOCK;
#endif
	    Elem* pom=new Elem(p);
	    	if(!first)
			first=pom;
	    	else
	    		last->next=pom;
	    	last=pom;
#ifndef BCC_BLOCK_IGNORE
	_UNLOCK;
#endif
	}

void List::remove(){
#ifndef BCC_BLOCK_IGNORE
	_LOCK;
#endif
	Elem* old=0;
	while(first){
		old=first;
		first=first->next;
		old->p=0;
		old->next=0;
		delete old;
	}
	first=last=0;
#ifndef BCC_BLOCK_IGNORE
	_UNLOCK;
#endif
}

PCB* List::findpcb(ID i){
#ifndef BCC_BLOCK_IGNORE
	_LOCK;
#endif
	Elem* now=first;
	while(now->p->getId()!=i){
			now=now->next;
	}
#ifndef BCC_BLOCK_IGNORE
	_UNLOCK;
#endif
	if(now)
		return now->p;
	else
		return 0;
}


void List::overWait(){
#ifndef BCC_BLOCK_IGNORE
	_LOCK;
#endif
     if(first!=0){
     Elem* now=first;
     while(now!=0){
    	 now->p->flagr=1;
    	 if(over==0)
    	    now->p->flagbw=0;
    	 else
    	    now->p->flagbs=0;
    	 Scheduler::put(now->p);
    	 now=now->next;
     }
#ifndef BCC_BLOCK_IGNORE
	_UNLOCK;
#endif
     remove();
     }

}


void List::removebyID(ID i){
#ifndef BCC_BLOCK_IGNORE
	_LOCK;
#endif
	Elem* old=0;
	Elem* now=first;
	if(now){
	while(now->p->getId()!=i){
		old=now;
		now=now->next;
	}
	if(now){
    		if(old==0){
    			first=first->next;
    			if(first==0)
				last=0;
    }
    else
    	old->next=now->next;
        if(now==last)last=old;
    now->p=0;
    now->next=0;
	delete now;
	}
	}
#ifndef BCC_BLOCK_IGNORE
	_UNLOCK;
#endif
}


PCB* List::getFirst(){
	if(first){
#ifndef BCC_BLOCK_IGNORE
	_LOCK;
#endif
		Elem*pom=first;
		PCB* ret=first->p;
		first->p=0;
		first=first->next;
		pom->next=0;
		if(first==0)
			last=0;
		delete pom;
#ifndef BCC_BLOCK_IGNORE
	_UNLOCK;
#endif
		return ret;
	}else
	return 0;
}

void List::deblock(PCB* p){
	p->flagbs=0;
	p->flagr=1;
	p->SemRet=0;
	p->tsliceSem=65535;
	Scheduler::put(p);
}

void List::FindTO(){
	Elem*pom=first;
	int s=0;
	while(pom){
		    if(pom->p->tsliceSem!=65535){
			pom->p->tsliceSem--;
			if(pom->p->tsliceSem==0){
				List::deblock(pom->p);
				Elem* pp=pom;
				s=1;
		        pom=pom->next;
				this->removebyID(pp->p->getId());
			}
		    }
	    if(s==0)
		pom=pom->next;
	    s=0;
	}
}






