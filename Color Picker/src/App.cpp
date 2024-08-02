#include "App.h"

void App::initVariables()
{
	this->colorRGB = sf::Color(0, 0, 0);
}

void App::initWindow()
{
	window.create(sf::VideoMode(1024, 600), "Color Picker", sf::Style::Default);
	window.setFramerateLimit(60);
}

void App::initFont()
{
	font.loadFromFile("Fonts/RPixerick.ttf");
}

void App::initTools()
{
	colorSVPicker = new SatValuePicker(100, 50);
	colorSVPicker->setPositionPicker(INIT_SATURATION, INIT_VALUE);

	huePicker = new HuePicker(100, 50 + colorSVPicker->getSize().y + 50);
	huePicker->setPositionPointer(INIT_HUE);

	colorSVPicker->updateHueBox(huePicker->getHue());
	
	labels["H"] = new Label(620, 50, &font, sf::Color(255, 255, 255), 32, "H");
	labels["S"] = new Label(620, 170, &font, sf::Color(255, 255, 255), 32, "S");
	labels["V"] = new Label(620, 290, &font, sf::Color(255, 255, 255), 32, "V");
	labels["R"] = new Label(840, 50, &font, sf::Color(255, 255, 255), 32, "R");
	labels["G"] = new Label(840, 170, &font, sf::Color(255, 255, 255), 32, "G");
	labels["B"] = new Label(840, 290, &font, sf::Color(255, 255, 255), 32, "B");

	textBoxes["H"] = new TextBox(550, 100, 150, 50, &font, sf::Color(255, 255, 255), sf::Color(181, 181, 181), sf::Color(181, 181, 181), 10, 32);
	textBoxes["H"]->setText(std::to_string(huePicker->getHue()));
	textBoxes["S"] = new TextBox(550, 220, 150, 50, &font, sf::Color(255, 255, 255), sf::Color(181, 181, 181), sf::Color(181, 181, 181), 10, 32);
	textBoxes["S"]->setText(std::to_string(colorSVPicker->getSaturation()));
	textBoxes["V"] = new TextBox(550, 340, 150, 50, &font, sf::Color(255, 255, 255), sf::Color(181, 181, 181), sf::Color(181, 181, 181), 10, 32);
	textBoxes["V"]->setText(std::to_string(colorSVPicker->getValue()));

	sf::Color colorRGB = convertHSVToRGB(huePicker->getHue(), colorSVPicker->getSaturation(), colorSVPicker->getValue());
	
	textBoxes["R"] = new TextBox(770, 100, 150, 50, &font, sf::Color(255, 255, 255), sf::Color(181, 181, 181), sf::Color(181, 181, 181), 10, 32);
	textBoxes["R"]->setText(std::to_string(colorRGB.r));
	textBoxes["G"] = new TextBox(770, 220, 150, 50, &font, sf::Color(255, 255, 255), sf::Color(181, 181, 181), sf::Color(181, 181, 181), 10, 32);
	textBoxes["G"]->setText(std::to_string(colorRGB.g));
	textBoxes["B"] = new TextBox(770, 340, 150, 50, &font, sf::Color(255, 255, 255), sf::Color(181, 181, 181), sf::Color(181, 181, 181), 10, 32);
	textBoxes["B"]->setText(std::to_string(colorRGB.b));

	colorShow = new sf::RectangleShape();
	colorShow->setSize(sf::Vector2f(370, 50));
	colorShow->setPosition(550, 460);
	colorShow->setFillColor(colorRGB);
}

App::App()
{
	initWindow();
	initVariables();
	initFont();
	initTools();
}

App::~App()
{
	delete colorShow;
	colorShow = nullptr;
	delete colorSVPicker;
	colorSVPicker = nullptr;
	delete huePicker;
	huePicker = nullptr;

	for (auto i = this->textBoxes.begin(); i != this->textBoxes.end(); i++)
	{
		delete i->second;
		i->second = nullptr;
	}

	for (auto i = this->labels.begin(); i != this->labels.end(); i++)
	{
		delete i->second;
		i->second = nullptr;
	}
}

int App::stringToInt(std::string str)
{
	int num = 0;
	try
	{
		num = std::stoi(str);
	}
	catch (const std::exception& e)
	{
		num = 0;
	}

	return num;
}

ColorHSV App::convertRGBToHSV(float r, float g, float b)
{
	r = r / 255.f;
	g = g / 255.f;
	b = b / 255.f;

	double xmax = std::max(r, std::max(g, b)); //Value
	double xmin = std::min(r, std::min(g, b));
	double c = xmax - xmin;
	double h = 0, s = 0; //Hue, Saturation

	if (c == 0)
		h = 0;
	else if (xmax == r)
		h = fmod(60 * ((g - b) / c) + 0, 360);
	else if (xmax == g)
		h = fmod(60 * ((b - r) / c) + 120, 360);
	else if (xmax == b)
		h = fmod(60 * ((r - g) / c) + 240, 360);

	if (h < 0)
		h = h + 360;

	if (xmax == 0)
		s = 0;
	else
		s = (c / xmax) * 100;

	double v = xmax * 100.f;

	return ColorHSV(h, s, v);
}

sf::Color App::convertHSVToRGB(uint16_t h, uint8_t s, uint8_t v)
{
	uint8_t h1 = static_cast<float>(h) / 60.f;
	float h2 = static_cast<float>(h) / 60.f - static_cast<float>(h1);
	float sat = static_cast<float>(s) / 100.f;
	float val = static_cast<float>(v) / 100.f;
	float w1 = val * (1.f - sat);
	float w2 = val * (1.f - sat * h2);
	float w3 = val * (1.f - sat * (1.f - h2));
	if (h1 == 0)
		return sf::Color(val * 255.f, w3 * 255.f, w1 * 255.f);
	else if (h1 == 1)
		return sf::Color(w2 * 255.f, val * 255.f, w1 * 255.f);
	else if (h1 == 2)
		return sf::Color(w1 * 255.f, val * 255.f, w3 * 255.f);
	else if (h1 == 3)
		return sf::Color(w1 * 255.f, w2 * 255.f, val * 255.f);
	else if (h1 == 4)
		return sf::Color(w3 * 255.f, w1 * 255.f, val * 255.f);
	else if (h1 == 5)
		return sf::Color(val * 255.f, w1 * 255.f, w2 * 255.f);
	else if (h1 == 6)
		return sf::Color(val * 255.f, w3 * 255.f, w1 * 255.f);

	return sf::Color(0, 0, 0);
}


void App::updateEvents()
{
	HandleEvents::instance.setIsTextEntered(false);
	while (window.pollEvent(sfEvent))
	{
		if (sfEvent.type == sf::Event::Closed)
		{
			window.close();
		}
		else if (sfEvent.type == sf::Event::TextEntered)
		{
			HandleEvents::instance.setUnicodeTextEntered(sfEvent.text.unicode);
			HandleEvents::instance.setIsTextEntered(true);
		}
	}

}

void App::updateMousePosition()
{
	mousePositionScreen = sf::Mouse::getPosition();
	mousePositionWindow = sf::Mouse::getPosition(window);
	mousePositionView = window.mapPixelToCoords(sf::Mouse::getPosition(window));
}

void App::updateTools()
{
	colorSVPicker->update(mousePositionView);
	huePicker->update(mousePositionView);

	if (colorSVPicker->getState() == ACTIVE || huePicker->getState() == ACTIVE)
	{
		textBoxes["H"]->setText(std::to_string(huePicker->getHue()));
		textBoxes["S"]->setText(std::to_string(colorSVPicker->getSaturation()));
		textBoxes["V"]->setText(std::to_string(colorSVPicker->getValue()));
		colorSVPicker->updateHueBox(huePicker->getHue());
		colorRGB = convertHSVToRGB(huePicker->getHue(), colorSVPicker->getSaturation(), colorSVPicker->getValue());
		textBoxes["R"]->setText(std::to_string(colorRGB.r));
		textBoxes["G"]->setText(std::to_string(colorRGB.g));
		textBoxes["B"]->setText(std::to_string(colorRGB.b));
		colorShow->setFillColor(colorRGB);
	}

	for (auto& i : textBoxes)
	{
		i.second->update(mousePositionView);
		if (i.second->getState() == UNCHECK)
		{
			if(i.first == "H")
				i.second->setText(std::to_string(huePicker->getHue()));
			else if(i.first == "S")
				i.second->setText(std::to_string(colorSVPicker->getSaturation()));
			else if (i.first == "V")
				i.second->setText(std::to_string(colorSVPicker->getValue()));
			else if (i.first == "R")
				i.second->setText(std::to_string(colorRGB.r));
			else if (i.first == "G")
				i.second->setText(std::to_string(colorRGB.g));
			else if (i.first == "B")
				i.second->setText(std::to_string(colorRGB.b));
		}
	}

	for (auto& i : textBoxes)
	{
		if (HandleEvents::instance.isTextEntered())
		{
			if (textBoxes["H"]->getState() == ACTIVE || textBoxes["S"]->getState() == ACTIVE || textBoxes["V"]->getState() == ACTIVE)
			{
				int h = 0, s = 0, v = 0;
				h = stringToInt(textBoxes["H"]->getText());
				s = stringToInt(textBoxes["S"]->getText());
				v = stringToInt(textBoxes["V"]->getText());
				if (h > 360)
					h = 360;
				if (s > 100)
					s = 100;
				if (v > 100)
					v = 100;
				huePicker->setPositionPointer(h);
				colorSVPicker->updateHueBox(huePicker->getHue());
				colorSVPicker->setPositionPicker(s, v);
				colorRGB = convertHSVToRGB(huePicker->getHue(), colorSVPicker->getSaturation(), colorSVPicker->getValue());
				textBoxes["R"]->setText(std::to_string(colorRGB.r));
				textBoxes["G"]->setText(std::to_string(colorRGB.g));
				textBoxes["B"]->setText(std::to_string(colorRGB.b));
				colorShow->setFillColor(colorRGB);
			}
			else if (textBoxes["R"]->getState() == ACTIVE || textBoxes["G"]->getState() == ACTIVE || textBoxes["B"]->getState() == ACTIVE)
			{
				int r = 0, g = 0, b = 0;
				r = stringToInt(textBoxes["R"]->getText());
				g = stringToInt(textBoxes["G"]->getText());
				b = stringToInt(textBoxes["B"]->getText());
				if (r > 255)
					r = 255;
				if (g > 255)
					g = 255;
				if (b > 255)
					b = 255;
				ColorHSV colorHSV = convertRGBToHSV(r, g, b);
				textBoxes["H"]->setText(std::to_string(colorHSV.getHue()));
				textBoxes["S"]->setText(std::to_string(colorHSV.getSaturation()));
				textBoxes["V"]->setText(std::to_string(colorHSV.getValue()));
				huePicker->setPositionPointer(stringToInt(textBoxes["H"]->getText()));
				colorSVPicker->updateHueBox(huePicker->getHue());
				colorSVPicker->setPositionPicker(stringToInt(textBoxes["S"]->getText()), stringToInt(textBoxes["V"]->getText()));
				colorRGB = sf::Color(r, g, b);
				colorShow->setFillColor(colorRGB);
			}
		}
	}
}

void App::update()
{
	updateEvents();
	updateMousePosition();
	updateTools();
}

void App::renderTools()
{
	window.draw(*colorShow);
	colorSVPicker->render(window);
	huePicker->render(window);
	for (auto& i : labels)
	{
		i.second->render(window);
	}
	for (auto& i : textBoxes)
	{
		i.second->render(window);
	}
}

void App::render()
{
	window.clear();
	renderTools();
	window.display();
}

void App::run()
{
	while (window.isOpen())
	{
		update();
		render();
	}
}