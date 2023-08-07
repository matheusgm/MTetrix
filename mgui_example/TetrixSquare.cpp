#include "stdafx.h"
#include "TetrixSquare.h"

TetrixSquare::TetrixSquare(float x, float y, int size, sf::Texture& texture, int start_frame_x, int start_frame_y, int width, int height)
{
	this->sprite.setScale(sf::Vector2f(
		static_cast<float>(size) / static_cast<float>(width),
		static_cast<float>(size) / static_cast<float>(height)
	));
	this->sprite.setTexture(texture, true);
	this->sprite.setTextureRect(sf::IntRect(start_frame_x * width, start_frame_y * height, width, height));

	this->setPosition(x, y);
}

TetrixSquare::~TetrixSquare()
{
}

const sf::FloatRect TetrixSquare::getGlobalBounds()
{
	return this->sprite.getGlobalBounds();
}

const sf::Vector2f TetrixSquare::getPosition()
{
	return this->sprite.getPosition();
}

const sf::Vector2f TetrixSquare::getRelativePosition(const sf::Vector2f position)
{
	return this->getPosition() - position;
}

const sf::Vector2i TetrixSquare::getRelativeSquareTile(const sf::Vector2f position)
{
	return sf::Vector2i(
		static_cast<int>(this->getRelativePosition(position).x/this->getGlobalBounds().getSize().x),
		static_cast<int>(this->getRelativePosition(position).y/this->getGlobalBounds().getSize().y)
		);
}

void TetrixSquare::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

void TetrixSquare::move(const float x, const float y)
{
	this->sprite.move(x, y);
}

void TetrixSquare::update(const float& dt)
{
}

void TetrixSquare::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}
