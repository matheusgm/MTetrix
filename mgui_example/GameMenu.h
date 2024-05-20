#ifndef GAMEMENU_H
#define GAMEMENU_H

#include "Button.h"

class GameMenu
{
private:
	sf::Font& font;
	sf::Text menuText;

	sf::RectangleShape background;
	sf::RectangleShape container;

	std::map<std::string, gui::Button*> buttons;

public:
	GameMenu(sf::RenderWindow& window, sf::Font& font, std::string title = "");
	virtual ~GameMenu();

	// Accessor
	std::map<std::string, gui::Button*>& getButtons();
	gui::Button* getButton(std::string key);
	void addButton(std::string key, std::string text);

	// Modifier
	void setPosition(const float x, const float y);

	// Functions
	void onResizeWindow(sf::RenderWindow& new_window);
	void updateEvents(sf::Event& sfEvent, const sf::Vector2f& mousePos);
	void update(const sf::Vector2f& mousePos);
	void render(sf::RenderTarget& target);
};

#endif

