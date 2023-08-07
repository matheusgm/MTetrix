#include "stdafx.h"
#include "TetrixShape.h"

TetrixShape::TetrixShape(float x, float y, int square_size,
	sf::Texture& texture, int start_frame_x, int start_frame_y, int width, int height,
	shapes shape 
) : squareSize(square_size)
{
	// [0, 1]
	// [2, 3]
	// [4, 5]
	// [6, 7]
	std::vector<int> squares_position = {};
	switch (shape)
	{
	case I:
		squares_position = { 1, 3, 5, 7 };
		break;
	case J:
		squares_position = {3, 5, 7, 6};
		break;
	case L:
		squares_position = { 2, 3, 5, 7};
		break;
	case O:
		squares_position = { 2, 3, 4, 5 };
		break;
	case S:
		squares_position = { 2, 4, 5, 7 };
		break;
	case T:
		squares_position = { 3, 5, 7, 4 };
		break;
	case Z:
		squares_position = { 3, 5, 4, 6 };
		break;
	default:
		break;
	}

	for (auto& i : squares_position)
	{
		int column = i % 2;
		int row = i / 2;
		this->squares.push_back(
			new TetrixSquare(x + column * square_size, y + row * square_size, square_size, texture, start_frame_x, start_frame_y, width, height)
		);
	}

	// Top Left of 5
	this->rotationPoint = sf::Vector2f(x + square_size, y + (2 * square_size));
	this->setPosition(sf::Vector2f(x, y));
}

TetrixShape::~TetrixShape()
{
	for (auto &s : this->squares)
	{
		delete s;
	}
}

const sf::Vector2f TetrixShape::getPosition()
{
	return this->position;
}

const sf::Vector2f TetrixShape::getRotationPoint()
{
	return this->rotationPoint;
}

const std::vector<TetrixSquare*> TetrixShape::getSquares()
{
	return this->squares;
}

void TetrixShape::setPosition(sf::Vector2f position)
{
	this->position = position;
}

void TetrixShape::move(const float x, const float y)
{
	this->setPosition(sf::Vector2f(
		this->getPosition().x + x * this->squareSize,
		this->getPosition().y + y * this->squareSize
	));
	this->rotationPoint += sf::Vector2f(x * this->squareSize, y * this->squareSize);
	for (auto& s : this->squares)
	{
		s->move(x * this->squareSize, y * this->squareSize);
	}
}

void TetrixShape::rotate(const float angle)
{
	sf::Transform t;
	t.rotate(angle, this->getRotationPoint().x, this->getRotationPoint().y);

	for (auto& s : this->squares)
	{
		sf::FloatRect new_rect = t.transformRect(s->getGlobalBounds());
		s->setPosition(round(new_rect.left), round(new_rect.top));
	}
}

void TetrixShape::update(const float& dt)
{
	for (auto& s : this->squares)
	{
		s->update(dt);
	}
}

void TetrixShape::render(sf::RenderTarget& target)
{
	for (auto& s : this->squares)
	{
		s->render(target);
	}
}
