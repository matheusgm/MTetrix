#include "stdafx.h"
#include "Gui.h"

gui::Button::Button(float x, float y, float width, float height,
	sf::Font* font, std::string text, unsigned character_size,
	sf::Color text_normal_color, sf::Color text_hover_color, sf::Color text_pressed_color,
	sf::Color normal_color, sf::Color hover_color, sf::Color pressed_color,
	sf::Color outline_normal_color, sf::Color outline_hover_color, sf::Color outline_pressed_color,
	short unsigned id)
{
	this->buttonState = NORMAL;
	this->id = id;
	this->onPressedCallback = [] {};
	this->buttonPressed = false;

	// Font
	this->font = font;

	// Shape
	this->shape.setFillColor(normalColor);
	this->shape.setOutlineThickness(1.f);
	this->shape.setOutlineColor(outline_normal_color);

	// Text
	this->text.setString(text);
	this->text.setFont(*this->font);
	this->text.setFillColor(text_normal_color);
	this->text.setCharacterSize(character_size);

	this->setSize(width, height);
	this->setPosition(x, y);

	
	// Colors State
	this->textNormalColor = text_normal_color;
	this->textHoverColor = text_hover_color;
	this->textPressedColor = text_pressed_color;
	this->textDisabledColor = sf::Color::Color(text_normal_color.r, text_normal_color.g, text_normal_color.b, 150);

	this->normalColor = normal_color;
	this->hoverColor = hover_color;
	this->pressedColor = pressed_color;
	this->disabledColor = sf::Color::Color(normal_color.r, normal_color.g, normal_color.b, 150);
	
	this->outlineNormalColor = outline_normal_color;
	this->outlineHoverColor = outline_hover_color;
	this->outlinePressedColor = outline_pressed_color;
	this->outlineDisabledColor = sf::Color::Color(outline_pressed_color.r, outline_pressed_color.g, outline_pressed_color.b, 150);

}

gui::Button::~Button()
{
}

// Acessors
const bool gui::Button::isPressed() const
{
	if (this->buttonState == PRESSED) {
		return true;
	}
	return false;
}

const std::string gui::Button::getText() const
{
	return this->text.getString();
}

const short unsigned& gui::Button::getId() const
{
	return this->id;
}

const sf::Vector2f& gui::Button::getPosition() const
{
	return this->shape.getPosition();
}

const sf::Vector2f& gui::Button::getSize() const
{
	return this->shape.getGlobalBounds().getSize();
}

const float gui::Button::getTop() const
{
	return this->shape.getPosition().y;
}

const float gui::Button::getBottom() const
{
	return this->shape.getPosition().y + this->shape.getSize().y;
}

const float gui::Button::getLeft() const
{
	return this->shape.getPosition().x;
}

const float gui::Button::getRight() const
{
	return this->shape.getPosition().x + this->shape.getSize().x;
}


void gui::Button::setPosition(const float x, const float y)
{
	this->shape.setPosition(sf::Vector2f(x, y));
	this->text.setPosition(
		this->shape.getPosition().x + (this->shape.getSize().x / 2.f) - (this->text.getGlobalBounds().width / 2.f),
		this->shape.getPosition().y + (this->shape.getSize().y / 2.f) - (this->text.getGlobalBounds().height / 2.f) - (10.f / 2.f)
	);
}

void gui::Button::setSize(const float width, const float height)
{
	this->shape.setSize(sf::Vector2f(width, height));
}

// Modifier
void gui::Button::setText(const std::string text)
{
	this->text.setString(text); 
}

void gui::Button::setId(const short unsigned id)
{
	this->id = id;
}

void gui::Button::setDisabled(const bool disable)
{
	if (disable)
		this->buttonState = DISABLED;
	else
		this->buttonState = NORMAL;
}

void gui::Button::onPressed(std::function<void()> callback)
{
	this->onPressedCallback = callback;
}

// Functions

void gui::Button::updateEvents(sf::Event& sfEvent, const sf::Vector2f& mousePos)
{
	// Disabled
	if (this->buttonState != DISABLED) {
		// Idle
		this->buttonState = NORMAL;
		// Hover
		if (this->shape.getGlobalBounds().contains(mousePos)) {
			this->buttonState = HOVER;
			// Pressed
			if (sfEvent.type == sf::Event::MouseButtonPressed)
			{
				if (sfEvent.mouseButton.button == sf::Mouse::Left)
				{
					this->buttonPressed = true;
				}
			}
			if(this->buttonPressed)
				this->buttonState = PRESSED;
		}
		if (this->buttonPressed)
		{
			if (sfEvent.type == sf::Event::MouseButtonReleased)
			{
				this->buttonPressed = false;
				if (this->shape.getGlobalBounds().contains(mousePos))
				{
					this->buttonState = HOVER;
					if (sfEvent.mouseButton.button == sf::Mouse::Left)
					{
						this->buttonState = NORMAL;
						this->onPressedCallback();
					}
				}
			}
		}
	}
}

void gui::Button::update(const sf::Vector2f& mousePos)
{
	// Update the booleans for hover and pressed

	switch (this->buttonState)
	{
	case NORMAL:
		this->shape.setFillColor(this->normalColor);
		this->text.setFillColor(this->textNormalColor);
		this->shape.setOutlineColor(this->outlineNormalColor);
		break;
	case HOVER:
		this->shape.setFillColor(this->hoverColor);
		this->text.setFillColor(this->textHoverColor);
		this->shape.setOutlineColor(this->outlineHoverColor);
		break;
	case PRESSED:
		this->shape.setFillColor(this->pressedColor);
		this->text.setFillColor(this->textPressedColor);
		this->shape.setOutlineColor(this->outlinePressedColor);
		break;
	case DISABLED:
		this->shape.setFillColor(this->disabledColor);
		this->text.setFillColor(this->textDisabledColor);
		this->shape.setOutlineColor(this->outlineDisabledColor);
		break;
	default:
		this->shape.setFillColor(sf::Color::Red);
		this->text.setFillColor(sf::Color::Blue);
		this->shape.setOutlineColor(sf::Color::Green);
		break;
	}

}

void gui::Button::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
	target.draw(this->text);
}

// Slider ===============================================

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
			float interval_size = (this->backgroundShape.getSize().x / (static_cast<float>(this->maxValue - this->minValue)/this->step));
			float local_mouse_x = mousePos.x - this->backgroundShape.getPosition().x + (interval_size/2.f);

			if (local_mouse_x <= 0.f)
				local_mouse_x = 0.f;
			else if (local_mouse_x >= this->backgroundShape.getSize().x)
				local_mouse_x = this->backgroundShape.getSize().x;

			int new_val = static_cast<int>(local_mouse_x / interval_size)*this->step + this->minValue;
			
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
