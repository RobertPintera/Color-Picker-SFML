#ifndef SATVALUEPICKER_H
#define SATVALUEPICKER_H

#include "Tool.h"

class SatValuePicker : public Tool
{
private:
	unsigned short height;
	unsigned short width;
	sf::Image imageBox;
	sf::RectangleShape box;
	sf::RectangleShape pointerShape;
	sf::Texture textureBox;
	sf::Texture texturePointerShape;
	
	uint8_t s;
	uint8_t v;

	void initTextureBox();
	void initTexturePointer();
	void initBox(float x, float y);
	void initPointer(float x, float y);
public:
	SatValuePicker(float x, float y);
	virtual ~SatValuePicker();

	void setPositionPicker(uint8_t s, uint8_t v);

	uint8_t getSaturaion();
	uint8_t getValue();
	sf::Vector2f getPosition();
	sf::Vector2f getSize();

	void updateBox(uint16_t h);
	void update(const sf::Vector2f mousePosition);
	void render(sf::RenderTarget& target);
};

#endif // !SATVALUEPICKER_H