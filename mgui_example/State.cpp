#include "stdafx.h"
#include "State.h"

void State::initFonts()
{
	if (!this->font.loadFromFile("Fonts/MochiyPopPOne-Regular.ttf")) {
		throw("ERROR::STATE::COULD NOT LOAD FONT");
	}
}

State::State(StateData* state_data)
{
	this->stateData = state_data;
	this->window = state_data->window;
	this->supportedKeys = state_data->supportedKeys;
	this->states = state_data->states;
	this->quit = false;
	this->paused = false;
	this->keytime = 0.f;
	this->keytimeMax = 10.f;
	this->gridSize = state_data->gridSize;
}

State::~State()
{
}

// Accessors
const bool& State::getQuit() const
{
	return this->quit;
}

const bool State::getKeytime()
{
	if (this->keytime >= this->keytimeMax) {
		this->keytime = 0.f;
		return true;
	}
	return false;
}

const sf::Vector2f State::getWindowCenter()
{
	return sf::Vector2f(
		static_cast<float>(this->window->getSize().x / 2.f),
		static_cast<float>(this->window->getSize().y / 2.f)
		);
}

// Functions
void State::endState() 
{
	this->quit = true;
}

void State::pauseState()
{
	this->paused = true;
}

void State::unpauseState()
{
	this->paused = false;
}

void State::updateMousePositions()
{
	this->mousePosScreen = sf::Mouse::getPosition();
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));

}

void State::updateKeytime(const float& dt)
{
	if (this->keytime < this->keytimeMax) {
		this->keytime += 100.f * dt;
	}
}
