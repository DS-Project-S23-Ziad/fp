#include "UI.h"
#include"Processor.h"
void UI::Print_InteractiveMode( int& timestep,  int& NumofProcessor, Processor**& ArrOfprocessor,  LinkedQueue<Process*>& NEW,  LinkedQueue<Process*>& BLK,  LinkedQueue<Process*>& TRM)
{
	/*char x;*/
	cout<<"Time Step: "<< timestep<<endl;
	cout << "-------------------- RDY processes --------------------" << endl;
	for (int i = 0; i < NumofProcessor; i++)
	{
		cout << "processor " << i << " [" << ArrOfprocessor[i]->TypeName() << "]; " << ArrOfprocessor[i]->SizeOfRDY() << " RDY: ";
		ArrOfprocessor[i]->PrintRDY();
		cout << endl;
	}
	cout << "-------------------- BLK processes --------------------" << endl;
	cout << BLK.GetNumOFNodes() << " BLK:";
	BLK.printQueue();
	cout << endl;
	cout << "-------------------- RUN processes --------------------" << endl;
	int NUMofRUNNED=0;
	for (int i = 0; i < NumofProcessor; i++)
	{
		if (ArrOfprocessor[i]->IsBUSY()) { NUMofRUNNED++; }
	}
	cout << NUMofRUNNED << " RUN:";
	for (int i = 0; i < NumofProcessor; i++)
	{
		if (ArrOfprocessor[i]->IsBUSY()) { cout << ArrOfprocessor[i]->GetRun()->getPID() << "(P" << i << ") "; }
	}
	cout << endl << "-------------     TRM processes  ---------------------" << endl;
	cout << TRM.GetNumOFNodes() << " TRM:";
	TRM.printQueue();
	cout<<endl << "PRESS ANY KEY TO MOVE TO NEXT STEP !" << endl;
	//cin.get();
}
