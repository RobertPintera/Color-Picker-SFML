#ifndef HUEPICKER_H
#define HUEPICKER_H

#include "Tool.h"

class HuePicker : public Tool
{
private:
	sf::RectangleShape hueBox;
	sf::RectangleShape pointerHue;
	sf::Texture textureBox;
	sf::Texture texturePointerHue;

	uint16_t h;

	void initTextureBox();
	void initTexturePointer();
	void initBox(float x, float y);
	void initPointer(float x, float y);
public:
	HuePicker(float x, float y);
	virtual ~HuePicker();

	//Setters
	void setPositionPointer(uint16_t h);

	//Getters
	uint16_t getHue();
	
	//Functions
	void update(const sf::Vector2f& mousePosition);
	void render(sf::RenderTarget& target);
};

#endif // !HUEPICKER_H