#include "tools/TextBox.h"


void TextBox::initBox(float x, float y, float width, float height, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor)
{
	shape.setPosition(sf::Vector2f(x, y));
	shape.setSize(sf::Vector2f(width, height));

	this->idleColor = idleColor;
	this->hoverColor = hoverColor;
	this->activeColor = activeColor;
}

void TextBox::initTextAndCursor(float x, float y, int limit, unsigned int fontSize)
{
	selectIndex = 0;
	this->limit = limit;
	text.setPosition(x+10,y);
	text.setCharacterSize(fontSize);
	text.setFillColor(sf::Color(0, 0, 0));

	cursor.setSize(sf::Vector2f(text.getCharacterSize()/16.f,text.getCharacterSize()));
	cursor.setFillColor(sf::Color(0, 0, 0, 0));
	cursor.setPosition(x+12, y+5);
}

void TextBox::initFont(sf::Font& font)
{
	this->font = &font;
	text.setFont(font);
}

void TextBox::deleteCharacter()
{
	if (selectIndex > 0)
	{
		selectIndex--;
		textString.erase(selectIndex, 1);
	}
}

TextBox::TextBox(float x, float y, float width, float height, sf::Font* font, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor, int limit, unsigned int fontSize)
{
	initBox(x,y,width,height,idleColor,hoverColor,activeColor);
	initFont(*font);
	initTextAndCursor(x, y, limit, fontSize);
	
}

TextBox::~TextBox()
{
	font = nullptr;
}

void TextBox::setCursor()
{
	float textWidth = text.getLocalBounds().width;
	cursor.setFillColor(sf::Color(0, 0, 0,255));
	cursor.setPosition(text.getPosition().x+ textWidth + 2, cursor.getPosition().y);
}

void TextBox::setText(std::string text)
{
	textString = text;
	this->text.setString(textString);
	selectIndex = textString.getSize();
}

std::string TextBox::getText()
{
	return text.getString();
}

bool TextBox::getIsTextEntered()
{
	return HandleEvents::instance.isTextEntered() && getState()  == ACTIVE;
}


void TextBox::update(const sf::Vector2f mousePosition)
{
	if(getState() == DEFAULT)
	{
		setState(UNCHECK);
	}
	else if (getState() != ACTIVE)
	{
		setState(IDLE);
		if (shape.getGlobalBounds().contains(mousePosition))
		{
			setState(HOVER);

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				setFocus();
			}
		}
	}
	else
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (!shape.getGlobalBounds().contains(mousePosition))
			{
				setState(UNCHECK);
			}
		}
	}
	
	switch (getState())
	{
	case IDLE:
		shape.setFillColor(idleColor);
		break;
	case HOVER:
		shape.setFillColor(hoverColor);
		break;
	case ACTIVE:
		shape.setFillColor(activeColor);

		if (HandleEvents::instance.isTextEntered())
		{
			int charTyped = HandleEvents::instance.getUnicodeTextEntered();
			if (textString.getSize() <= limit && charTyped != ENTER_KEY)
			{
				if (charTyped != DELETE_KEY)
				{
					textString.insert(selectIndex, HandleEvents::instance.getUnicodeTextEntered());
					selectIndex++;
				}
				else
				{
					deleteCharacter();
				}
			}
			else if (textString.getSize() > limit && charTyped == DELETE_KEY)
			{
				deleteCharacter();
			}

			text.setString(textString);
		}
		setCursor();
		break;
	case UNCHECK:
		cursor.setFillColor(sf::Color(255, 0, 0, 0));
		break;
	default:
		shape.setFillColor(idleColor);
		break;
	}

	
}


void TextBox::render(sf::RenderTarget& target)
{
	target.draw(shape);
	target.draw(text);
	target.draw(cursor);
}
