#include "stdafx.h"
#include "Tetrix.h"


void Tetrix::initVariables()
{
	this->score = 0;
	this->linesCleared = 0;

	this->gridArea.setPosition(sf::Vector2f(100.f, 100.f));
	this->gridArea.setFillColor(sf::Color::Black);
	this->gridArea.setOutlineThickness(1.f);
	this->gridArea.setOutlineColor(sf::Color::Black);
	this->gridArea.setSize(sf::Vector2f(
		static_cast<float>(this->squareSize * this->columns),
		static_cast<float>(this->squareSize * this->rows)
	));
}

void Tetrix::initShape()
{
	int shape = rand() % SHAPES_SIZE;
	int color = rand() % 4;

	this->tShape = new TetrixShape(
		this->gridArea.getPosition().x + floor(this->columns / 2.f)*this->squareSize,
		this->gridArea.getPosition().y - (2 * this->squareSize),
		this->squareSize, this->squaresTexture, color / 2, color % 2, 128, 128, static_cast<shapes>(shape)
	);
}

void Tetrix::initSquareMatrix()
{
	this->squaresMatrix = new TetrixSquare * *[this->rows] {NULL};
	for (int i = 0; i < this->rows; i++)
	{
		this->squaresMatrix[i] = new TetrixSquare * [this->columns] {NULL};
	}

}

bool Tetrix::checkOverlap()
{
	sf::Vector2f gridStart = this->gridArea.getPosition();
	int i = 0;
	int j = 0;
	for (auto& ts : this->tShape->getSquares())
	{
		j = ts->getRelativeSquareTile(this->gridArea.getPosition()).x;
		i = ts->getRelativeSquareTile(this->gridArea.getPosition()).y;
		if (i >= 0 and i < this->rows and j >= 0 and j < this->columns)
			if (this->squaresMatrix[i][j] != NULL) return true;
	}
	return false;
}

collide Tetrix::checkCollide()
{
	int i = 0;
	int j = 0;
	int maxY = 0;
	int maxX = 0;
	collide detection;
	for (auto& s : this->tShape->getSquares())
	{
		i = s->getRelativeSquareTile(this->gridArea.getPosition()).y;
		j = s->getRelativeSquareTile(this->gridArea.getPosition()).x;
		if (j > this->columns - 1) // Algum quadrado ficou fora do lado direito
		{
			if ((j - (this->columns - 1)) > maxX) maxX = (j - (this->columns - 1));
		}
		else if (j < 0) // Algum quadrado ficou fora do lado esquerdo
		{
			if (j < maxX) maxX = j;
		}
		if (i > this->rows - 1) // Algum quadrado ficou fora em baixo
		{
			if ((i - (this->rows - 1)) > maxY) maxY = (i - (this->rows - 1));
		}
	}

	detection.bottom = maxY;
	detection.left = 0;
	detection.right = 0;
	if (maxX > 0) detection.right = maxX;
	else if (maxX < 0) detection.left = maxX;
	
	return detection;
}

void Tetrix::shapeActionFinished()
{
	// Put squares in Matrix
	std::set<int> linesToCheck = {};
	std::vector<int> linesCompleted = {};
	int i = 0;
	int j = 0;

	// Put the Squares of the Shape in the correct position of the Matrix
	for (auto* ts : this->tShape->getSquares())
	{
		j = ts->getRelativeSquareTile(this->gridArea.getPosition()).x;
		i = ts->getRelativeSquareTile(this->gridArea.getPosition()).y;
		linesToCheck.insert(i);
		if (ts)
		{
			this->squaresMatrix[i][j] = new TetrixSquare(*ts);
		}
	}

	// Analyse only the lines of the new Squares in the Matrix
	for (auto& l : linesToCheck)
	{
		if (this->isLineFullComplete(l)) linesCompleted.push_back(l);
	}

	// Eliminate the completed lines and increment the pontuation
	this->eliminateCompletedLines(linesCompleted);

	// Update position of line above the completed lines
	this->updateMatrixAfterCompletedLines(linesCompleted);

	// Increment Points
	this->linesCleared += linesCompleted.size();
	this->score += this->calculateScore(linesCompleted.size());

	// TODO - Verify if is not game over

	// Generate a new shape
	delete this->tShape;

	this->initShape();

}

Tetrix::Tetrix(sf::Texture squaresTexture, int rows, int columns, int squareSize)
	: squaresTexture(squaresTexture), rows(rows), columns(columns), squareSize(squareSize)
{
	this->initSquareMatrix();
	this->initVariables();
	this->initShape();

	this->elapsed_time = sf::seconds(0.f);
	this->delta_time = sf::seconds(0.5f);
}

Tetrix::~Tetrix()
{
	delete this->tShape;

	if (this->squaresMatrix)
	{
		for (int i = 0; i < this->rows; i++)
		{
			for (int j = 0; j < this->columns; j++)
			{
				delete this->squaresMatrix[i][j];
			}
			delete[] this->squaresMatrix[i];
		}
	}
	delete[] this->squaresMatrix;
}

int Tetrix::calculateScore(int lines_cleared)
{
	int level = this->getLevel();
	switch (lines_cleared)
	{
	case 1:
		return 40 * level;
	case 2 :
		return 100 * level;
	case 3:
		return 300 * level;
	case 4:
		return 1200 * level;
	default:
		return 0;
	}
}

void Tetrix::resetTimer()
{
	this->elapsed_time = sf::seconds(0.f);
}

void Tetrix::restartTimer()
{
	this->clock.restart();
}

int Tetrix::getLevel()
{
	return  static_cast<int>(floor(this->linesCleared / 10)) + 1;
}

int Tetrix::getScore()
{
	return this->score;
}

void Tetrix::moveShapeDown()
{
	this->tShape->move(0.f, 1.f);

	int bottom = this->checkCollide().bottom;
	bool overlap = false;
	if (bottom == 0)  overlap = this->checkOverlap();
	if (overlap || bottom != 0)
	{
		this->tShape->move(0.f, -1.f);
		this->shapeActionFinished();
	}
}

void Tetrix::moveShapeLeft()
{
	this->tShape->move(-1.f, 0.f);
	int left = this->checkCollide().left;
	bool overlap = false;
	if (left == 0) overlap = this->checkOverlap();
	if (overlap || left != 0) this->tShape->move(1.f, 0.f);
}

void Tetrix::moveShapeRight()
{
	this->tShape->move(1.f, 0.f);
	int right = this->checkCollide().right;
	bool overlap = false;
	if (right == 0) overlap = this->checkOverlap();
	if (overlap || right != 0) this->tShape->move(-1.f, 0.f);
}

void Tetrix::rotateShape(const float angle)
{
	this->tShape->rotate(angle);
	collide detect = this->checkCollide();
	int right = detect.right;
	int left = detect.left;
	int bottom = detect.bottom;
	bool overlap = false;
	if (left != 0)
	{
		this->tShape->move(static_cast<float>(-left), 0.f);
		overlap = this->checkOverlap();
		if (overlap)
		{
			this->tShape->move(static_cast<float>(left), 0.f);
			this->tShape->rotate(-angle);
		}
	}
	else if (right != 0)
	{
		this->tShape->move(static_cast<float>(-right), 0.f);
		overlap = this->checkOverlap();
		if (overlap)
		{
			this->tShape->move(static_cast<float>(right), 0.f);
			this->tShape->rotate(-angle);
		}
	}
	else if (bottom)
	{
		this->tShape->move(0.f, static_cast<float>(-bottom));
		overlap = this->checkOverlap();
		if (overlap)
		{
			this->tShape->move(0.f, static_cast<float>(bottom));
			this->tShape->rotate(-angle);
		}
	}
	else
	{
		overlap = this->checkOverlap();
		if (overlap)
		{
			this->tShape->rotate(-angle);
		}
	}
}

bool Tetrix::isLineFullComplete(int line)
{
	bool line_completed = true;
	for (int j = 0; j < this->columns; j++)
	{
		if (this->squaresMatrix[line][j] == NULL) line_completed = false;
	}
	return line_completed;
}

void Tetrix::eliminateCompletedLines(std::vector<int> linesCompleted)
{
	for (auto& line : linesCompleted)
	{
		for (int j = 0; j < this->columns; j++)
		{
			delete this->squaresMatrix[line][j];
			this->squaresMatrix[line][j] = NULL;
		}
	}
	
}

void Tetrix::updateMatrixAfterCompletedLines(std::vector<int> linesCompleted)
{
	TetrixSquare** aux;
	// Para cada linha completa e eliminada, deslocar em uma unidade as linhas de cima.
	std::sort(linesCompleted.begin(), linesCompleted.end());
	for (auto& line : linesCompleted)
	{
		if (line > 0)
		{
			for (int i = line - 1; i >= 0; i--)
			{
				aux = this->squaresMatrix[i + 1];
				this->squaresMatrix[i + 1] = this->squaresMatrix[i];
				this->squaresMatrix[i] = aux;
				for (int j = 0; j < this->columns; j++)
				{
					if(this->squaresMatrix[i + 1][j] != NULL)
						this->squaresMatrix[i + 1][j]->move(0.f, static_cast<float>(this->squareSize));
				}
			}
		}
		
	}
}

void Tetrix::onResizeWindow(sf::RenderWindow& new_window)
{
	sf::Vector2f diffShapeGridArea = this->tShape->getPosition() - this->gridArea.getPosition();

	this->gridArea.setPosition(sf::Vector2f(
		new_window.getSize().x / 2.f - this->gridArea.getSize().x / 2.f,
		new_window.getSize().y / 2.f - this->gridArea.getSize().y / 2.f
	));

	this->tShape->setPosition(this->gridArea.getPosition() + diffShapeGridArea);

	for (int i = 0; i < this->rows; i++)
	{
		for (int j = 0; j < this->columns; j++)
		{
			if (this->squaresMatrix[i][j] != NULL)
				this->squaresMatrix[i][j]->setPosition(
					this->gridArea.getPosition().x + j * this->squareSize,
					this->gridArea.getPosition().y + i * this->squareSize
				);
		}
	}
}

void Tetrix::update(const float& dt)
{
	this->elapsed_time += this->clock.restart();
	if (this->elapsed_time >= this->delta_time) // Tempo atingiu 1 segundo (delta time)
	{
		this->moveShapeDown();
		this->elapsed_time -= this->delta_time;
	}

	this->tShape->update(dt);
}

void Tetrix::renderSquareMatrix(sf::RenderTarget& target)
{
	if (!this->squaresMatrix) return;

	for (int i = 0; i < this->rows; i++)
	{
		for (int j = 0; j < this->columns; j++)
		{
			if (!this->squaresMatrix[i][j]) continue;
			this->squaresMatrix[i][j]->render(target);
		}
	}
}

void Tetrix::render(sf::RenderTarget& target)
{
	target.draw(this->gridArea);
	this->tShape->render(target);

	this->renderSquareMatrix(target);
}
