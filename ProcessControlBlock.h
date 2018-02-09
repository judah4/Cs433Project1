#ifndef PCB_H   // if x.h hasn't been included yet...
#define PCB_H

enum PcbState {
	NEW, READY, RUNNING, WAITING, TERMINATED
};

struct ProcessControlBlock {
	int id;
	PcbState state;
	int priority;
	ProcessControlBlock() {
		state = PcbState::NEW;
		priority = 1;
	}
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

#endif