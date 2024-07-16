#include "tools/Label.h"

void Label::initText(float x, float y, sf::Color colorText, unsigned int fontSize, std::string text)
{
	this->text.setPosition(x, y);
	this->text.setCharacterSize(fontSize);
	this->text.setString(text);
	this->text.setFillColor(colorText);
}

void Label::initFont(sf::Font& font)
{
	text.setFont(font);
}

Label::Label(float x, float y, sf::Font* font, sf::Color colorText, unsigned int fontSize, std::string text)
{
	initText(x, y, colorText, fontSize, text);
	initFont(*font);
}

Label::~Label()
{
	font = nullptr;
}

void Label::setText(std::string text)
{
	this->text.setString(text);
}

void Label::update()
{
}

void Label::render(sf::RenderTarget& target)
{
	target.draw(text);
}
