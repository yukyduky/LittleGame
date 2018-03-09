#pragma once
#ifndef IDLIST_H
#define IDLIST_H

#include <list>
#include <vector>
#include <unordered_map>
#include <queue>
#include <functional>

template<class T>
class idlist
{
private:
	std::list<size_t> m_AvailableIDs;
	std::priority_queue<size_t, std::vector<size_t>, std::greater<size_t>> m_AvailableIndexes;
	std::unordered_map<size_t, size_t> m_IDToIndex;
	std::unordered_map<size_t, size_t> m_IndexToID;
	std::vector<typename T> m_Container;
	size_t m_NrOfElements;
public:
	idlist();
	idlist(const size_t size);

	size_t push(typename T element);
	void remove(const size_t id);
	void resize(const size_t size);
	void reserve(const size_t size);
	size_t capacity();
	void clear();
	T& getElementByID(const size_t id);
	bool empty();
	size_t size();
	T* data();
	size_t peekNextID();

	T& operator[](size_t id);
};

template<class T>
inline idlist<T>::idlist() : m_NrOfElements(0)
{
}

template<class T>
inline idlist<T>::idlist(const size_t size) : idlist()
{
	this->resize(size);
}

template<class T>
inline size_t idlist<T>::push(typename T element)
{
	size_t index = m_NrOfElements;
	size_t id = index;

	if (m_AvailableIDs.empty()) 
	{
		m_Container.push_back(element);
		m_IDToIndex.insert(m_IDToIndex.end(), std::pair<size_t, size_t>(id, index));
		m_IndexToID.insert(m_IndexToID.end(), std::pair<size_t, size_t>(index, id));
	}
	else 
	{
		id = m_AvailableIDs.front();
		m_AvailableIDs.pop_front();
		index = m_AvailableIndexes.top();
		m_AvailableIndexes.pop();

		m_Container[index] = element;
		m_IDToIndex[id] = index;
		m_IndexToID[index] = id;
	}

	m_NrOfElements++;

	return id;
}

template<class T>
inline void idlist<T>::remove(const size_t id)
{
	size_t lastIndex = m_NrOfElements - m_AvailableIDs.size() - 1;

	if (lastIndex == 0)
	{
		m_IDToIndex.erase(id);
		m_IndexToID.erase(lastIndex);
		m_AvailableIDs.push_front(id);
		m_AvailableIndexes.push(lastIndex);
		m_NrOfElements--;
	}
	else if (lastIndex != static_cast<size_t>(-1))
	{
		// Get the index of the id to remove
		size_t holeIndex = m_IDToIndex.at(id);

		m_Container[holeIndex] = m_Container[lastIndex];

		m_IDToIndex[m_IndexToID[lastIndex]] = holeIndex;
		m_IndexToID[holeIndex] = m_IndexToID[lastIndex];

		m_IDToIndex.erase(id);
		m_IndexToID.erase(lastIndex);
		m_AvailableIDs.push_front(id);
		m_AvailableIndexes.push(lastIndex);
		m_NrOfElements--;
	}
}

template<class T>
inline void idlist<T>::resize(const size_t size)
{
	if (size > m_Container.size()) 
	{
		m_Container.resize(size);
		for (size_t i = m_NrOfElements; i < size; i++)
		{
			m_AvailableIDs.push_back(i);
			m_AvailableIndexes.push(i);
			m_IDToIndex.insert(m_IDToIndex.end(), std::pair<size_t, size_t>(i, i));
			m_IndexToID.insert(m_IndexToID.end(), std::pair<size_t, size_t>(i, i));
		}
		m_NrOfElements = size;
	}
}

template<class T>
inline void idlist<T>::reserve(const size_t size)
{
	m_Container.reserve(size);
	m_IDToIndex.reserve(size);
	m_IndexToID.reserve(size);
}

template<class T>
inline size_t idlist<T>::capacity()
{
	return m_Container.capacity();
}

template<class T>
inline void idlist<T>::clear()
{
	m_Container.clear();
	m_IDToIndex.clear();
	m_IndexToID.clear();
	m_AvailableIDs.clear();

	for (size_t i = 0; i < m_AvailableIndexes.size(); i++)
	{
		m_AvailableIndexes.pop();
	}
}

template<class T>
inline T& idlist<T>::getElementByID(const size_t id)
{
	return m_Container[m_IDToIndex.at(id)]; // TODOYE: Throw own exception
}

template<class T>
inline bool idlist<T>::empty()
{
	return m_IDToIndex.empty();
}

template<class T>
inline size_t idlist<T>::size()
{
	return m_NrOfElements;
}

template<class T>
inline T* idlist<T>::data()
{
	return m_Container.data();
}

template<class T>
inline size_t idlist<T>::peekNextID()
{
	return m_AvailableIDs.front();
}

template<class T>
inline T& idlist<T>::operator[](size_t index)
{
	if (index >= m_NrOfElements)
	{
		throw("idlist - Subscript out of range");
	}

	return m_Container[index];
}

#endif
