#pragma once
#ifndef COMPONENT_H
#define COMPONENT_H

struct Message;
class GameObject;

/* Component pattern */

class Component
{
public:
	virtual const size_t getID() = 0;
	virtual void receive(GameObject & obj, Message msg) = 0;
};

#endif // !COMPONENT_H
