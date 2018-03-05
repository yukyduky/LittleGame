#include "IDHandler.h"



IDHandler::IDHandler() : nrOfIDs(0)
{
}

IDHandler::IDHandler(const size_t size) : nrOfIDs(0)
{
	this->resize(size);
}

void IDHandler::remove(const size_t id)
{
	std::list<size_t>::const_iterator it = this->usedIDs.begin();
	bool idRemoved = false;

	while (!idRemoved && it != this->usedIDs.end())
	{
		if (*it == id)
		{
			idRemoved = true;
			this->usedIDs.erase(it);
			this->availableIDs.push_back(id);
		}
		else
		{
			it++;
		}
	}
}

void IDHandler::remove(std::list<size_t>::const_iterator it)
{
	this->availableIDs.push_back(*it);
	this->usedIDs.erase(it);
}

void IDHandler::resize(const size_t size)
{
	if (size > this->nrOfIDs)
	{
		for (size_t i = this->nrOfIDs; i < size; i++)
		{
			this->availableIDs.push_back(i);
		}
		this->nrOfIDs = size;
	}
}

void IDHandler::clear()
{
	this->availableIDs.clear();
	this->usedIDs.clear();
	this->nrOfIDs = 0;
}

bool IDHandler::idInUse(const size_t id)
{
	bool idFound = false;
	if (id < this->nrOfIDs)
	{
		std::list<size_t>::const_iterator it = this->usedIDs.begin();
		while (!idFound && it != this->usedIDs.end())
		{
			if (*it == id)
			{
				idFound = true;
			}
			it++;
		}
	}
	return idFound;
}

bool IDHandler::empty()
{
	return this->usedIDs.empty();
}

const size_t IDHandler::peekNextID()
{
	size_t id = this->nrOfIDs;
	if (!this->availableIDs.empty())
	{
		id = this->availableIDs.front();
	}
	return id;
}

const size_t IDHandler::getNewID()
{
	size_t id = -1;
	if (!this->availableIDs.empty())
	{
		this->usedIDs.push_back(this->availableIDs.front());
		this->availableIDs.pop_front();
		id = this->usedIDs.back();
	}
	else
	{
		this->usedIDs.push_back(nrOfIDs);
		id = nrOfIDs;
		nrOfIDs++;
	}
	return id;
}

const size_t IDHandler::getNrOfIDs()
{
	return this->nrOfIDs;
}

std::list<size_t>::const_iterator IDHandler::begin() const
{
	return this->usedIDs.begin();
}

std::list<size_t>::const_iterator IDHandler::end() const
{
	return this->usedIDs.end();
}

std::list<size_t>::const_reverse_iterator IDHandler::rbegin() const
{
	return this->usedIDs.rbegin();
}

std::list<size_t>::const_reverse_iterator IDHandler::rend() const
{
	return this->usedIDs.rend();
}
