// Judah Perez
// 2/4/2018
//CS 433 Project 1
// Priority Queue of Processes

#include <iostream> 
#include "ProcessControlBlock.h"
#include "PcbTable.h"
#include "ReadyQueue.h"

void AddTestProcs(PcbTable* table) {
	int id = 1;

	for (int i = 0; i < 20; i++)
	{
		ProcessControlBlock* firstBlock = new ProcessControlBlock{};
		firstBlock->id = id++;
		firstBlock->state = PcbState::NEW;
		table->addProcess(firstBlock);
	}

}

int main()
{
	std::cout << "Process Control" << std::endl;

	PcbTable* table = new PcbTable();
	AddTestProcs(table);

	int firstProcSize = 4;
	int firstProcs[4] = { 5, 1, 8, 11 };
	
	//test print
	if (!table->isEmpty()) {
		ProcessListLink* link = table->begin();
		while (link != NULL) {
			ProcessControlBlock* firstBlock = link->proc;
			std::cout << "Id:" << firstBlock->id << " State:" << StateName(firstBlock->state) << " Priority:" << firstBlock->priority << std::endl;
			link = link->nextLink;
		}

	}

	ReadyQueue* readyQueue = new ReadyQueue();
	if (!table->isEmpty()) {
		ProcessListLink* link = table->begin();
		while (link != NULL) {

			for (int i = 0; i < firstProcSize; i++)
			{
				if (link->proc->id == firstProcs[i]) {
					readyQueue->insertProc(link->proc);
					break; //out of 4
				}
			}

			link = link->nextLink;
		}

	}

	readyQueue->displayQueue();


	std::cout << "Press any to continue..." << std::endl;
	int pause = 0;
	std::cin >> pause;
    return 0;
}

