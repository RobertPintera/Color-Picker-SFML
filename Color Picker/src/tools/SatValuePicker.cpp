#include "tools/SatValuePicker.h"

void SatValuePicker::initTextureBox()
{
	textureBox.create(width + 1, height + 1);
	imageBox.create(width + 1, height + 1, sf::Color(0, 0, 0, 0));
	updateHueBox(0);
}

void SatValuePicker::initTexturePointer()
{
	int a = 5;
	sf::Image imagePointerShape;
	imagePointerShape.create(5, 5, sf::Color(0, 0, 0, 0));

	for (int i = 1; i < a - 1; i++)
	{
		imagePointerShape.setPixel(i, 0, sf::Color(255, 255, 255));
		imagePointerShape.setPixel(i, a - 1, sf::Color(255, 255, 255));
		imagePointerShape.setPixel(0, i, sf::Color(255, 255, 255));
		imagePointerShape.setPixel(a - 1, i, sf::Color(255, 255, 255));
	}

	texturePointerShape.loadFromImage(imagePointerShape);
}

void SatValuePicker::initBox(float x, float y)
{
	box.setTexture(&textureBox);
	box.setSize(sf::Vector2f(100.f * 360.f / 100.f, 100.f * 360.f / 100.f));
	box.setPosition(x, y);
	
}

void SatValuePicker::initPointer(float x, float y)
{
	pointerShape.setTexture(&texturePointerShape);
	pointerShape.setSize(sf::Vector2f(5.f * 360.f / 100.f, 5.f * 360.f / 100.f));
	pointerShape.setOrigin(pointerShape.getSize().x / 2.f, pointerShape.getSize().y / 2.f);
	pointerShape.setPosition(box.getPosition().x + 361.f, box.getPosition().y);
}

SatValuePicker::SatValuePicker(float x, float y)
{
	height = 255;
	width = 255;
	s = 100;
	v = 100;
	initTextureBox();
	initTexturePointer();
	initBox(x, y);
	initPointer(x, y);
}

SatValuePicker::~SatValuePicker()
{

}

void SatValuePicker::setPositionPicker(uint8_t s, uint8_t v)
{
	if (s > 100)
		this->s = 100;
	else
		this->s = s;

	if (v > 100)
		this->v = 100;
	else
		this->v = v;
	pointerShape.setPosition(box.getPosition().x + this->s * 360.f / 100.f, box.getPosition().y + box.getLocalBounds().width - this->v * 360.f / 100.f);
}

uint8_t SatValuePicker::getSaturation()
{
	return s;
}

uint8_t SatValuePicker::getValue()
{
	return v;
}

sf::Vector2f SatValuePicker::getPosition()
{
	return box.getPosition();
}

sf::Vector2f SatValuePicker::getSize()
{
	return box.getSize();
}

void SatValuePicker::updateHueBox(uint16_t h)
{
	int a = 0, b = 0;
	uint8_t c1 = static_cast<float>(h) / 60.f;
	float c2 = static_cast<float>(h) / 60.f - static_cast<float>(c1);
	for (int i = height; i >= 0; i--)
	{
		for (int j = 0; j <= width; j++)
		{
			a = height - i;
			b = j;
			float sat = j / static_cast<float>(width);
			float val = i / static_cast<float>(height);
			float w1 = val * (1.f - sat);
			float w2 = val * (1.f - sat * c2);
			float w3 = val * (1.f - sat * (1.f - c2));
			switch (c1)
			{
			case 0:
				imageBox.setPixel(b, a, sf::Color(val * 255.f, w3 * 255.f, w1 * 255.f));
				break;
			case 1:
				imageBox.setPixel(b, a, sf::Color(w2 * 255.f, val * 255.f, w1 * 255.f));
				break;
			case 2:
				imageBox.setPixel(b, a, sf::Color(w1 * 255.f, val * 255.f, w3 * 255.f));
				break;
			case 3:
				imageBox.setPixel(b, a, sf::Color(w1 * 255.f, w2 * 255.f, val * 255.f));
				break;
			case 4:
				imageBox.setPixel(b, a, sf::Color(w3 * 255.f, w1 * 255.f, val * 255.f));
				break;
			case 5:
				imageBox.setPixel(b, a, sf::Color(val * 255.f, w1 * 255.f, w2 * 255.f));
				break;
			case 6:
				imageBox.setPixel(b, a, sf::Color(val * 255.f, w3 * 255.f, w1 * 255.f));
				break;
			default:
				break;
			}
		}
	}
	textureBox.update(imageBox);
}



void SatValuePicker::update(const sf::Vector2f& mousePosition)
{
	setState(IDLE);
	if (box.getGlobalBounds().contains(mousePosition))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			setFocus();
			pointerShape.setPosition(mousePosition.x, mousePosition.y);
			s = round((pointerShape.getPosition().x - box.getPosition().x) * 100.f / 360.f);
			v = round((box.getPosition().y + box.getSize().y - pointerShape.getPosition().y) * 100.f / 360.f);
		}
	}
}



void SatValuePicker::render(sf::RenderTarget& target)
{
	target.draw(box);
	target.draw(pointerShape);
}
