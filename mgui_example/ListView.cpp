#include "stdafx.h"
#include "ListView.h"

gui::ListView::ListView(float x, float y, float width, float height, sf::Font* font)
	: BaseGui(sf::Vector2f(x, y), sf::Vector2f(width, height))
{
	// Background Shape
	this->backgroundShape.setFillColor(sf::Color::Yellow);
	this->backgroundShape.setOutlineThickness(1.f);
	this->backgroundShape.setOutlineColor(sf::Color::Black);

	// Scroll
	this->scroll = new Scroll(x + width - 10.f, y, 10.f, height, font);
	this->scroll->onValueChange(
		[this] { this->setListItemPosition(this->scroll->getValue()); }
	);

	this->elements.push_back(new ListItem());
	this->elements.push_back(new ListItem());
	this->elements.push_back(new ListItem());
	
	this->setSize(width, height);
	this->setPosition(x, y);
}

gui::ListView::~ListView()
{
	delete this->scroll;
}

void gui::ListView::addListItem(ListItem* item)
{
}

void gui::ListView::removeListItem(int pos)
{
}

void gui::ListView::setListItemPosition(int value)
{
	if (this->elements.size() == 0)
		return;

	float heightElements = this->elements.size() * this->elements.at(0)->getSize().y;
	float heightView = this->getSize().y;

	int i = 0;
	for (auto& it : this->elements) {
		it->setPosition(this->getPosition().x, this->getPosition().y + i * it->getSize().y + (value/100.f)*(heightElements-heightView));
		i++;
	}
}

void gui::ListView::setPosition(const float x, const float y)
{
	BaseGui::setPosition(sf::Vector2f(x, y));

	this->backgroundShape.setPosition(this->getPosition());
	this->scroll->setPosition(x + this->getSize().x - this->scroll->getSize().x, this->getPosition().y);

	this->setListItemPosition(this->scroll->getValue());
}

void gui::ListView::setSize(const float width, const float height)
{
	BaseGui::setSize(sf::Vector2f(width, height));

	this->backgroundShape.setSize(sf::Vector2f(this->getSize().x - this->scroll->getSize().x, this->getSize().y));
	this->scroll->setSize(this->scroll->getSize().x, height);

	for (auto& it : this->elements) {
		it->setSize(this->backgroundShape.getSize().x, it->getSize().y);
	}
}

bool gui::ListView::globalBoundsContains(const sf::Vector2f& points)
{
	return this->backgroundShape.getGlobalBounds().contains(points);
}

void gui::ListView::updateEvents(sf::Event& sfEvent, const sf::Vector2f& mousePos)
{
	this->scroll->updateEvents(sfEvent, mousePos);
	if (sfEvent.type == sf::Event::MouseWheelScrolled)
	{
		if (this->globalBoundsContains(mousePos))
		{
			this->scroll->scrollWheel(static_cast<int>(sfEvent.mouseWheelScroll.delta));
			this->setListItemPosition(this->scroll->getValue());
		}
	}
}

void gui::ListView::update(const sf::Vector2f& mousePos)
{
	this->scroll->update(mousePos);
}

void gui::ListView::render(sf::RenderTarget& target)
{
	target.draw(this->backgroundShape);
	this->scroll->render(target);

	for (auto& it : this->elements) {
		it->render(target);
	}
}
