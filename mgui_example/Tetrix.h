#ifndef TETRIX_H
#define TETRIX_H

#include "TetrixShape.h"

struct collide
{
	int left;
	int right;
	int bottom;
};

class Tetrix
{
private:
	sf::RectangleShape gridArea;
	int squareSize;
	int rows;
	int columns;

	sf::Clock clock;
	sf::Time elapsed_time;
	sf::Time delta_time;

	std::function<void()> onGameoverCallback;

	sf::Texture squaresTexture;
	TetrixShape* tShape;
	TetrixSquare*** squaresMatrix;

	int score;
	int linesCleared; // Level = 1 level a cada 10 lines cleared
	bool gameOver;
	sf::SoundBuffer gameSoundBuffer;
	sf::SoundBuffer gameOverSoundBuffer;
	sf::SoundBuffer lineClearedSoundBuffer;
	sf::SoundBuffer newShapeSoundBuffer;
	sf::SoundBuffer rotateShapeSoundBuffer;
	sf::SoundBuffer shapeMoveSoundBuffer;
	sf::SoundBuffer pauseGameSoundBuffer;

	sf::Sound gameSound;
	sf::Sound gameOverSound;
	sf::Sound rotateShapeSound;
	sf::Sound newShapeSound;
	sf::Sound lineClearedSound;
	sf::Sound shapeMoveSound;
	sf::Sound pauseGameSound;

	// Functions
	void initVariables();
	void initShape();
	void initSounds();
	void initSquareMatrix();
	bool checkOverlap();
	collide checkCollide();
	void shapeActionFinished();
	int calculateScore(int lines_cleared);

public:
	Tetrix(sf::Texture squaresTexture, int rows = 20, int columns = 10, int squareSize = 20);
	virtual ~Tetrix();

	void resetTimer();
	void restartTimer();

	int getLevel();
	int getScore();
	sf::Vector2f getPosition();
	void setSoundVolume(float value);

	// Movement Functions
	void moveShapeDown();
	void moveShapeLeft();
	void moveShapeRight();
	void rotateShape(const float angle);

	// Functions
	void onPause();
	void onResume();
	bool isLineFullComplete(int line);
	void onGameover(std::function<void()> callback);
	void eliminateCompletedLines(std::vector<int> linesCompleted);
	void updateMatrixAfterCompletedLines(std::vector<int> linesCompleted);
	void onResizeWindow(sf::RenderWindow& new_window);
	void update(const float& dt);
	void renderSquareMatrix(sf::RenderTarget& target);
	void render(sf::RenderTarget& target);

};

#endif

