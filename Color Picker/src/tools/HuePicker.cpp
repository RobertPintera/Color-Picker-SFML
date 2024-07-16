#include "tools/HuePicker.h"

void HuePicker::initTextureBox()
{
	sf::Image imageHue;
	imageHue.create(361, 1, sf::Color(0, 0, 0, 0));

	for (int i = 0; i <= 360; i++)
	{
		int normalized = int((i / 360.f) * 256 * 6);
		int region = normalized / 256;
		int x = normalized % 256;
		uint8_t r = 0, g = 0, b = 0;
		switch (region)
		{
		case 0: r = 255; g = 0;   b = 0;   g += x; break;
		case 1: r = 255; g = 255; b = 0;   r -= x; break;
		case 2: r = 0;   g = 255; b = 0;   b += x; break;
		case 3: r = 0;   g = 255; b = 255; g -= x; break;
		case 4: r = 0;   g = 0;   b = 255; r += x; break;
		case 5: r = 255; g = 0;   b = 255; b -= x; break;
		default:
			break;
		}

		imageHue.setPixel(i, 0, sf::Color(r, g, b));
	}

	textureBox.loadFromImage(imageHue);
}

void HuePicker::initTexturePointer()
{
	int a = 5, b = 27;
	sf::Image imagePointerHue;
	imagePointerHue.create(a, b, sf::Color(0, 0, 0, 0));

	for (int i = 0; i < a; i++)
	{
		imagePointerHue.setPixel(i, 0, sf::Color(255, 255, 255));
		imagePointerHue.setPixel(i, b - 1, sf::Color(255, 255, 255));
	}
	for (int i = 1; i < b; i++)
	{
		imagePointerHue.setPixel(0, i, sf::Color(255, 255, 255));
		imagePointerHue.setPixel(a - 1, i, sf::Color(255, 255, 255));
	}

	texturePointerHue.loadFromImage(imagePointerHue);
}

void HuePicker::initBox(float x, float y)
{
	hueBox.setTexture(&textureBox);
	hueBox.setSize(sf::Vector2f(360.f, 50.f));
	hueBox.setPosition(x, y);
}

void HuePicker::initPointer(float x, float y)
{
	pointerHue.setTexture(&texturePointerHue);
	pointerHue.setSize(sf::Vector2f(10.f, 54.f));
	pointerHue.setOrigin(pointerHue.getSize().x / 2.f + 1.f, 0.f);
	pointerHue.setPosition(hueBox.getPosition().x, hueBox.getPosition().y - 2);
}

HuePicker::HuePicker(float x, float y)
{
	h = 0;
	initTextureBox();
	initTexturePointer();
	initBox(x, y);
	initPointer(x, y);
}

HuePicker::~HuePicker()
{
}

void HuePicker::setPositionPointer(uint16_t h)
{
	if (h > 360)
		this->h = 360;
	else
		this->h = h;
	
	pointerHue.setPosition(hueBox.getPosition().x + this->h, pointerHue.getPosition().y);
}

uint16_t HuePicker::getHue()
{
	return h;
}

void HuePicker::update(const sf::Vector2f mousePosition)
{
	setState(IDLE);
	if (hueBox.getGlobalBounds().contains(mousePosition))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			setFocus();
			pointerHue.setPosition(mousePosition.x, pointerHue.getPosition().y);
			h = round(pointerHue.getPosition().x - hueBox.getPosition().x);
		}
	}
}

void HuePicker::render(sf::RenderTarget& target)
{
	target.draw(hueBox);
	target.draw(pointerHue);
}
