// Judah Perez
// 2/4/2018
//CS 433 Project 1
// Priority Queue of Processes

#include <iostream> 
#include "ProcessControlBlock.h"

int main()
{
	std::cout << "Process Control" << std::endl;

	ProcessControlBlock* firstBlock = new ProcessControlBlock(1);

	std::cout << "Id:" << firstBlock->getId() << " State:" << firstBlock->getStateName() << std::endl;

	std::cout << "Press any to continue..." << std::endl;
	int pause = 0;
	std::cin >> pause;
    return 0;
}

