#pragma once
#include<iostream>
#include"FCFS.h"
#include"LinkedList.h"
#include"LinkedQueue.h"
#include"Processor.h"
class UI
{
private:
public:
	void Print_InteractiveMode( int& timestep,  int& NumofProcessor, Processor** &ArrOfprocessor,  LinkedQueue <Process*> & NEW,  LinkedQueue <Process*>& BLK,  LinkedQueue <Process*>& TRM);
};

