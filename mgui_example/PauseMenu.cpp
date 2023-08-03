#include "stdafx.h"
#include "PauseMenu.h"

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

// Functions
const bool PauseMenu::isButtonPressed(const std::string key)
{
	return this->buttons[key]->isPressed();
}


void PauseMenu::addButton(const std::string key, float y, const std::string text)
{
	float gap = 50.f;
	float width = this->container.getSize().x - 2*gap;
	float height = 50.f;
	float x = this->container.getPosition().x + (this->container.getSize().x / 2.f) - (width / 2.f);
	this->buttons[key] = new gui::Button(
		x, y,
		width, height,
		&this->font, text, 32);
}

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
			static_cast<float>(new_window.getSize().x) / 4.f,
			static_cast<float>(new_window.getSize().y) - 60.f
		)
	);
	this->container.setPosition(
		(static_cast<float>(new_window.getSize().x) / 2.f) - (this->container.getSize().x / 2.f),
		30.f
	);

	// Text
	this->menuText.setPosition(
		this->container.getPosition().x + this->container.getSize().x / 2.f - this->menuText.getGlobalBounds().width / 2.f,
		this->container.getPosition().y + 20.f
	);

	// Buttons
	float gap = 50.f;
	for (auto& it : this->buttons) {
		it.second->setSize(this->container.getSize().x - (2 * gap), 50.f);
		it.second->setPosition(this->container.getPosition().x + (this->container.getSize().x / 2.f) - (it.second->getSize().x / 2.f), it.second->getPosition().y);
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

	for (auto& it : this->buttons) {
		it.second->render(target);
	}

	target.draw(this->menuText);
}


