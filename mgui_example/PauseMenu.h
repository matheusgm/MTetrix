#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include "GameMenu.h"

class PauseMenu :
	public GameMenu
{
private:
	// Functions

public:
	PauseMenu(sf::RenderWindow& window, sf::Font& font);
	virtual ~PauseMenu();

};

#endif

