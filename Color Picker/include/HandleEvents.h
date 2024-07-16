#ifndef HANDLEEVENTS_H
#define HANDLEEVENTS_H

#include <iostream>
#include <string>
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

class HandleEvents
{
private:
	bool isTyped;
	unsigned int unicodeTyped;

	HandleEvents();
	virtual ~HandleEvents();
public:
	static HandleEvents instance;

	void setUnicodeTextEntered(unsigned int sfEvent);
	void setIsTextEntered(const bool isEnter);

	unsigned int getUnicodeTextEntered();
	bool isTextEntered();
};



#endif // !HANDLEEVENTS_H


