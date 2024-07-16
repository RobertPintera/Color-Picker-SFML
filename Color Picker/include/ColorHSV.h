#ifndef COLORHSV_H
#define COLORHSV_H

#include "HandleEvents.h"

class ColorHSV
{
private:
	uint16_t h;
	uint8_t s;
	uint8_t v;
public:
	ColorHSV();
	ColorHSV(uint16_t h, uint8_t s, uint8_t v);
	virtual ~ColorHSV();

	uint16_t getHue();
	uint8_t getSaturation();
	uint8_t getValue();
};


#endif // !COLORHSV_H