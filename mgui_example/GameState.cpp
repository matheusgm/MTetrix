#include "stdafx.h"
#include "GameState.h"

void GameState::initDeferredRender()
{
	this->renderTexture.create(
		this->stateData->gfxSettings->resolution.width,
		this->stateData->gfxSettings->resolution.height
	);

	this->renderSprite.setTexture(this->renderTexture.getTexture());
}

// Initializer Functions
void GameState::initKeybinds()
{

	std::ifstream ifs("Config/gamestate_keybinds.ini");

	if (ifs.is_open()) {
		std::string key = "";
		std::string key2 = "";

		while (ifs >> key >> key2) {
			this->keybinds[key] = this->supportedKeys->at(key2);
		}
	}

	ifs.close();
}

void GameState::initTexture()
{
	if (!this->textures["PLAYER_SHEET"].loadFromFile("Resources/Images/Sprites/Player/sheet.png")) {
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_PLAYER_TEXTURE";
	}
	if (!this->textures["TETRIX_SQUARES_SHEET"].loadFromFile("Resources/Images/Sprites/TetrixElements.png")) {
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_TETRIX_SQUARES_TEXTURE";
	}
}

void GameState::initPauseMenu()
{
	this->pmenu = new PauseMenu(*this->window, this->font);
	this->pmenu->getButton("QUIT")->onPressed([this]{this->endState(); });

}

void GameState::initVariables()
{
	this->squareSize = 20;
	this->rows = 20;
	this->columns = 10;
	this->squaresTexture = this->textures["TETRIX_SQUARES_SHEET"];
	this->gridArea.setFillColor(sf::Color::Color(200, 0, 200, 255));
	this->gridArea.setOutlineThickness(1.f);
	this->gridArea.setOutlineColor(sf::Color::Black);
	this->gridArea.setSize(sf::Vector2f(
		static_cast<float>(this->squareSize * this->columns),
		static_cast<float>(this->squareSize * this->rows)
	));
}

void GameState::initPlayers()
{
	this->player = new Player(0,0, this->textures["PLAYER_SHEET"]);
	this->tShape = new TetrixShape(
		this->gridArea.getPosition().x, this->gridArea.getPosition().y,
		this->squareSize, this->squaresTexture, 0, 0, 128, 128, shapes::L
	);
}

void GameState::initSquareMatrix()
{
	this->squaresMatrix = new TetrixSquare * *[this->rows] {NULL};
	for (int i = 0; i < this->rows; i++)
	{
		this->squaresMatrix[i] = new TetrixSquare * [this->columns] {NULL};
	}

}

bool GameState::checkBottom()
{
	std::vector<TetrixSquare*> squares = this->tShape->getSquares();
	sf::Vector2f gridStart = this->gridArea.getPosition();
	int i = 0;
	for (auto& ts : squares)
	{
		i = ts->getRelativeSquareTile(this->gridArea.getPosition()).y;
		if (i == this->rows) return true;
	}
	return false;
}

bool GameState::checkOverlap()
{
	std::vector<TetrixSquare*> squares = this->tShape->getSquares();
	sf::Vector2f gridStart = this->gridArea.getPosition();
	int i = 0;
	int j = 0;
	for (auto& ts : squares)
	{
		j = ts->getRelativeSquareTile(this->gridArea.getPosition()).x;
		i = ts->getRelativeSquareTile(this->gridArea.getPosition()).y;
		if (this->squaresMatrix[i][j] != NULL) return true;
	}
	return false;
}

int GameState::checkLeftSide()
{
	int j = 0;
	int maxX = 0;
	for (auto& s : this->tShape->getSquares())
	{
		j = s->getRelativeSquareTile(this->gridArea.getPosition()).x;
		if (j < 0) // Algum quadrado ficou fora
		{
			if (j < maxX) maxX = j;
		}
	}
	return maxX;
}

int GameState::checkRightSide()
{
	int j = 0;
	int maxX = 0;
	for (auto& s : this->tShape->getSquares())
	{
		j = s->getRelativeSquareTile(this->gridArea.getPosition()).x;
		if (j > this->columns - 1) // Algum quadrado ficou fora
		{
			if ((j - (this->columns - 1)) > maxX) maxX = (j - (this->columns - 1));
		}
	}
	return maxX;
}

void GameState::shapeActionFinished()
{
	// Put squares in Matrix
	std::vector<TetrixSquare*> squares = this->tShape->getSquares();
	int i = 0;
	int j = 0;
	for (auto* ts : squares)
	{
		j = ts->getRelativeSquareTile(this->gridArea.getPosition()).x;
		i = ts->getRelativeSquareTile(this->gridArea.getPosition()).y;
		if (ts)
		{
			this->squaresMatrix[i][j] = new TetrixSquare(*ts);
		}
	}

	// TODO - Verify if is not game over

	// Generate a new shape
	delete this->tShape;

	int shape = rand() % SHAPES_SIZE;
	int color = rand() % 4;

	this->tShape = new TetrixShape(
		this->gridArea.getPosition().x, this->gridArea.getPosition().y,
		this->squareSize, this->squaresTexture, color/2, color%2, 128, 128, static_cast<shapes>(shape)
	);

}

GameState::GameState(StateData* state_data) : State(state_data)
{
	srand(time(0));
	this->initKeybinds();
	this->initFonts();
	this->initTexture();
	this->initPauseMenu();
	this->initVariables();

	this->onResizeWindow();

	this->initSquareMatrix();
	this->initPlayers();

	this->background.setFillColor(sf::Color::Yellow);
}

GameState::~GameState()
{
	delete this->pmenu;
	delete this->player;
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

void GameState::updateView(const float& dt)
{
	//this->view.setCenter(this->player->getPosition());s
}

void GameState::updateKeyboardInput(sf::Event& sfEvent)
{
	if (sfEvent.type == sf::Event::KeyPressed)
	{
		if (sfEvent.key.code == sf::Keyboard::Key(this->keybinds.at("CLOSE")))
		{
			if (!this->paused) {
				this->pauseState();
			}
			else {
				this->unpauseState();
			}
		}

		// Update player input
		if (sfEvent.key.code ==  sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT"))) {
			this->tShape->move(-1.f, 0.f);
			int left = this->checkLeftSide();
			bool overlap = false;
			if (left == 0) overlap = this->checkOverlap();
			if (overlap || left != 0) this->tShape->move(1.f, 0.f);
		}
		if (sfEvent.key.code == sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))) {
			this->tShape->move(1.f, 0.f);
			int right = this->checkRightSide();
			bool overlap = false;
			if (right == 0) overlap = this->checkOverlap();
			if (overlap || right != 0) this->tShape->move(-1.f, 0.f);
		}
		if (sfEvent.key.code == sf::Keyboard::Key(this->keybinds.at("MOVE_UP"))) {
			// Rotate Left
			this->tShape->rotate(90.f);
			int right = this->checkRightSide();
			int left = this->checkLeftSide();
			bool overlap = false;
			if (left != 0)
			{
				this->tShape->move(static_cast<float>(-left), 0.f);
				overlap = this->checkOverlap();
				if (overlap)
				{
					this->tShape->move(static_cast<float>(left), 0.f);
					this->tShape->rotate(-90.f);
				}
			}
			else if (right != 0)
			{
				this->tShape->move(static_cast<float>(-right), 0.f);
				overlap = this->checkOverlap();
				if (overlap)
				{
					this->tShape->move(static_cast<float>(right), 0.f);
					this->tShape->rotate(-90.f);
				}
			}
			else
			{
				overlap = this->checkOverlap();
				if (overlap)
				{
					this->tShape->rotate(-90.f);
				}
			}
				

		}
		if (sfEvent.key.code == sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN"))) {
			this->tShape->move(0.f, 1.f);
			
			bool bottom = this->checkBottom();
			bool overlap = false;
			if (!bottom) {
				overlap = this->checkOverlap();
			}
			if (overlap || bottom)
			{
				this->tShape->move(0.f, -1.f);
				this->shapeActionFinished();
			}
		}
	}
}

void GameState::onResizeWindow()
{
	this->initDeferredRender();

	this->renderSprite.setTextureRect(
		sf::IntRect(
			0,
			0,
			this->stateData->gfxSettings->resolution.width,
			this->stateData->gfxSettings->resolution.height
		)
	);

	this->background.setSize(
		sf::Vector2f(
			static_cast<float>(this->window->getSize().x),
			static_cast<float>(this->window->getSize().y)
		)
	);

	this->gridArea.setPosition(sf::Vector2f(
		this->window->getSize().x/2.f - this->gridArea.getSize().x/2.f,
		this->window->getSize().y/2.f - this->gridArea.getSize().y/2.f
	));

	this->pmenu->onResizeWindow(*this->window);
}

void GameState::updateEvents(sf::Event& sfEvent)
{
	this->updateKeyboardInput(sfEvent);
	if (this->paused) {
		this->pmenu->updateEvents(sfEvent, this->mousePosView);
	}
}

void GameState::updatePauseMenuButtons()
{
}

void GameState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateKeytime(dt);

	if (!this->paused) { // Unpaused update
		
		this->updateView(dt);

		this->player->update(dt);
		this->tShape->update(dt);
	}
	else { // Paused update
		this->pmenu->update(this->mousePosView);
		this->updatePauseMenuButtons();
	}
}

void GameState::renderSquareMatrix(sf::RenderTarget& target)
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

void GameState::render(sf::RenderTarget* target)
{
	if (!target) {
		target = this->window;
	}
	this->renderTexture.clear();

	this->renderTexture.draw(this->background);
	
	this->player->render(this->renderTexture);

	this->renderTexture.draw(this->gridArea);
	this->tShape->render(this->renderTexture);
	
	this->renderSquareMatrix(this->renderTexture);

	if (this->paused) { // Pause menu render
		this->pmenu->render(this->renderTexture);
	}
	
	// FINAL RENDER
	this->renderTexture.display();

	this->renderSprite.setTexture(this->renderTexture.getTexture());
	target->draw(this->renderSprite);
}
