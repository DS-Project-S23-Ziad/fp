#pragma once
#include"Processor.h"
#include"LinkedList.h"
class Scheduler;
class FCFS :public Processor
{
private:
	LinkedList<Process*> RDY;
	LinkedQueue<int*> SIGKILLlist;//have the int pointer point to array of 2elements (AT,PID)
	float forkprobability;
public:
	FCFS();
	FCFS(LinkedQueue<int*>& list, float fork_probability, Scheduler* OUR_scheduler);//CONSTRUCOT INITIALIZE SIGKILLlist (take it by refrence to save memory)
	virtual void ScheduleAlgo();
	virtual void insertToRDY(Process* r);
	virtual bool RemoveFromRDY(Process*& r);
	virtual bool RDYisEmpty();
	virtual void PrintRDY();
	virtual int SizeOfRDY();
	//Process* DeleteFromRdy(int id);
	virtual bool peekRDY(Process*& r);
	void SetSIGKILLlist(LinkedQueue<int*>& list);
	virtual int TotalRCT();
	//bool Search(int ID,Process* &p,int killTime=-1);
	//void Kill(Process*& p);
	~FCFS();
	bool KillSig(int ID, int killTime);
};