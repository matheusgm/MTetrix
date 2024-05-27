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
		squares_position = { 3, 5, 7, 6 };
		break;
	case L:
		squares_position = { 2, 3, 5, 7 };
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

	float upperRow = 4;

	for (auto& i : squares_position)
	{
		int column = i % 2;
		int row = i / 2;
		this->squares.push_back(
			new TetrixSquare(x + column * square_size, y + row * square_size, square_size, texture, start_frame_x, start_frame_y, width, height)
		);
		if (row < upperRow) upperRow = (float)row;
	}

	// Top Left of 5
	this->rotationPoint = sf::Vector2f(x + square_size, y + (2 * square_size));
	this->position = sf::Vector2f(x, y);
	if (upperRow * square_size > 0) this->move(0, -upperRow);
}

TetrixShape::~TetrixShape()
{
	for (auto& s : this->squares)
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
	sf::Vector2f diff = position - this->getPosition();
	for (auto& s : this->squares)
	{
		s->setPosition(s->getPosition().x + diff.x, s->getPosition().y + diff.y);
	}
	this->position = position;
	this->rotationPoint = sf::Vector2f(this->position.x + this->squareSize, this->position.y + (2 * this->squareSize));
}

void TetrixShape::move(const float x, const float y)
{
	this->position = sf::Vector2f(
		this->getPosition().x + x * this->squareSize,
		this->getPosition().y + y * this->squareSize
	);
	this->rotationPoint += sf::Vector2f(x * this->squareSize, y * this->squareSize);
	for (auto& s : this->squares)
	{
		s->move(x * this->squareSize, y * this->squareSize);
	}
}

void TetrixShape::rotate(const float angle)
{
	float old_center_x, old_center_y;
	float new_rect_center_x, new_rect_center_y;
	int diff_x, diff_y;

	sf::Transform t;
	t.rotate(angle, this->getRotationPoint().x, this->getRotationPoint().y);

	for (auto& s : this->squares)
	{
		sf::FloatRect new_rect = t.transformRect(s->getGlobalBounds());

		old_center_x = s->getPosition().x + s->getGlobalBounds().getSize().x / 2.f;
		old_center_y = s->getPosition().y + s->getGlobalBounds().getSize().y / 2.f;

		new_rect_center_x = new_rect.left + new_rect.width / 2.f;
		new_rect_center_y = new_rect.top + new_rect.height / 2.f;

		diff_x = static_cast<int>(round(new_rect_center_x - old_center_x));
		diff_y = static_cast<int>(round(new_rect_center_y - old_center_y));

		s->move((float)diff_x, (float)diff_y);
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
