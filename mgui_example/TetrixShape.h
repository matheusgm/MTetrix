#ifndef TETRIXSHAPE_H
#define TETRIXSHAPE_H

#include "TetrixSquare.h"

#define SHAPES_SIZE 7;
enum shapes { I = 0, J, L, O, S, T, Z };

class TetrixShape
{
private:
	std::vector<TetrixSquare*> squares;
	sf::Vector2f position;
	sf::Vector2f rotationPoint;
	int squareSize;
public:
	TetrixShape(float x, float y, int square_size,
		sf::Texture& texture, int start_frame_x, int start_frame_y, int width, int height,
		shapes shape
	);
	virtual ~TetrixShape();

	const sf::Vector2f getPosition();
	const sf::Vector2f getRotationPoint();
	const std::vector<TetrixSquare*> getSquares();

	void setPosition(sf::Vector2f position);

	// Function
	void move(const float x, const float y);
	void rotate(const float angle);
	void update(const float& dt);
	void render(sf::RenderTarget& target);
};
#endif

