#ifndef SETTINGSSTATE_H
#define SETTINGSSTATE_H

#include "State.h"
#include "Gui.h"

class SettingsState :
    public State 
{
private:
    // Variables
    sf::RectangleShape background;

    std::map<std::string, gui::Button*> buttons;

    sf::Text soundText;
    gui::Slider* soundSlider;
    sf::Text soundValue;

    //std::vector<sf::VideoMode> modes;

    // Functions
    void initVariables();
    void initKeybinds();
    void initGui();

public:
    SettingsState(StateData* state_data);
    virtual ~SettingsState();

    // Accessors

    // Functions
    void updateInput(const float& dt);
    void updateEvents(sf::Event& sfEvent);
    void onResizeWindow();
    void updateGui(const float& dt);
    void update(const float& dt);
    void renderGui(sf::RenderTarget& target);
    void render(sf::RenderTarget* target = nullptr);
};
#endif

