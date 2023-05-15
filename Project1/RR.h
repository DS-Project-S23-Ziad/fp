#pragma once
#include"Processor.h"
#include"LinkedQueue.h"
class Scheduler;
class RR :public Processor
{
private:
	int TimeSlice;
	LinkedQueue<Process*> RDY;
public:
	RR();
	RR(int T, Scheduler* OUR_scheduler);
	virtual void ScheduleAlgo();
	/*virtual Process* DeleteFromRdy(int id);*/
	bool RDYisEmpty();
	virtual void insertToRDY(Process* r);
	virtual bool RemoveFromRDY(Process*& r);
	virtual void PrintRDY();
	virtual int SizeOfRDY();
	virtual bool peekRDY(Process*& r);
	virtual int TotalRCT();
};