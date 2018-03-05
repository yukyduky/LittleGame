#pragma once
#ifndef IDHANDLER_H
#define IDHANDLER_H

#include <list>

class IDHandler
{
private:
	size_t nrOfIDs;
	std::list<size_t> usedIDs;
	std::list<size_t> availableIDs;
public:
	IDHandler();
	IDHandler(const size_t size);

	void remove(const size_t id);
	void remove(std::list<size_t>::const_iterator it);
	void resize(const size_t size);
	void clear();
	bool idInUse(const size_t id);
	bool empty();
	const size_t peekNextID();

	const size_t getNewID();
	const size_t getNrOfIDs();

	std::list<size_t>::const_iterator begin() const;
	std::list<size_t>::const_iterator end() const;
	std::list<size_t>::const_reverse_iterator rbegin() const;
	std::list<size_t>::const_reverse_iterator rend() const;
};

#endif // IDHANDLER_H
