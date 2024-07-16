#ifndef LABEL_H
#define LABEL_H

#include "Tool.h"

class Label : public Tool
{
private:
	sf::Font* font;
	sf::Text text;

	void initText(float x, float y, sf::Color colorText, unsigned int fontSize, std::string text);
	void initFont(sf::Font& font);
public:
	Label(float x, float y, sf::Font* font, sf::Color colorText, unsigned int fontSize, std::string text);
	virtual ~Label();

	void setText(std::string text);

	void update();
	void render(sf::RenderTarget& target);
};

#endif // !LABEL_H