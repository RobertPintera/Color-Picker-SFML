#ifndef APP_H
#define APP_H

#include "tools/TextBox.h"
#include "tools/SatValuePicker.h"
#include "tools/HuePicker.h"
#include "tools/Label.h"
#include "ColorHSV.h"

#define INIT_HUE 0
#define INIT_SATURATION 100
#define INIT_VALUE 100

class App
{
private:
	//Window
	sf::RenderWindow window;
	sf::Event sfEvent;

	//Font
	sf::Font font;

	//Mouse Position
	sf::Vector2i mousePositionScreen;
	sf::Vector2i mousePositionWindow;
	sf::Vector2f mousePositionView;

	//Tools
	sf::RectangleShape* colorShow;
	SatValuePicker* colorSVPicker;
	HuePicker* huePicker;
	std::map<std::string, Label*> labels;
	std::map<std::string,TextBox*> textBoxes;
	
	sf::Color colorRGB;

	void initVariables();
	void initWindow();
	void initFont();
	void initTools();
public:
	App();
	virtual ~App();
	
	int stringToInt(std::string str);
	ColorHSV convertRGBToHSV(float r, float g, float b);
	sf::Color convertHSVToRGB(uint16_t h, uint8_t s, uint8_t v);

	void updateEvents();
	void updateMousePosition();
	void updateTools();
	void update();

	void renderTools();
	void render();

	void run();
};


#endif // !APP_H