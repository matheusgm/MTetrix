#ifndef STATE_H
#define STATE_H

#include "Player.h"
#include "GraphicsSettings.h"

class Player;
class GraphicsSettings;
class State;

struct StateData
{
	// Varibles
	float gridSize;
	sf::RenderWindow* window;
	GraphicsSettings* gfxSettings;
	std::map<std::string, int>* supportedKeys;
	std::stack<State*>* states;

	StateData() = default;
};

class State
{
private:

protected:
	StateData* stateData;
	std::stack<State*>* states;
	sf::RenderWindow* window;
	sf::Font font;
	std::map<std::string, int>* supportedKeys;
	std::map<std::string, int> keybinds;
	bool quit;
	bool paused;
	float keytime;
	float keytimeMax;
	float gridSize;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	// Resources
	std::map<std::string, sf::Texture> textures;

	// Functions
	virtual void initKeybinds() = 0;
	void initFonts();

public:
	State(StateData* state_data);
	virtual ~State();

	// Accessors
	const bool& getQuit() const;
	const bool getKeytime();
	const sf::Vector2f getWindowCenter();

	// Functions
	void endState();
	void pauseState();
	void unpauseState();

	virtual void updateMousePositions();
	virtual void updateKeytime(const float& dt);
	virtual void updateInput(const float& dt) = 0;
	virtual void updateEvents(sf::Event& sfEvent) = 0;
	virtual void onResizeWindow() = 0;
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target = nullptr) = 0;
};
#endif
