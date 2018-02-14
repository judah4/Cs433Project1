/*Judah Perez
*2/11/18
* CS 433 Project 1
* Ready Queue with PCB Table.
*/

#include <iostream> 
#include <chrono>
#include "ProcessControlBlock.h"
#include "PcbTable.h"
#include "ReadyQueue.h"

//setup test processes
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

//adding to ready queue
void AddToProcess(PcbTable* table, ReadyQueue* queue, int procs[]) {
	ProcessListLink* link = table->begin();
	while (link != NULL) {
		int sizeOfProcs = sizeof(procs);
		for (int i = 0; i < sizeOfProcs; i++)
		{
			if (link->proc->id == procs[i]) {
				queue->insertProc(link->proc);
				break;
			}
		}

		link = link->nextLink;
	}
}

void PrintTable(PcbTable* table) {
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
}

void Test1() {
	std::cout << "*---Test1---*" << std::endl;
	PcbTable* table = new PcbTable();
	AddTestProcs(table, false);

	int firstProcs[4] = { 5, 1, 8, 11 };
	int secRoundProcs[5] = { 3, 7, 2, 12, 9 };
	std::cout << "--PCB Table--" << std::endl;
	//test print
	PrintTable(table);

	ReadyQueue* readyQueue = new ReadyQueue();
	if (!table->isEmpty()) {
		AddToProcess(table, readyQueue, firstProcs);
	}

	readyQueue->displayQueue();

	ProcessControlBlock* process = readyQueue->removeHighestProc();
	readyQueue->displayQueue();

	AddToProcess(table, readyQueue, secRoundProcs);
	readyQueue->displayQueue();

	while (process != NULL) {
		process = readyQueue->removeHighestProc();
		readyQueue->displayQueue();
	}

}

double Test2(bool printTable, bool randomeSeed) {
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

	//fanct c++11 stuff
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";

	if (printTable) {
		PrintTable(table);
	}

	return elapsed_seconds.count();

}

int main()
{
	std::cout << "Process Control by Judah Perez" << std::endl;
	Test1();
	std::cout << "*---Test2---*" << std::endl;
	std::cout << "1000000 interation test" << std::endl;
	Test2(true, false);
	
	std::cout << "Testing with same seed, 1000000 iterations" << std::endl;
	Test2(false, false);
	Test2(false, false);
	Test2(false, false);
	std::cout << "Testing with random seeds, 1000000 iterations" << std::endl;
	int runsCount = 5;
	double totalTime = 0;
	totalTime += Test2(false, true);
	totalTime += Test2(false, true);
	totalTime += Test2(false, true);
	totalTime += Test2(false, true);
	totalTime += Test2(false, true);

	//generating total
	double averageTime = totalTime / runsCount;
	std::cout << "average elapsed time: " << averageTime << "s\n";
	std::cout << "Press any to continue..." << std::endl;
	int pause = 0;
	std::cin >> pause;
	return 0;
}

