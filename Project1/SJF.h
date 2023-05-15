#pragma once
#include"Processor.h"
#include"PriorityQueue.h"
class Scheduler;
class SJF :public Processor
{
private:
	PriorityQueue<Process*> RDY;
public:
	SJF(Scheduler* OUR_scheduler);
	SJF();
	virtual void ScheduleAlgo();
	/*virtual Process* DeleteFromRdy(int id);*/
	virtual void insertToRDY(Process* r);
	virtual bool RemoveFromRDY(Process*& r);
	virtual bool RDYisEmpty();
	virtual void PrintRDY();
	virtual int SizeOfRDY();
	virtual bool peekRDY(Process*& r);
	virtual int TotalRCT();
};