#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include "Gui.h"

class PauseMenu
{
private:
	sf::Font& font;
	sf::Text menuText;

	sf::RectangleShape background;
	sf::RectangleShape container;

	std::map<std::string, gui::Button*> buttons;

	// Functions
	void initButtons();

public:
	PauseMenu(sf::RenderWindow& window, sf::Font& font);
	virtual ~PauseMenu();

	// Accessor
	std::map<std::string, gui::Button*>& getButtons();
	gui::Button* getButton(std::string key);

	// Modifier
	void setPosition(const float x, const float y);

	// Functions
	void onResizeWindow(sf::RenderWindow& new_window);
	void updateEvents(sf::Event& sfEvent, const sf::Vector2f& mousePos);
	void update(const sf::Vector2f& mousePos);
	void render(sf::RenderTarget& target);

};

#endif

