#include "ColorHSV.h"

ColorHSV::ColorHSV()
{
	h = 0;
	s = 0;
	v = 0;
}

ColorHSV::ColorHSV(uint16_t h, uint8_t s, uint8_t v)
{
	this->h = h;
	this->s = s;
	this->v = v;
}

ColorHSV::~ColorHSV()
{
}

uint16_t ColorHSV::getHue()
{
	return h;
}

uint8_t ColorHSV::getSaturation()
{
	return s;
}

uint8_t ColorHSV::getValue()
{
	return v;
}
