#include "stdafx.h"
#include "MainMenuState.h"

void MainMenuState::initKeybinds()
{

	std::ifstream ifs("Config/mainmenustate_keybinds.ini");

	if (ifs.is_open()) {
		std::string key = "";
		std::string key2 = "";

		while (ifs >> key >> key2) {
			this->keybinds[key] = this->supportedKeys->at(key2);
		}
	}

	ifs.close();
}

void MainMenuState::initGui()
{
	// Buttons
	this->buttons["GAME_STATE"] = new gui::Button(
		100.f, 100.f,
		250.f, 50.f,
		&this->font, "New Game", 32);

	this->buttons["SETTINGS_STATE"] = new gui::Button(
		100.f, 200.f,
		 250.f, 50.f,
		&this->font, "Settings", 32);

	this->buttons["EXIT_STATE"] = new gui::Button(
		100.f, 300.f,
		250.f, 50.f,
		&this->font, "Quit", 32);

	// New Game
	this->buttons["GAME_STATE"]->onPressed([this] {
		this->states->push(new GameState(this->stateData));
		});

	// Settings
	this->buttons["SETTINGS_STATE"]->onPressed([this] {
		this->states->push(new SettingsState(this->stateData));
		});

	// Quit the game
	this->buttons["EXIT_STATE"]->onPressed([this] {
		this->endState();
		});

}

MainMenuState::MainMenuState(StateData* state_data) 
	: State(state_data)
{
	this->initFonts();
	this->initKeybinds();
	this->initGui();
	this->onResizeWindow();

	this->background.setFillColor(sf::Color::Magenta);
}

MainMenuState::~MainMenuState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it) {
		delete it->second;
	}
}


void MainMenuState::updateKeyboardInput(sf::Event& sfEvent)
{

}

void MainMenuState::updateEvents(sf::Event& sfEvent)
{
	this->updateKeyboardInput(sfEvent);
	for (auto& it : this->buttons) {
		it.second->updateEvents(sfEvent, this->mousePosView);
	}
}

void MainMenuState::onResizeWindow()
{
	sf::Vector2f window_center = this->getWindowCenter();
	sf::Vector2u window_size = this->window->getSize();

	float gap = 50.f;

	this->background.setSize(
		sf::Vector2f(
			static_cast<float>(window_size.x),
			static_cast<float>(window_size.y)
		)
	);

	this->buttons["GAME_STATE"]->setPosition(window_center.x - 125.f, 0 + gap);

	gui::Button& firstBtn = *this->buttons["GAME_STATE"];

	this->buttons["SETTINGS_STATE"]->setPosition(firstBtn.getLeft(), firstBtn.getBottom() + gap);
	this->buttons["EXIT_STATE"]->setPosition(firstBtn.getLeft(), window_size.y - 50.f - gap);
}

void MainMenuState::updateGui()
{
	/* Updates all the buttons in the state and handles their functionality */
	for (auto& it : this->buttons) {
		it.second->update(this->mousePosView);
	}
}

void MainMenuState::update(const float& dt)
{
	this->updateMousePositions();

	this->updateGui();
}

void MainMenuState::renderGui(sf::RenderTarget& target)
{
	for (auto& it : this->buttons) {
		it.second->render(target);
	}
}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target) {
		target = this->window;
	}

	target->draw(this->background);

	this->renderGui(*target);


}

