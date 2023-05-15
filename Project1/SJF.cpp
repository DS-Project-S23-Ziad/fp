#include"SJF.h"
#include"Processor.h"
#include"Scheduler.h"

SJF::SJF() : Processor(NULL)
{
	RUN = NULL;
	typeOfProcessor = sjf;
	type = "SJF";
	OURscheduler = NULL;
}
SJF::SJF(Scheduler* OUR_scheduler) : Processor(OUR_scheduler)
{
}
void SJF::ScheduleAlgo()
{
	if (!RUN)
		RemoveFromRDY(RUN);
	else
	{
		RUN->setRCT(RUN->getRCT() - 1);
		int* dummyint;
		if (!RUN->getIO_PAIRS().peek(dummyint))
		{
			if (OURscheduler->IO_RQST_HNDL(RUN))
			{
				//int* x;
				//RUN->getIO_PAIRS().dequeue(x);
				RUN = NULL;
			}
		}
		if (RUN->getRCT() == 0)
		{
			OURscheduler->insertTOTRM(RUN);
			RUN = NULL;
		}
	}
}

//Process* SJF::DeleteFromRdy(int id)
//{
//	return nullptr;
//}
void SJF::insertToRDY(Process* r)
{
	RDY.enqueue(r);
}
bool SJF::RemoveFromRDY(Process*& r)
{
	return RDY.dequeue(r);

}
bool SJF::RDYisEmpty()
{
	if (RDY.isEmpty() == true)
	{
		return true;

	}
	else
		return false;

}

void SJF::PrintRDY()
{
	RDY.printQueue();
}

int SJF::SizeOfRDY()
{
	return RDY.GetNumOFNodes();
}

bool SJF::peekRDY(Process*& r)
{
	return RDY.peek(r);
}

int SJF::TotalRCT()
{
	PriorityQueue<Process*> myRDY = RDY;
	int TotalRCT = 0;
	Process* temp = NULL;
	while (myRDY.dequeue(temp))
	{
		TotalRCT = TotalRCT + temp->getRCT();
	}
	return TotalRCT;
}
