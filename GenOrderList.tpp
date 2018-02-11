#include "GenOrderList.h"

template<typename T>
void GenOrderNode<T>::add(T* process)
{
	GenNode<T>* node = new GenNode<T>();
	node->data = process;
	if (data == nullptr) {
		data = node;
	}
	else {
		dataLast->next = node;
	}
	dataLast = node;
}

template<typename T>
void GenOrderNode<T>::remove(T* process)
{
	if (data->data == process) {
		data = data->next;
		if (data == nullptr) {
			dataLast = nullptr;
		}
		return;
	}

	GenNode<T>* prev = data;
	GenNode<T>* node = data->next;
	while (node != nullptr) {
		
		if (node->data == process) {
			prev->next = node->next;
			if (prev->next == nullptr) {
				dataLast = prev;
			}
			return;
		}

		prev = node;
		node = node->next;
	}
	
}


template<typename T>
GenOrderList<T>::GenOrderList()
{
	m_link = nullptr;
}

template<typename T>
GenOrderList<T>::~GenOrderList()
{
}

template<typename T>
void GenOrderList<T>::add(T* process, int order) {

	if (m_link == nullptr) {
		m_link = new GenOrderNode<T>(order);
		m_linkLast = m_link;
		m_link->add(process);
		return;
	}

	//new highest priority
	if (order < m_link->order) {
		GenOrderNode<T>* nextLink = m_link;
		m_link = new GenOrderNode<T>(order);
		m_link->next = nextLink;
		m_link->add(process);
		return;
	}
	if (order == m_link->order) {
		m_link->add(process);
		return;
	}

	GenOrderNode<T>* prevLink = m_link;
	GenOrderNode<T>* orderLink = m_link->next;
	while (orderLink != nullptr) {

		if (order == orderLink->order) {
			orderLink->add(process);
			return;
		}
		if (order < orderLink->order) {
			GenOrderNode<T> newLink = new GenOrderNode<T>(order);
			prevLink->next = newLink;
			newLink->next = orderLink;
			newLink->add(process);
			return;
		}

		prevLink = orderLink;
		orderLink = orderLink->next;
	}

	GenOrderNode<T>* newLink = new GenOrderNode<T>(order);
	prevLink->next = newLink;
	newLink->add(process);
	 
	m_linkLast->nextLink = link;
	m_linkLast = link;
	
}
template<typename T>
void GenOrderList<T>::remove(T* process, int order) {

	if (m_link->order == order) {
		m_link->remove(process);

		if (m_link->data == nullptr) {
			m_link = m_link->next;
			if (m_link == nullptr) {
				m_linkLast = nullptr;
			}
		}
		
		return;
	}

	GenOrderNode<T>* prevLink = m_link;
	GenOrderNode<T>* link = m_link->next;
	while (link != nullptr) {
		if (link->order == order) {
			link->remove(process);
			if (m_link->data == nullptr) {
				prevLink->next = link->next;
				if (link->next == nullptr) {
					m_linkLast = prevLink;
				}
			}
			return;
		}

		prevLink = link;
		link->next;
	}

}

template<typename T>
bool GenOrderList<T>::isEmpty() {
	return m_link != nullptr;
}

template<typename T>
GenOrderNode<T>* GenOrderList<T>::begin() {
	return m_link;
}
