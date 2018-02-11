#include "ReadyQueue.h"
#include "ProcessControlBlock.h"
#include "GenOrderList.h"
#include <iostream>


ReadyQueue::ReadyQueue()
{
	m_list = new GenOrderList<ProcessControlBlock>();
}


ReadyQueue::~ReadyQueue()
{
}

void ReadyQueue::insertProc(ProcessControlBlock* proc) {
	m_list->add(proc, proc->priority);
	proc->state = PcbState::READY;
}
ProcessControlBlock* ReadyQueue::removeHighestProc() {
	ProcessControlBlock* first = m_list->begin()->data->data;
	m_list->remove(first, first->priority);
	first->state = PcbState::RUNNING;
	return first;
}
int ReadyQueue::size() {
	int count = 0;
	GenOrderNode<ProcessControlBlock>* link = m_list->begin();
	while (link != nullptr) {
		GenNode<ProcessControlBlock>* innerNode = link->data;
		while (innerNode != nullptr) {
			count++;
			innerNode = innerNode->next;
		}

		link = link->next;
	}
	return count;
}

void ReadyQueue::displayQueue() {
	std::cout << "--Ready Queue--" << std::endl;
	GenOrderNode<ProcessControlBlock>* link = m_list->begin();
	while (link != nullptr) {
		GenNode<ProcessControlBlock>* innerNode = link->data;
		while (innerNode != nullptr) {
			innerNode->data->print();
			innerNode = innerNode->next;
		}

		link = link->next;
	}


	

}