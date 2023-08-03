#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H
#include "GameState.h"
#include "SettingsState.h"
#include "Gui.h"

class MainMenuState :
    public State
{
private: 
    // Variables
    sf::RectangleShape background;

    std::map<std::string, gui::Button*> buttons;

    // Functions
    void initKeybinds();
    void initGui();

public:
    MainMenuState(StateData* state_data);
    virtual ~MainMenuState();

    // Functions
    void updateInput(const float& dt);
    void updateEvents(sf::Event& sfEvent);
    void onResizeWindow();
    void updateGui();
    void update(const float& dt);
    void renderGui(sf::RenderTarget& target);
    void render(sf::RenderTarget* target = nullptr);
};  
#endif

