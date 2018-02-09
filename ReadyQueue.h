#pragma once
#include "ProcessControlBlock.h"

class ReadyQueue
{
public:
	ReadyQueue();
	~ReadyQueue();
	void insertProc(ProcessControlBlock* proc);
	ProcessControlBlock* removeHighestProc();
	int size();
	void displayQueue();
};

