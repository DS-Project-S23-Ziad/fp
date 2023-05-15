#pragma once
#include"Process.h"
#include<string>
class Scheduler;
enum Types
{
	fcfs, sjf, rr
};
enum State { IDLE, BUSY };

class Processor
{

private:
	/*int IndState;*/
	/*int IndState;*/
protected:
	Process* RUN;
	Types typeOfProcessor;
	string type;
	State ProcessorState;
	Scheduler* OURscheduler;
public:
	Processor(Scheduler* OUR_scheduler) {
		RUN = NULL;
		ProcessorState = IDLE;
		OURscheduler = OUR_scheduler;
	}
	virtual void ScheduleAlgo() = 0;
	virtual void insertToRDY(Process* r) = 0;
	virtual bool RemoveFromRDY(Process*& r) = 0;
	virtual void SetState(State s) { ProcessorState = s; }
	virtual void SetRun(Process* run) { RUN = run; }
	virtual void PrintRDY() = 0;
	virtual int SizeOfRDY() = 0;
	virtual Process* GetRun() { return RUN; }
	virtual bool IsBUSY() {
		return ProcessorState;
	}
	virtual Types GetType() {
		return typeOfProcessor;
	}
	virtual bool RDYisEmpty() = 0;
	/*virtual Process* DeleteFromRdy(int id)=0;*/
	virtual string TypeName() { return type; }
	virtual bool peekRDY(Process*& r) = 0;
	virtual int TotalRCT() = 0;
};
