#pragma once
enum PcbState { NEW, READY, RUNNING, WAITING, TERMINATED
};

class ProcessControlBlock
{
private:
	int m_id;
	PcbState m_state;
public:
	ProcessControlBlock(int id);
	~ProcessControlBlock();
	int getId();
	PcbState getState();
	char const* getStateName();
};

