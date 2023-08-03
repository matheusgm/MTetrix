#include "stdafx.h"
#include "PauseMenu.h"

void PauseMenu::initButtons()
{
	float gap = 50.f;
	float width = this->container.getSize().x - 2 * gap;
	float height = 50.f;
	this->buttons["QUIT"] = new gui::Button(
		100.f, 100.f,
		width, height,
		&this->font, "Quit", 32);
}

PauseMenu::PauseMenu(sf::RenderWindow& window, sf::Font& font)
	:font(font)
{	
	// Init Background
	this->background.setFillColor(sf::Color(20, 20, 20, 100));

	// Init Container
	this->container.setFillColor(sf::Color(20, 20, 20, 200));

	// Init text
	this->menuText.setFont(font);
	this->menuText.setFillColor(sf::Color(255, 255, 255, 200));
	this->menuText.setCharacterSize(30);
	this->menuText.setString("PAUSED");

	this->initButtons();
}

PauseMenu::~PauseMenu()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it) {
		delete it->second;
	}
}

std::map<std::string, gui::Button*>& PauseMenu::getButtons()
{
	return this->buttons;
}

gui::Button* PauseMenu::getButton(std::string key)
{
	return this->buttons[key];
}

void PauseMenu::setPosition(const float x, const float y)
{
	// Container
	this->container.setPosition(x, y);

	// Text
	this->menuText.setPosition(
		this->container.getPosition().x + this->container.getSize().x / 2.f - this->menuText.getGlobalBounds().width / 2.f,
		this->container.getPosition().y + 20.f
	);

	// Buttons
	this->buttons["QUIT"]->setPosition(this->container.getPosition().x + (this->container.getSize().x / 2.f) - (this->buttons["QUIT"]->getSize().x / 2.f), this->container.getSize().y - 50.f);
}

// Functions
void PauseMenu::onResizeWindow(sf::RenderWindow& new_window)
{
	// Background
	this->background.setSize(
		sf::Vector2f(
			static_cast<float>(new_window.getSize().x),
			static_cast<float>(new_window.getSize().y)
		)
	);

	// Container
	this->container.setSize(
		sf::Vector2f(
			static_cast<float>(new_window.getSize().x) / 3.f,
			static_cast<float>(new_window.getSize().y) - 60.f
		)
	);

	// Buttons
	float gap = 50.f;
	this->buttons["QUIT"]->setSize(this->container.getSize().x - (2 * gap), 50.f);

	this->setPosition((static_cast<float>(new_window.getSize().x) / 2.f) - (this->container.getSize().x / 2.f), 30.f);
}

void PauseMenu::updateEvents(sf::Event& sfEvent, const sf::Vector2f& mousePos)
{
	for (auto& it : this->buttons) {
		it.second->updateEvents(sfEvent, mousePos);
	}
}


void PauseMenu::update(const sf::Vector2f& mousePos)
{
	for (auto& it : this->buttons) {
		it.second->update(mousePos);
	}
}

void PauseMenu::render(sf::RenderTarget& target)
{
	target.draw(this->background);
	target.draw(this->container);
	target.draw(this->menuText);

	for (auto& it : this->buttons) {
		it.second->render(target);
	}
}


