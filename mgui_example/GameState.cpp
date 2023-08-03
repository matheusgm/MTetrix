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
}

void GameState::initPauseMenu()
{
	this->pmenu = new PauseMenu(*this->window, this->font);

	this->pmenu->addButton("QUIT", 200.f, "Quit", [this] {this->endState(); });

}

void GameState::initPlayers()
{
	this->player = new Player(0,0, this->textures["PLAYER_SHEET"]);
}

GameState::GameState(StateData* state_data) : State(state_data)
{
	this->initKeybinds();
	this->initFonts();
	this->initTexture();
	this->initPauseMenu();
	this->initPlayers();

	this->onResizeWindow();

	this->background.setFillColor(sf::Color::Yellow);
}

GameState::~GameState()
{
	delete this->pmenu;
	delete this->player;
}

void GameState::updateView(const float& dt)
{
	//this->view.setCenter(this->player->getPosition());s
}

void GameState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getKeytime()) {
		if (!this->paused) {
			this->pauseState();
		}
		else {
			this->unpauseState();
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

	this->pmenu->onResizeWindow(*this->window);
}

void GameState::updateEvents(sf::Event& sfEvent)
{
	this->pmenu->updateEvents(sfEvent, this->mousePosView);
}

void GameState::updatePlayerInput(const float& dt)
{

	// Update player input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT")))) {
		this->player->move(-1.f, 0.f, dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT")))) {
		this->player->move(1.f, 0.f, dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP")))) {
		this->player->move(0.f, -1.f, dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN")))) {
		this->player->move(0.f, 1.f, dt);
	}
}

void GameState::updatePauseMenuButtons()
{
}

void GameState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateKeytime(dt);
	this->updateInput(dt);

	if (!this->paused) { // Unpaused update
		
		this->updateView(dt);

		this->updatePlayerInput(dt);

		this->player->update(dt);
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

	if (this->paused) { // Pause menu render
		this->pmenu->render(this->renderTexture);
	}
	
	// FINAL RENDER
	this->renderTexture.display();

	this->renderSprite.setTexture(this->renderTexture.getTexture());
	target->draw(this->renderSprite);
}
