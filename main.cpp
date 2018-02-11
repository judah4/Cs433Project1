// Judah Perez
// 2/4/2018
//CS 433 Project 1
// Priority Queue of Processes

#include <iostream> 
#include <chrono>
#include "ProcessControlBlock.h"
#include "PcbTable.h"
#include "ReadyQueue.h"

void AddTestProcs(PcbTable* table, bool randomSeed) {
	if (randomSeed) {
		srand(time(NULL));
	}
	else {
		srand(40404);
	}
	

	int id = 1;

	for (int i = 0; i < 20; i++)
	{
		ProcessControlBlock* firstBlock = new ProcessControlBlock{};
		firstBlock->id = id++;
		firstBlock->state = PcbState::NEW;
		firstBlock->priority = rand() % 50;
		table->addProcess(firstBlock);
	}

}

void AddToProcess(PcbTable* table, ReadyQueue* queue, int procs[]) {
	ProcessListLink* link = table->begin();
	while (link != NULL) {

		for (int i = 0; i < sizeof(procs); i++)
		{
			if (link->proc->id == procs[i]) {
				queue->insertProc(link->proc);
				break;
			}
		}

		link = link->nextLink;
	}
}

void Test1() {
	PcbTable* table = new PcbTable();
	AddTestProcs(table, false);

	int firstProcs[4] = { 5, 1, 8, 11 };
	int secRoundProcs[5] = { 3, 7, 2, 12, 9 };
	std::cout << "--PCB Table--" << std::endl;
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
		AddToProcess(table, readyQueue, firstProcs);
	}

	readyQueue->displayQueue();

	ProcessControlBlock* process = readyQueue->removeHighestProc();
	readyQueue->displayQueue();

	AddToProcess(table, readyQueue, secRoundProcs);
	readyQueue->displayQueue();

	while (process != nullptr) {
		process = readyQueue->removeHighestProc();
		readyQueue->displayQueue();
	}

}

void Test2(bool printTable, bool randomeSeed) {
	PcbTable* table = new PcbTable();
	AddTestProcs(table, randomeSeed);
	ReadyQueue* readyQueue = new ReadyQueue();

	int startIndex = rand() % 20;
	int total = 20;
	for (int cnt = startIndex; cnt < total + startIndex; cnt++)
	{
		int index = cnt % total;
		AddToProcess(table, readyQueue, new int[1]{ index });
	}
	if (printTable) {
		readyQueue->displayQueue();
	}
	//c++11 goodness
	auto start = std::chrono::system_clock::now();

	for (int cnt = 0; cnt < 1000000; cnt++)
	{
		//so many iterations
		if (rand() % 2 == 1) {
			//remove
			readyQueue->removeHighestProc();
		}
		else {
			//add
			ProcessListLink* link = table->begin();
			while (link != NULL) {
				if (link->proc->state == PcbState::NEW) {
					readyQueue->insertProc(link->proc);
					break;
				}

				link = link->nextLink;
			}
		}
	}
	
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
}

int main()
{
	std::cout << "Process Control by Judah Perez" << std::endl;
	Test1();
	std::cout << "1000000 interation test" << std::endl;
	Test2(true, false);
	std::cout << "Testing with same seed, 1000000 iterations" << std::endl;
	Test2(false, false);
	Test2(false, false);
	Test2(false, false);
	std::cout << "Testing with randome seeds, 1000000 iterations" << std::endl;
	Test2(false, true);
	Test2(false, true);
	Test2(false, true);
	std::cout << "Press any to continue..." << std::endl;
	int pause = 0;
	std::cin >> pause;
    return 0;
}

