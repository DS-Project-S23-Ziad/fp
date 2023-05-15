#include"FCFS.h"
#include"Scheduler.h"
#include"Node.h"
#include<iostream>
#include"Process.h"
FCFS::FCFS() : Processor(NULL) {
	RUN = NULL;
	typeOfProcessor = fcfs;
	type = "FCFS";
	OURscheduler = NULL;
}

FCFS::FCFS(LinkedQueue<int*>& list, float fork_probability, Scheduler* OUR_scheduler) : Processor(OUR_scheduler)
{
	RUN = NULL;
	typeOfProcessor = fcfs;
	type = "FCFS";
	forkprobability = fork_probability;
	SetSIGKILLlist(list);
}
void FCFS::ScheduleAlgo()
{
	if (!RUN)
	{
		Process* ProcessToRUN = new Process;
		RemoveFromRDY(ProcessToRUN);
		SetRun(ProcessToRUN);
		SetState(BUSY);
	}
}
void FCFS::insertToRDY(Process* r)
{
	RDY.InsertEnd(r);
}
bool FCFS::RemoveFromRDY(Process*& r)
{
	return RDY.DeleteFirst(r);
}

bool FCFS::RDYisEmpty()
{
	if (!RDY.gethead())
	{
		return true;
	}
	else
		return false;
}
void FCFS::PrintRDY()
{
	RDY.PrintList();
}
int FCFS::SizeOfRDY()
{
	return RDY.GetNoOfNodes();
}
//Process*  FCFS:: DeleteFromRdy(int id) {
//	 Node<Process*>* Processptr = RDY.gethead();
//	if (!Processptr)
//	{
//		return nullptr;
//	}
//
//	while (Processptr)
//	{
//		if (Processptr->getItem()->getPID() == id)
//		{
//			RDY.DeleteNode((Processptr->getItem()));
//			return Processptr->getItem();
//		}
//		Processptr = Processptr->getNext();
//	}
//	return nullptr;
//}

bool FCFS::peekRDY(Process*& r)
{
	r = RDY.gethead()->getItem();
	return r;
}

void FCFS::SetSIGKILLlist(LinkedQueue<int*>& list)
{
	SIGKILLlist = list;
}

int FCFS::TotalRCT()
{
	if (RDYisEmpty())
		return 0;
	Node<Process*>* Processptr = RDY.gethead();
	int TotalRCT = 0;
	while (Processptr)
	{
		TotalRCT = TotalRCT + Processptr->getItem()->getRCT();
		Processptr = Processptr->getNext();
	}
	return TotalRCT;
}

/*void FCFS::AddSIGKILLlist(int time, int pid)
{
	int KillSignal[2] = { time , pid };
	 SIGKILLlist.enqueue(KillSignal);
}*/


FCFS::~FCFS()
{
}

bool FCFS::KillSig(int ID, int killTime)
{
	if (RUN)
	{
		if (RUN->getPID() == ID && (killTime == (RUN->getCT() - RUN->getRCT()))) {
			if (RUN->getChild())
			{
				OURscheduler->killORPH(RUN->getChild());
			}
			OURscheduler->ADDtoTRM(RUN);
			RUN = NULL;
			return true;
		}
	}
	if (!RDYisEmpty())
	{
		Process dummyp;
		Process* p = &dummyp; //dummy Process to put the conditions in its data and check by it and recieve deleted Process in it if we delete 
		p->setPID(ID);
		p->setCT(5 + killTime);
		p->setRCT(5);
		if (RDY.DeleteNode(p))
		{
			OURscheduler->killORPH(p->getChild());
			return true;
		}
	}
	return false;
}
//bool FCFS::Search(int ID, Process*& p, int killTime = -1)
//{
   // if (RUN)
   // {
   //	 if (RUN->getPID() == ID && (killTime == (RUN->getCT() - RUN->getRCT()) || killTime == -1)) {
   //		 p = RUN;
   //		 return true;
   //	 }
   // }
   // if (!RDYisEmpty())
   // {
   //	 Node<Process*>* Processptr = RDY.gethead();

   //	 while (Processptr)
   //	 {
   //		 if (Processptr->getItem()->getPID() == ID && killTime == Processptr->getItem()->getCT() - Processptr->getItem()->getRCT())
   //		 {
   //			 p = Processptr->getItem();
   //			 return true;
   //		 }
   //		 Processptr = Processptr->getNext();
   //	 }
   // }
   // return false;
//}
//void FCFS::Kill(Process*& p)
//{
	//if (RUN)
	//{
	//	if (RUN->getPID()==ID){
	//		if (RUN->getChild())
	//		{
	//			Scheduler::killSIG(RUN->getChild()->getPID());
	//		}
	//		/*Search_Kill(RUN->getChild()->getPID());*/
	//		Scheduler::ADDtoTRM(RUN);
	//		RUN = NULL;
	//	}
	//}
	//if (!RDYisEmpty())
	//{
	//	Node<Process*>* Processptr = RDY.gethead();

	//	while (Processptr)
	//	{
	//		if (Processptr->getItem()->getPID() == ID)
	//		{
	//			if (Processptr->getItem()->getChild())
	//			{
	//				Scheduler::killORPH(Processptr->getItem()->getChild()->getPID());
	//			}
	//			RDY.DeleteNode(Processptr->getItem());
	//		}
	//		Processptr = Processptr->getNext();
	//	}
	//}
   // if (p->getChild())
   // {
   //	 Scheduler::killORPH(p->getChild()->getPID());
   // }
   // if (RUN == p) {
   //	 RUN = NULL;
   // }
   // else {
   //	 RDY.DeleteNode(p);
   // }
   // Scheduler::ADDtoTRM(p);
//}


