#include "stdafx.h"
#include "ListItem.h"

gui::ListItem::ListItem()
{
	// Background Shape
	this->shape.setFillColor(sf::Color::Red);
	this->shape.setOutlineThickness(1.f);
	this->shape.setOutlineColor(sf::Color::Black);

	// Text
	this->text.setString("Hello");
	//this->text.setFont(*this->font);
	this->text.setFillColor(sf::Color::White);
	this->text.setCharacterSize(24);

	this->setSize(100.f, 50.f);
	this->setPosition(0.f, 0.f);
}

gui::ListItem::~ListItem()
{
}

void gui::ListItem::setPosition(float x, float y)
{
	this->position = sf::Vector2f(x, y);
	this->shape.setPosition(this->position);
	this->text.setPosition(this->position);
}

void gui::ListItem::setSize(float x, float y)
{
	this->size = sf::Vector2f(x, y);
	this->shape.setSize(this->size);
}

const sf::Vector2f& gui::ListItem::getSize() const
{
	return this->size;
}

void gui::ListItem::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
	target.draw(this->text);
}
