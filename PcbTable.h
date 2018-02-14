#pragma once

#include "ProcessControlBlock.h"

struct ProcessListLink {
	ProcessControlBlock* proc;
	ProcessListLink* nextLink;
	bool hasLink;
	ProcessListLink() {
		hasLink = false;
		nextLink = nullptr;
	}
};

//pcb table with its own link list implentation. I did this first.
class PcbTable
{
private:
	
	ProcessListLink* m_link;
	ProcessListLink* m_linkLast;
	bool m_empty;
public:
	PcbTable();
	~PcbTable();
	void addProcess(ProcessControlBlock* process);
	void removeProcess(ProcessControlBlock* process);
	bool isEmpty();
	ProcessListLink* begin();
};

