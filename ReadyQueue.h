#pragma once
#include "ProcessControlBlock.h"
#include "GenOrderList.h"
class ReadyQueue
{
private:
	GenOrderList<ProcessControlBlock>* m_list;
public:
	ReadyQueue();
	~ReadyQueue();
	void insertProc(ProcessControlBlock* proc);
	ProcessControlBlock* removeHighestProc();
	int size();
	void displayQueue();
};

