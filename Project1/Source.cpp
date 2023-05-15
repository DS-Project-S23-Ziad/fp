#include<iostream>
#include"Scheduler.h"
int main() {
	Scheduler s;
	s.SimulatorFun("ex.txt");
	cout << Scheduler::timestep;
}