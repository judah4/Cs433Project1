#include "ProcessControlBlock.h"


ProcessControlBlock::ProcessControlBlock(int id)
{
	m_id = id;
	m_state = PcbState::NEW;
}

ProcessControlBlock::~ProcessControlBlock()
{
}

int ProcessControlBlock::getId() {
	return m_id;
}

PcbState ProcessControlBlock::getState() {
	return m_state;
}

char const* ProcessControlBlock::getStateName() {
	switch (m_state)
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