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

}

void GameState::initPlayers()
{
	this->player = new Player(0, 0, this->textures["PLAYER_SHEET"]);
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

	this->tetrix = new Tetrix(this->textures["TETRIX_SQUARES_SHEET"]);

	this->onResizeWindow();

	this->background.setFillColor(sf::Color::Yellow);
}

GameState::~GameState()
{
	delete this->pmenu;
	delete this->player;
	delete this->tetrix;
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
		this->tetrix->update(dt);
	}
	else { // Paused update
		this->pmenu->update(this->mousePosView);
		this->updatePauseMenuButtons();
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
	
	this->tetrix->render(this->renderTexture);

	if (this->paused) { // Pause menu render
		this->pmenu->render(this->renderTexture);
	}
	
	// FINAL RENDER
	this->renderTexture.display();

	this->renderSprite.setTexture(this->renderTexture.getTexture());
	target->draw(this->renderSprite);
}
