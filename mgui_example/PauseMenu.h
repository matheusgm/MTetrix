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

public:
	PauseMenu(sf::RenderWindow& window, sf::Font& font);
	virtual ~PauseMenu();

	// Accessor
	std::map<std::string, gui::Button*>& getButtons();

	// Functions
	const bool isButtonPressed(const std::string key);
	void addButton(const std::string key, float y, const std::string text);
	void onResizeWindow(sf::RenderWindow& new_window);
	void update(const sf::Vector2f& mousePos);
	void render(sf::RenderTarget& target);

};

#endif

