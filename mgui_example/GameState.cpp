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
	this->pmenu->addButton("QUIT", "Quit");
	this->pmenu->addButton("Teste", "teste");
	this->pmenu->getButton("QUIT")->onPressed([this]{this->endState(); });
}

void GameState::initVariables()
{
	this->background.setFillColor(sf::Color::Yellow);

	this->tetrixLevelLabel.setFont(this->font);
	this->tetrixLevelLabel.setCharacterSize(30u);
	this->tetrixLevelLabel.setFillColor(sf::Color::Black);
	this->tetrixLevelLabel.setString("Level:");

	this->tetrixLevelValue.setFont(this->font);
	this->tetrixLevelValue.setCharacterSize(30u);
	this->tetrixLevelValue.setFillColor(sf::Color::Black);
	

	this->tetrixScoreLabel.setFont(this->font);
	this->tetrixScoreLabel.setCharacterSize(30u);
	this->tetrixScoreLabel.setFillColor(sf::Color::Black);
	this->tetrixScoreLabel.setString("Score: ");
	
	this->tetrixScoreValue.setFont(this->font);
	this->tetrixScoreValue.setCharacterSize(30u);
	this->tetrixScoreValue.setFillColor(sf::Color::Black);
}

void GameState::initPlayers()
{
	this->player = new Player(0, 0, this->textures["PLAYER_SHEET"]);
}

void GameState::initGameoverMenu()
{
	this->gameovermenu = new GameMenu(*this->window, this->font, "Game Over");
	this->gameovermenu->addButton("QUIT", "Quit");
	this->gameovermenu->addButton("RESTART", "Restart");
	this->gameovermenu->getButton("RESTART")->onPressed([this] {this->initGame(); });
	this->gameovermenu->getButton("QUIT")->onPressed([this] {this->endState(); });
	this->gameovermenu->onResizeWindow(*this->window);
}

GameState::GameState(StateData* state_data) : State(state_data)
{
	srand(static_cast<unsigned int>(time(0)));
	this->initKeybinds();
	this->initFonts();
	this->initTexture();
	this->initPauseMenu();
	this->initVariables();

	this->initPlayers();

	this->initGame();

	this->onResizeWindow();
}

GameState::~GameState()
{
	delete this->pmenu;
	delete this->gameovermenu;
	delete this->player;
	delete this->tetrix;
}

void GameState::initGame()
{
	this->gameovermenu = NULL;
	this->tetrix = new Tetrix(this->textures["TETRIX_SQUARES_SHEET"], 20, 10, 30);
	this->tetrix->onGameover([this] { this->initGameoverMenu(); });

	this->tetrix->setSoundVolume(this->stateData->audioSettings->soundVolume);

	this->tetrixLevelValue.setString(std::to_string(this->tetrix->getLevel()));
	this->tetrixScoreValue.setString(std::to_string(this->tetrix->getScore()));

	this->tetrix->onResizeWindow(*this->window);
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
			if (!this->gameovermenu)
			{
				if (!this->paused) {
					this->pauseState();
					this->tetrix->onPause();
				}
				else {
					this->unpauseState();
					this->tetrix->onResume();
				}
			}
		}

		// Update player input
		if (sfEvent.key.code ==  sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT"))) {
			this->tetrix->moveShapeLeft();
		}
		if (sfEvent.key.code == sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))) {
			this->tetrix->moveShapeRight();
		}
		if (sfEvent.key.code == sf::Keyboard::Key(this->keybinds.at("MOVE_UP"))) {
			// Rotate
			this->tetrix->rotateShape(90.f);
		}
		if (sfEvent.key.code == sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN"))) {
			this->tetrix->moveShapeDown();
			this->tetrix->resetTimer();
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

	this->tetrix->onResizeWindow(*this->window);

	this->pmenu->onResizeWindow(*this->window);
	if(this->gameovermenu)
		this->gameovermenu->onResizeWindow(*this->window);

	this->tetrixLevelLabel.setPosition(
		sf::Vector2f(
			this->tetrix->getPosition().x - 200.f,
			this->window->getSize().y / 2.f - this->tetrixLevelValue.getGlobalBounds().height - this->tetrixLevelLabel.getGlobalBounds().height - 40.f
		)
	);

	this->tetrixLevelValue.setPosition(
		sf::Vector2f(
			this->tetrix->getPosition().x - 200.f + 25.f,
			this->window->getSize().y / 2.f - this->tetrixLevelValue.getGlobalBounds().height - 20.f
		)
	);

	this->tetrixScoreLabel.setPosition(
		sf::Vector2f(
			this->tetrix->getPosition().x - 200.f,
			this->window->getSize().y / 2.f
		)
	);

	this->tetrixScoreValue.setPosition(
		sf::Vector2f(
			this->tetrix->getPosition().x - 200.f + 25.f,
			this->window->getSize().y / 2.f + this->tetrixScoreLabel.getGlobalBounds().height + 20.f
		)
	);

	
}

void GameState::updateEvents(sf::Event& sfEvent)
{
	this->updateKeyboardInput(sfEvent);
	if (this->paused) {
		this->pmenu->updateEvents(sfEvent, this->mousePosView);
	}
	if(this->gameovermenu)
		this->gameovermenu->updateEvents(sfEvent, this->mousePosView);
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
		this->tetrix->update(dt);

		// REDO
		this->tetrixLevelValue.setString(std::to_string(this->tetrix->getLevel()));
		this->tetrixScoreValue.setString(std::to_string(this->tetrix->getScore()));
	}
	else { // Paused update
		this->pmenu->update(this->mousePosView);
		this->updatePauseMenuButtons();
	}

	if (this->gameovermenu)
		this->gameovermenu->update(this->mousePosView);
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target) {
		target = this->window;
	}
	this->renderTexture.clear();

	this->renderTexture.draw(this->background);
	
	this->player->render(this->renderTexture);
	
	this->tetrix->render(this->renderTexture);

	this->renderTexture.draw(this->tetrixLevelLabel);
	this->renderTexture.draw(this->tetrixLevelValue);
	this->renderTexture.draw(this->tetrixScoreLabel);
	this->renderTexture.draw(this->tetrixScoreValue);

	if (this->paused) { // Pause menu render
		this->pmenu->render(this->renderTexture);
	}

	if (this->gameovermenu)
		this->gameovermenu->render(this->renderTexture);
	
	// FINAL RENDER
	this->renderTexture.display();

	this->renderSprite.setTexture(this->renderTexture.getTexture());
	target->draw(this->renderSprite);
}
