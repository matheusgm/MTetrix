#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
#include "PauseMenu.h"
#include "Tetrix.h"

class PauseMenu;
class Player;
class TileMap;

class GameState :
    public State
{
private:
    sf::RenderTexture renderTexture;
    sf::Sprite renderSprite;

    sf::RectangleShape background;

    PauseMenu* pmenu;

    Player* player;
    Tetrix* tetrix;

    sf::Text tetrixScore;
    sf::Text tetrixLevel;

    // Functions
    void initDeferredRender();
    void initKeybinds();
    void initTexture();
    void initPauseMenu();
    void initVariables();
    void initPlayers();


public:
    GameState(StateData* state_data);
    virtual ~GameState();

    // Functions
    void updateView(const float& dt);
    void updateKeyboardInput(sf::Event& sfEvent);
    void onResizeWindow();
    void updateEvents(sf::Event& sfEvent);
    void updatePauseMenuButtons();
    void update(const float& dt);
    void render(sf::RenderTarget* target = nullptr);
};
#endif
