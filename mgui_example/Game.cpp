#include "stdafx.h"
#include "Game.h"

// Static functions

// Initializer functions

void Game::initVariables()
{
	this->window = NULL;
	this->dt = 0.f;
	this->gridSize = 50.f;
}

void Game::initGraphicsSettings()
{
	this->gfxSettings.loadFromFile("Config/graphics.ini");
}

void Game::initAudioSettings()
{
	this->audioSettings.loadFromFile("Config/audio.ini");
}

void Game::initWindow(){

	/* Create a SFML window */

	if (this->gfxSettings.fullscreen)
	{
		this->window = new sf::RenderWindow(
			this->gfxSettings.resolution,
			this->gfxSettings.title,
			sf::Style::Fullscreen,
			this->gfxSettings.contextSettings
		);
	}
	else
	{
		this->window = new sf::RenderWindow(
			this->gfxSettings.resolution,
			this->gfxSettings.title,
			sf::Style::Default,
			this->gfxSettings.contextSettings
		);
	}

	this->window->setFramerateLimit(this->gfxSettings.frameRateLimit);
	this->window->setVerticalSyncEnabled(this->gfxSettings.verticalSync);
}


void Game::initKeys()
{

	std::ifstream ifs("Config/supported_keys.ini");

	if (ifs.is_open()) {
		std::string key = "";
		int key_value = 0;

		while (ifs >> key >> key_value) {
			this->supportedKeys[key] = key_value;
		}
	}

	ifs.close();

	// DEBUG REMOVE LATER!
	for (auto i : this->supportedKeys) {
		std::cout << i.first << " " << i.second << "\n";
	}
	
}

void Game::initStateData()
{
	this->stateData.window = this->window;
	this->stateData.gfxSettings = &this->gfxSettings;
	this->stateData.audioSettings = &this->audioSettings;
	this->stateData.supportedKeys = &this->supportedKeys;
	this->stateData.states = &this->states;
	this->stateData.gridSize = this->gridSize;
}

void Game::initStates()
{
	this->states.push(new MainMenuState(&this->stateData));
}


// Constructors / Destructors
Game::Game(){
	this->initVariables();
	this->initGraphicsSettings();
	this->initAudioSettings();
	this->initWindow();
	this->initKeys();
	this->initStateData();
	this->initStates();

}

Game::~Game()
{
	delete this->window;

	while (!this->states.empty()) {
		delete this->states.top();
		this->states.pop();
	}
}




// Functions
void Game::endApplication()
{
	std::cout << "Ending Application!" << "\n";
}


void Game::updateDt()
{
	this->dt = this->dtClock.restart().asSeconds();

}

void Game::updateSFMLEvents()
{
	while (this->window->pollEvent(this->sfEvent)) {
		if (this->sfEvent.type == sf::Event::Closed) {
			this->window->close();
		}else if (this->sfEvent.type == sf::Event::Resized) {
			// resize my view
			sf::FloatRect visibleArea(0.f, 0.f, static_cast<float>(this->sfEvent.size.width), static_cast<float>(this->sfEvent.size.height));
			this->window->setView(sf::View(visibleArea));
			this->gfxSettings.resolution.width = this->sfEvent.size.width;
			this->gfxSettings.resolution.height = this->sfEvent.size.height;
			if (!this->states.empty()) {
				this->states.top()->onResizeWindow();
			}
		}
		if (!this->states.empty()) {
			this->states.top()->updateEvents(this->sfEvent);
		}
	}
}

void Game::update()
{
	this->updateSFMLEvents();

	if (!this->states.empty()) {
		this->states.top()->update(this->dt);
		
		if (this->states.top()->getQuit()) {
			this->states.top()->endState();
			delete this->states.top();
			this->states.pop();
			if (!this->states.empty()) { // Rever, talvez poderia ser bom uma verificação para saber se precisa atualizar
				this->states.top()->onResizeWindow();
			}
		}
	}
	// Application end
	else {
		this->endApplication();
		this->window->close();
	}

	

}

void Game::render()
{
	this->window->clear();

	// Render items
	if (!this->states.empty()) {
		this->states.top()->render();
	}

	this->window->display();
}

void Game::run()
{
	while (this->window->isOpen()) {
		this->updateDt();
		this->update();
		this->render();
	}
}


