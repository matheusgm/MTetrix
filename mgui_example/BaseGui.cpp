#include "stdafx.h"
#include "BaseGui.h"

const sf::Vector2f& gui::BaseGui::getPosition() const
{
	return this->position;
}

const sf::Vector2f& gui::BaseGui::getSize() const
{
	return this->size;
}

const float gui::BaseGui::getTop() const
{
	return this->position.y;
}

const float gui::BaseGui::getBottom() const
{
	return this->position.y + this->size.y;
}

const float gui::BaseGui::getLeft() const
{
	return this->position.x;
}

const float gui::BaseGui::getRight() const
{
	return this->position.x + this->size.x;
}

void gui::BaseGui::setPosition(sf::Vector2f position)
{
	this->position = position;
}

void gui::BaseGui::setSize(sf::Vector2f size)
{
	this->size = size;
}
