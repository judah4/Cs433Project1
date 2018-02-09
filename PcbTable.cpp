#include "PcbTable.h"


PcbTable::PcbTable()
{
	m_empty = true;
	m_link = nullptr;
}


PcbTable::~PcbTable()
{
}

void PcbTable::addProcess(ProcessControlBlock* process) {
	ProcessListLink* link = new ProcessListLink{};
	link->proc = process;
	if (m_empty == true) {
		m_link = link;
		m_empty = false;
		m_linkLast = m_link;
	}
	else {
		m_linkLast->nextLink = link;
		m_linkLast->hasLink = true;
		m_linkLast = link;
	}
}
void PcbTable::removeProcess(ProcessControlBlock* process) {

	if (m_link->proc == process) {
		if (m_link->hasLink) {
			m_link = m_link->nextLink;
		}
		else {
			m_empty = true;
			m_link = nullptr;
			m_linkLast = nullptr;
		}
		return;
	}

	ProcessListLink* prevLink = m_link;

	while (prevLink->hasLink) {
		ProcessListLink* link = prevLink->nextLink;
		if (link->proc == process) {
			if (link == m_linkLast) {
				m_linkLast = prevLink;
			}
			prevLink->hasLink = false;
			prevLink->nextLink = nullptr;

			return;
		}
		
		prevLink = link; //traverse list
	}

}

bool PcbTable::isEmpty() {
	return m_empty;
}


ProcessListLink* PcbTable::begin() {
	return m_link;
}
