#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
#include "PauseMenu.h"
#include "TetrixShape.h"

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

    // Tetrix Variables
    sf::RectangleShape gridArea;
    int squareSize;
    int rows;
    int columns;

    sf::Texture squaresTexture;
    TetrixShape* tShape;
    TetrixSquare*** squaresMatrix;

    // Functions
    void initDeferredRender();
    void initKeybinds();
    void initTexture();
    void initPauseMenu();
    void initVariables();
    void initPlayers();

    // Tetrix Functions
    void initSquareMatrix();
    bool checkBottom();
    bool checkOverlap();
    int checkLeftSide();
    int checkRightSide();
    void shapeActionFinished();

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
    void renderSquareMatrix(sf::RenderTarget& target);
    void render(sf::RenderTarget* target = nullptr);
};
#endif
