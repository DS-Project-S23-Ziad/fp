#include "RR.h"
#include"Scheduler.h"
RR::RR(int T, Scheduler* OUR_scheduler) : Processor(OUR_scheduler)
{
	RUN = NULL;
	typeOfProcessor = rr;
	TimeSlice = 0;
	type = "RR";
	TimeSlice = T;
}
RR::RR() : Processor(NULL)
{
	RUN = NULL;
	typeOfProcessor = rr;
	TimeSlice = 0;
	type = "RR";
}
void RR::ScheduleAlgo()
{

}
//Process* RR::DeleteFromRdy(int id)
//{
//	return nullptr;
//}
bool RR::RDYisEmpty()
{
	if (RDY.isEmpty() == true)
	{
		return true;

	}
	else
		return false;

}

void RR::insertToRDY(Process* r)
{
	RDY.enqueue(r);
}

bool RR::RemoveFromRDY(Process*& r)
{
	return RDY.dequeue(r);
}
void RR::PrintRDY()
{
	RDY.printQueue();
}
int RR::SizeOfRDY()
{
	return RDY.GetNumOFNodes();
}

bool RR::peekRDY(Process*& r)
{
	return RDY.peek(r);
}

int RR::TotalRCT()
{
	LinkedQueue<Process*> myRDY = RDY;
	int TotalRCT = 0;
	Process* temp = NULL;
	while (myRDY.dequeue(temp))
	{
		TotalRCT = TotalRCT + temp->getRCT();
	}
	return TotalRCT;
}

