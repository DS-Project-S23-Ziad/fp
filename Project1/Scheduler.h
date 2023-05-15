#pragma once
#include"LinkedQueue.h"
#include"Process.h"
#include"Processor.h"
#include"QueueADT.h"
#include<string>
#include"UI.h"
class Scheduler
{
private:
	Processor** ArrOfprocessor;
	FCFS** ArrOfFCFS;
	int NumOfFCFS, NumOfSJF, NumOfRR, TimeSliceForRR, Tf, MaxW, STL, forkP, NumofProcess, NumofProcessor;
	LinkedQueue <Process*> NEW;
	LinkedQueue <Process*> TRM, BLK;
	UI UIobj;
	LinkedQueue<int*> KILLlist;//TO GET FROM LOAD FUNCTION AND PASS IT BY REFRENCE TO FCFS

public:
	void LoadFile(string fileName);
	void SimulatorFun(string fileName);
	void ADDtoTRM(Process*& p);
	//phase[2]
	static int timestep; //TIME STEP
	bool migrateToSJF(Process* p);
	void killORPH(Process* Child);
	bool IO_RQST_HNDL(Process*& p);
	void insertTOTRM(Process*& p);
	void WorkStealing(Process*& p);
};

