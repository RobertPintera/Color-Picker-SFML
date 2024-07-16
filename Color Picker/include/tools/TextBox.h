#ifndef TEXTBOX_H
#define TEXTBOX_H

#define DELETE_KEY 8
#define ENTER_KEY 13

#include "Tool.h"

class TextBox : public Tool
{
private:
	sf::RectangleShape shape;
	sf::RectangleShape cursor;

	sf::Text text;
	sf::Font* font;
	sf::String textString;

	int limit;
	int selectIndex;

	sf::Color idleColor;
	sf::Color hoverColor;
	sf::Color activeColor;


	void initBox(float x, float y, float width, float height, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor);
	void initTextAndCursor(float x, float y, int limit, unsigned int fontSize);
	void initFont(sf::Font& font);

	void deleteCharacter();
public:
	TextBox(float x, float y, float width, float height, sf::Font* font, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor, int limit, unsigned int fontSize);
	virtual ~TextBox();

	//Setters
	void setCursor();
	void setText(std::string text);

	//Getters
	std::string getText();
	bool getIsTextEntered();

	void update(const sf::Vector2f mousePosition);
	void render(sf::RenderTarget& target);
};

#endif // !TEXTBOX_H