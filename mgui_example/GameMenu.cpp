#include "stdafx.h"
#include "GameMenu.h"

GameMenu::GameMenu(sf::RenderWindow& window, sf::Font& font, std::string title) :font(font)
{
	// Init Background
	this->background.setFillColor(sf::Color(20, 20, 20, 100));

	// Init Container
	this->container.setFillColor(sf::Color(20, 20, 20, 200));

	// Init text
	this->menuText.setFont(font);
	this->menuText.setFillColor(sf::Color(255, 255, 255, 200));
	this->menuText.setCharacterSize(30);
	this->menuText.setString(title);
}

GameMenu::~GameMenu()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it) {
		delete it->second;
	}
}

std::map<std::string, gui::Button*>& GameMenu::getButtons()
{
	return this->buttons;
}

gui::Button* GameMenu::getButton(std::string key)
{
	return this->buttons[key];
}

void GameMenu::addButton(std::string key, std::string text)
{
	float gap = 50.f;
	float width = this->container.getSize().x - 2 * gap;
	float height = 50.f;
	this->buttons[key] = new gui::Button(
		100.f, 100.f,
		width, height,
		&this->font, text, 32);
}

void GameMenu::setPosition(const float x, const float y)
{
	// Container
	this->container.setPosition(x, y);

	// Text
	this->menuText.setPosition(
		this->container.getPosition().x + this->container.getSize().x / 2.f - this->menuText.getGlobalBounds().width / 2.f,
		this->container.getPosition().y + 20.f
	);

	// Buttons
	int i = 0;
	for (auto& it : this->buttons) {
		it.second->setPosition(
			this->container.getPosition().x + (this->container.getSize().x / 2.f) - (it.second->getSize().x / 2.f),
			this->container.getPosition().y + this->container.getSize().y - (it.second->getSize().y * (i+1)) - (20.f * i) - 30.f);
		i++;
	}
}

void GameMenu::onResizeWindow(sf::RenderWindow& new_window)
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
	for (auto& it : this->buttons) {
		it.second->setSize(this->container.getSize().x - (2 * gap), 50.f);
	}

	this->setPosition((static_cast<float>(new_window.getSize().x) / 2.f) - (this->container.getSize().x / 2.f), 30.f);
}

void GameMenu::updateEvents(sf::Event& sfEvent, const sf::Vector2f& mousePos)
{
	for (auto& it : this->buttons) {
		it.second->updateEvents(sfEvent, mousePos);
	}
}

void GameMenu::update(const sf::Vector2f& mousePos)
{
	for (auto& it : this->buttons) {
		it.second->update(mousePos);
	}
}

void GameMenu::render(sf::RenderTarget& target)
{
	target.draw(this->background);
	target.draw(this->container);
	target.draw(this->menuText);

	for (auto& it : this->buttons) {
		it.second->render(target);
	}
}
