#ifndef PCB_H   // if x.h hasn't been included yet...
#define PCB_H

#include <iostream>

enum PcbState {
	NEW, READY, RUNNING, WAITING, TERMINATED
};

static char const* StateName(PcbState state) {
	switch (state)
	{
	case PcbState::NEW:
		return "NEW";
	case PcbState::READY:
		return "READY";
	case PcbState::RUNNING:
		return "RUNNING";
	case PcbState::WAITING:
		return "WAITING";
	case PcbState::TERMINATED:
		return "TERMINATED";
	}
	return "UNKNOWN";
}
//process control block, holds state and simple data(there is no data)
struct ProcessControlBlock {
	int id;
	PcbState state;
	int priority;
	void print() {
		std::cout << "Id:" << id << " State:" << StateName(state) << " Priority:" << priority << std::endl;

	}
	ProcessControlBlock() {
		state = PcbState::NEW;
		priority = 1;
	}
};



#endif