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

    GameMenu* pmenu;
    GameMenu* gameovermenu;

    Player* player;
    Tetrix* tetrix;

    sf::Text tetrixScoreLabel;
    sf::Text tetrixScoreValue;
    sf::Text tetrixLevelLabel;
    sf::Text tetrixLevelValue;

    // Functions
    void initDeferredRender();
    void initKeybinds();
    void initTexture();
    void initPauseMenu();
    void initVariables();
    void initPlayers();

    void initGameoverMenu();


public:
    GameState(StateData* state_data);
    virtual ~GameState();

    void initGame();

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
