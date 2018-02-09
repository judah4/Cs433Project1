// Judah Perez
// 2/4/2018
//CS 433 Project 1
// Priority Queue of Processes

#include <iostream> 
#include "ProcessControlBlock.h"
#include "PcbTable.h"

void AddTestProcs(PcbTable* table) {
	int id = 1;

	for (int i = 0; i < 5; i++)
	{
		ProcessControlBlock* firstBlock = new ProcessControlBlock{};
		firstBlock->id = id;
		id += 3;
		firstBlock->state = PcbState::NEW;
		table->addProcess(firstBlock);
	}

}

int main()
{
	std::cout << "Process Control" << std::endl;

	PcbTable* table = new PcbTable();
	AddTestProcs(table);
	

	if (!table->isEmpty()) {
		ProcessListLink* link = table->begin();
		while (link != NULL) {
			ProcessControlBlock* firstBlock = link->proc;
			std::cout << "Id:" << firstBlock->id << " State:" << StateName(firstBlock->state) << std::endl;
			link = link->nextLink;
		}

	}

	std::cout << "Press any to continue..." << std::endl;
	int pause = 0;
	std::cin >> pause;
    return 0;
}

