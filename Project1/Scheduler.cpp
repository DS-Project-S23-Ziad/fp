#include "Scheduler.h"
#include<fstream>
#include<iostream>
#include"LinkedQueue.h"
#include"QueueADT.h"
#include"FCFS.h"
#include"SJF.h"
#include"RR.h"
#include<ctime>
#include<cstdlib>
#include <limits.h>
#include <stdio.h>
#include<windows.h>
#include"UI.h"
using namespace std;
int Scheduler::timestep = 0; // definition outside class declaration
void Scheduler::LoadFile(string fileName)
{
	ifstream fin("ex.txt");
	/*int NumOfFCFS, NumOfSJF, NumOfRR, TimeSliceForRR, Tf, MaxW, STL, forkP, NumofProcess;*/
	fin >> NumOfFCFS >> NumOfSJF >> NumOfRR >> TimeSliceForRR >> Tf >> MaxW >> STL >> forkP >> NumofProcess;

	for (int i = 0; i < NumofProcess; i++)
	{
		int AT, PID, CT, N, x;
		fin >> AT >> PID >> CT >> N;
		Process* NewProcessPtr = new Process;
		NewProcessPtr->setAT(AT);
		NewProcessPtr->setPID(PID);
		NewProcessPtr->setCT(CT);
		for (int i = 1; i <= N; i++)
		{
			char ignore;
			int IoR, IoD;
			fin >> ignore;
			fin >> IoR;
			fin >> ignore;
			fin >> IoD;
			NewProcessPtr->addIO_Pairs(IoR, IoR);
			fin >> ignore;
			if (i < N)
				fin >> ignore;
		}
		NEW.enqueue(NewProcessPtr);
	}
	string ignore;
	string line;
	fin >> ignore;
	getline(fin, line);
	int time, KilledPid;
	while (!fin.eof())
	{
		fin >> time;
		fin >> KilledPid;
		int signal[2] = { time , KilledPid };
		KILLlist.enqueue(signal);
	}
}

//void Scheduler::SimulatorFun(string fileName)
//{
//}

void Scheduler::ADDtoTRM(Process*& p)
{
	TRM.enqueue(p);
}
void Scheduler::killORPH(Process* Child)
{
	Process* p;
	for (int i = 0; i < NumOfFCFS; i++)
	{
		if (ArrOfFCFS[i]->KillSig(Child->getPID(), (Child->getCT() - Child->getRCT()))) { return; }
	}
}



void Scheduler::SimulatorFun(string fileName)
{

	LoadFile(fileName); //load --> file

	//!!! creating array of Processors !!!
	NumofProcessor = NumOfFCFS + NumOfSJF + NumOfRR;
	ArrOfprocessor = new Processor * [NumofProcessor];
	ArrOfFCFS = new FCFS * [NumOfFCFS];
	//(1)FCFS
	for (int i = 0; i < NumOfFCFS; i++)
	{
		ArrOfFCFS[i] = new FCFS(KILLlist, forkP, this);
		ArrOfprocessor[i] = ArrOfFCFS[i];

	}
	//(2)SJF
	for (int j = NumOfFCFS; j < NumOfFCFS + NumOfSJF; j++)
	{
		ArrOfprocessor[j] = new SJF(this);
	}
	//(3)RR
	for (int k = NumOfFCFS + NumOfSJF; k < NumOfFCFS + NumOfSJF + NumOfRR; k++)
	{
		ArrOfprocessor[k] = new RR(TimeSliceForRR, this);
	}
	timestep = 0; //TIME STEP
	int MovNewRdy = 0; //NUMBER OF PROCSSES MOVED FROM NEW TO RDYs
	srand(time(0));
	while (TRM.GetNumOFNodes() < NumofProcess)
	{
		timestep++;//increasing time step
		Process* ProcessPtr = new Process;
		NEW.peek(ProcessPtr);
		while (!NEW.isEmpty() && ProcessPtr->getAT() == timestep) {
			//NEW TO RDY - start
			Process* ProcessMoved = new Process;
			NEW.dequeue(ProcessMoved);
			int min = INT_MAX;
			Processor* MINRDY = ArrOfprocessor[0];
			for (int i = 0; i < NumofProcessor; i++)
			{
				if (!ArrOfprocessor[i]->RDYisEmpty()) {
					if (ArrOfprocessor[i]->TotalRCT() < min)
					{
						min = ArrOfprocessor[i]->TotalRCT();
						MINRDY = ArrOfprocessor[i];
					}
				}
				else {
					MINRDY = ArrOfprocessor[i];
					break;
				}
			}
			NEW.peek(ProcessPtr);
			MINRDY->insertToRDY(ProcessMoved);
			//NEW TO RDY - end
		}
		for (int i = 0; i < NumofProcessor; i++)
		{
			ArrOfprocessor[i]->ScheduleAlgo();
		}
		if (timestep==50)
		{
			break;
		}
		if (timestep <= 50)
		{
			UIobj.Print_InteractiveMode(timestep, NumofProcessor, ArrOfprocessor, NEW, BLK, TRM);
		}
		
	}
}
bool Scheduler::migrateToSJF(Process* p)
{
	if (NumOfSJF == 0)return false;
	Processor* min_load = ArrOfprocessor[0];
	int min = INT_MAX;
	for (int i = 0; i < NumofProcessor; i++)
	{
		if (ArrOfprocessor[i]->GetType() == sjf && ArrOfprocessor[i]->TotalRCT() < min)
		{
			min_load = ArrOfprocessor[i];
			min = ArrOfprocessor[i]->TotalRCT();
		}
	}
	min_load->insertToRDY(p);
	return true;
}
bool Scheduler::IO_RQST_HNDL(Process*& p)
{
	p->getIO_R();
	if (p->getCT() - p->getRCT() == p->getIO_R())
	{
		p->setState("BLK");
		BLK.enqueue(p);
		return true;
	}
	return false;
}

void Scheduler::insertTOTRM(Process*& p)
{
	TRM.enqueue(p);
}

void Scheduler::WorkStealing(Process*& p)
{
	int LQF = INT_MIN;
	int SQF = INT_MAX;
	int StealLimit = 40;
	Processor* Longest = ArrOfprocessor[0];
	Processor* Shortest = ArrOfprocessor[0];
	for (int i = 0; i < NumofProcessor; i++)
	{
		if (ArrOfprocessor[i]->TotalRCT() < SQF)
		{
			SQF = ArrOfprocessor[i]->TotalRCT();
			Shortest = ArrOfprocessor[i];
		}
		if (ArrOfprocessor[i]->TotalRCT() > LQF)
		{
			LQF = ArrOfprocessor[i]->TotalRCT();
			Longest = ArrOfprocessor[i];
		}
	}
	StealLimit = (LQF - SQF) / LQF;
	while (StealLimit > 40)
	{
		Longest->RemoveFromRDY(p);
		Shortest->insertToRDY(p);
		StealLimit = (LQF - SQF) / LQF;
	}
}








