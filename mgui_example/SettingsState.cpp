#include "stdafx.h"
#include "SettingsState.h"

void SettingsState::initVariables()
{
	//this->modes = sf::VideoMode::getFullscreenModes();
}

void SettingsState::initKeybinds()
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

void SettingsState::initGui()
{
	this->buttons["BACK"] = new gui::Button(
		100.f, 100.f,
		150.f, 50.f,
		&this->font, "Back", 32);

	this->buttons["APPLY"] = new gui::Button(
		100.f, 200.f,
		150.f, 50.f,
		&this->font, "Apply", 32);

	// Button functionality
	// Quit the game
	this->buttons["BACK"]->onPressed([this] {
		this->endState();
	});

	// Apply selected settings
	this->buttons["APPLY"]->onPressed([this] {
		std::string soundValueString = this->soundValue.getString();
		this->stateData->audioSettings->soundVolume = std::stof(soundValueString);
		this->stateData->audioSettings->saveToFile("Config/audio.ini");
		this->endState();
		// TEST REMOVE LATER
		//this->window->create(this->stateData->gfxSettings->resolution, this->stateData->gfxSettings->title, sf::Style::Default);

		});

	/*std::vector<std::string> modes_str;
	for (auto& i : this->modes) {
		modes_str.push_back(std::to_string(i.width) + 'x' + std::to_string(i.height));
	}*/

	// SOUND ====================================
	this->soundText.setFillColor(sf::Color::Black);
	this->soundText.setCharacterSize(32);
	this->soundText.setString("Sound:");
	this->soundText.setFont(this->font);
	

	this->soundSlider = new gui::Slider(100.f, 100.f, 250.f, 16.f, 0, 100, static_cast<int>(this->stateData->audioSettings->soundVolume));
	this->soundSlider->onValueChange(
		[this] {this->soundValue.setString(std::to_string(this->soundSlider->getValue()) + "%"); }
	);

	this->soundValue.setFillColor(sf::Color::Black);
	this->soundValue.setCharacterSize(32);
	this->soundValue.setString(std::to_string(this->soundSlider->getValue()) + "%");
	this->soundValue.setFont(this->font);

	// LIST VIEW ====================================
	this->listView = new gui::ListView(200.f, 200.f, 200.f, 300.f);

	// SELECT ====================================
	this->select = new gui::Select(500.f, 200.f, 200.f, 100.f);

	// SCROLL ====================================
	this->scroll = new gui::Scroll(1000.f, 200.f, 20.f, 200.f);
}


SettingsState::SettingsState(StateData* state_data)
	:State(state_data)
{
	this->initVariables();
	this->initFonts();
	this->initKeybinds();
	this->initGui();
	this->onResizeWindow();
	
	this->background.setFillColor(sf::Color::Cyan);
}

SettingsState::~SettingsState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it) {
		delete it->second;
	}

	delete this->soundSlider;
	delete this->listView;
	delete this->select;
	delete this->scroll;
}

// Accessors

// Functions

void SettingsState::updateKeyboardInput(sf::Event& sfEvent)
{

}

void SettingsState::updateEvents(sf::Event& sfEvent)
{
	this->updateKeyboardInput(sfEvent);
	for (auto& it : this->buttons) {
		it.second->updateEvents(sfEvent, this->mousePosView);
	}
	this->soundSlider->updateEvents(sfEvent, this->mousePosView);

	this->listView->updateEvents(sfEvent, this->mousePosView);

	this->select->updateEvents(sfEvent, this->mousePosView);

	this->scroll->updateEvents(sfEvent, this->mousePosView);
}

void SettingsState::onResizeWindow()
{
	sf::Vector2f window_center = this->getWindowCenter();
	sf::Vector2u window_size = this->window->getSize();

	float gap = 50.f;

	// Background
	this->background.setSize(
		sf::Vector2f(
			static_cast<float>(window_size.x),
			static_cast<float>(window_size.y)
		)
	);

	// Buttons
	this->buttons["BACK"]->setPosition(window_size.x - 150.f - gap, window_size.y - 50.f - gap);
	gui::Button& firstBtn = *this->buttons["BACK"];
	this->buttons["APPLY"]->setPosition(firstBtn.getLeft() - 150.f - gap, window_size.y - 50.f - gap);

	// Sound Slider
	this->soundText.setPosition(sf::Vector2f((window_center.x / 2.f) - (this->soundText.getGlobalBounds().width / 2.f), gap));
	this->soundValue.setPosition(sf::Vector2f((3.f * window_center.x / 2.f), gap));
	this->soundSlider->setPosition(this->soundText.getPosition().x + this->soundText.getGlobalBounds().width + gap, 50.f + (this->soundText.getGlobalBounds().height / 2.f));
	this->soundSlider->setSize(this->soundValue.getPosition().x - this->soundText.getPosition().x - this->soundText.getGlobalBounds().width - 2*gap , 16.f);
}

void SettingsState::updateGui(const float& dt)
{
	/* Updates all the gui in the state and handles their functionality */
	// Buttons
	for (auto& it : this->buttons) {
		it.second->update(this->mousePosView);
	}
	this->soundSlider->update(this->mousePosView);
	this->listView->update(this->mousePosView);
	this->select->update(this->mousePosView);
	this->scroll->update(this->mousePosView);
}

void SettingsState::update(const float& dt)
{
	this->updateMousePositions();

	this->updateGui(dt);
}

void SettingsState::renderGui(sf::RenderTarget& target)
{
	for (auto& it : this->buttons) {
		it.second->render(target);
	}

	target.draw(this->soundText);
	target.draw(this->soundValue);
	this->soundSlider->render(target);

	this->listView->render(target);
	this->select->render(target);
	this->scroll->render(target);

}

void SettingsState::render(sf::RenderTarget* target)
{
	if (!target) {
		target = this->window;
	}

	target->draw(this->background);

	this->renderGui(*target);

}

