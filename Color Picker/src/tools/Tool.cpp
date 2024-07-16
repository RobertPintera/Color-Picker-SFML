#include "tools/Tool.h"

Tool *Tool::focus;

Tool::Tool()
{
    state = IDLE;
    focus = nullptr;
}

Tool::~Tool()
{
    if (focus == this)
    {
        focus = nullptr;
    }
}

void Tool::setFocus()
{
    if (focus == nullptr)
    {
        focus = this;
        setState(ACTIVE);
    }
    else if(focus != this)
    {
        focus->setState(DEFAULT);
        focus = this;
        setState(ACTIVE);
    }
    else
    {
        setState(ACTIVE);
    }

}

void Tool::setState(State state)
{
    this->state = state;
}

State Tool::getState()
{
    return state;
}


