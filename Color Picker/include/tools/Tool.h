#ifndef TOOL_H
#define TOOL_H

#include "HandleEvents.h"

enum State
{
	DEFAULT,
	IDLE,
	HOVER,
	ACTIVE,
	UNCHECK,
};

class Tool
{
private:
	static Tool* focus;
	State state;
public:
	Tool();
	virtual ~Tool();

	void setFocus();
	void setState(State state);

	State getState();
};

#endif // !TOOL_H