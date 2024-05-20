#include "stdafx.h"
#include "Slider.h"

gui::Slider::Slider(float x, float y, float width, float height,
	int min_value, int max_value, int default_value, int step,
	sf::Color background_color, sf::Color foreground_color, sf::Color indicator_color
)
{
	this->minValue = min_value;
	this->maxValue = max_value;
	this->value = default_value;
	if (default_value == 0 || default_value < this->minValue) {
		this->value = this->minValue;
	}
	else if (default_value > this->maxValue)
	{
		this->value = this->maxValue;
	}

	this->step = step;
	this->indicatorPressed = false;
	this->onValueChangeCallback = [] {};

	// Background Shape

	this->backgroundShape.setSize(sf::Vector2f(width, height));
	this->backgroundShape.setFillColor(background_color);
	this->backgroundShape.setOutlineThickness(1.f);
	this->backgroundShape.setOutlineColor(sf::Color::Black);

	// Foreground Shape
	this->foregroundShape.setFillColor(foreground_color);

	// Indicator
	this->indicatorShape.setRadius(height * 0.7f);
	this->indicatorShape.setFillColor(indicator_color);
	this->indicatorShape.setOutlineThickness(1.f);
	this->indicatorShape.setOutlineColor(sf::Color::Black);

	this->setPosition(x, y);

}

gui::Slider::~Slider()
{
}

const int gui::Slider::getValue() const
{
	return this->value;
}

const sf::Vector2f& gui::Slider::getSize() const
{
	return this->backgroundShape.getGlobalBounds().getSize();
}

void gui::Slider::setPosition(const float x, const float y)
{
	this->backgroundShape.setPosition(sf::Vector2f(x, y));
	this->foregroundShape.setPosition(this->backgroundShape.getPosition());
	// Mudar ao deslocar o indicator
	this->updateIndicator();
}

void gui::Slider::setSize(const float width, const float height)
{
	this->backgroundShape.setSize(sf::Vector2f(width, height));
	// Mudar ao deslocar o indicator
	this->updateIndicator();
}

void gui::Slider::onValueChange(std::function<void()> callback)
{
	this->onValueChangeCallback = callback;
}

void gui::Slider::updateIndicator()
{
	float value_perc = static_cast<float>(this->value - this->minValue) / static_cast<float>(this->maxValue - this->minValue);

	this->foregroundShape.setSize(sf::Vector2f(this->backgroundShape.getSize().x * value_perc, this->backgroundShape.getSize().y));

	this->indicatorShape.setPosition(
		sf::Vector2f(
			this->backgroundShape.getPosition().x - (this->indicatorShape.getGlobalBounds().width / 2.f) + (this->backgroundShape.getSize().x * value_perc),
			this->backgroundShape.getPosition().y + (this->backgroundShape.getSize().y / 2.f) - (this->indicatorShape.getGlobalBounds().height / 2.f)
		)
	);
}

void gui::Slider::updateEvents(sf::Event& sfEvent, const sf::Vector2f& mousePos)
{
	if (this->indicatorShape.getGlobalBounds().contains(mousePos)) {
		if (sfEvent.type == sf::Event::MouseButtonPressed)
		{
			if (sfEvent.mouseButton.button == sf::Mouse::Left)
			{
				this->indicatorPressed = true;
			}
		}
	}

	if (this->indicatorPressed)
	{
		if (sfEvent.type == sf::Event::MouseButtonReleased)
		{
			if (sfEvent.mouseButton.button == sf::Mouse::Left)
			{
				this->indicatorPressed = false;
			}
		}
		else if (sfEvent.type == sf::Event::MouseMoved)
		{
			float interval_size = (this->backgroundShape.getSize().x / (static_cast<float>(this->maxValue - this->minValue) / this->step));
			float local_mouse_x = mousePos.x - this->backgroundShape.getPosition().x + (interval_size / 2.f);

			if (local_mouse_x <= 0.f)
				local_mouse_x = 0.f;
			else if (local_mouse_x >= this->backgroundShape.getSize().x)
				local_mouse_x = this->backgroundShape.getSize().x;

			int new_val = static_cast<int>(local_mouse_x / interval_size) * this->step + this->minValue;

			// Only update if the value changes
			if (new_val != this->value)
			{
				this->value = new_val;
				this->updateIndicator();
				this->onValueChangeCallback();
			}
		}
	}

}

void gui::Slider::update(const sf::Vector2f& mousePos)
{

}

void gui::Slider::render(sf::RenderTarget& target)
{
	target.draw(this->backgroundShape);
	target.draw(this->foregroundShape);

	target.draw(this->indicatorShape);
}
