#include "HandleEvents.h"


HandleEvents HandleEvents::instance;

HandleEvents::HandleEvents()
{
    isTyped = false;
    unicodeTyped = 0;
}

HandleEvents::~HandleEvents()
{
}


void HandleEvents::setUnicodeTextEntered(unsigned int unicode)
{
    unicodeTyped = unicode;
}

void HandleEvents::setIsTextEntered(const bool isEnter)
{
    isTyped = isEnter;
}

unsigned int HandleEvents::getUnicodeTextEntered()
{
    return unicodeTyped;
}

bool HandleEvents::isTextEntered()
{
    return isTyped;
}
