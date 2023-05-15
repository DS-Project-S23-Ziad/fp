#pragma once
#include <string>
#include"LinkedQueue.h"
#include"Node.h"
#include"QueueADT.h"
using namespace std;
class Process
{
private:
	int PID;
	int AT;
	int CT;
	int RT;
	int TT;
	int TRT;
	int WT;
	int RemainingCT;
	string State;
	Process* child;
	LinkedQueue<int*> IO_Pairs;
public:
	Process();
	Process* getChild();
	friend ostream& operator<<(ostream&, Process& r);
	void setPID(int x);
	int getPID();
	void setAT(int x);
	int getAT();
	void setCT(int x);
	int getCT();
	void setRT(int x);
	int getRT();
	void setTT(int x);
	int getTT();
	void setTRT(int x);
	int getTRT();
	void setWT(int x);
	int getWT();
	void setState(string x);
	void addIO_Pairs(int IO_R, int IO_D);
	string getState();
	int getRCT();
	void setRCT(int time);
	int getIO_R();
	int getIO_D();
	LinkedQueue<int*> getIO_PAIRS();
};