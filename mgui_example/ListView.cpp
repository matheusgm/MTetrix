#include "stdafx.h"
#include "ListView.h"

gui::ListView::ListView(float x, float y, float width, float height, sf::Font* font)
{
	// Shape
	this->shape.setFillColor(sf::Color::Yellow);
	this->shape.setOutlineThickness(1.f);
	this->shape.setOutlineColor(sf::Color::Black);

	this->setSize(width, height);
	this->setPosition(x, y);

	// Scroll
	this->scroll = new Scroll(x + width, y, 10.f, height, font);
}

gui::ListView::~ListView()
{
	delete this->scroll;
}

void gui::ListView::setPosition(const float x, const float y)
{
	this->shape.setPosition(sf::Vector2f(x, y));
}

void gui::ListView::setSize(const float width, const float height)
{
	this->shape.setSize(sf::Vector2f(width, height));
}

void gui::ListView::updateEvents(sf::Event& sfEvent, const sf::Vector2f& mousePos)
{
	this->scroll->updateEvents(sfEvent, mousePos);
}

void gui::ListView::update(const sf::Vector2f& mousePos)
{
	this->scroll->update(mousePos);
}

void gui::ListView::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
	this->scroll->render(target);
}
