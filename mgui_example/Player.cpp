#include "stdafx.h"
#include "Player.h"

// Initializer functions
void Player::initVariables()
{
}

void Player::initComponents()
{
	
}

// Constructors / Destructors
Player::Player(float x, float y, sf::Texture& texture_sheet)
{
	this->initVariables();
	this->setPosition(x, y);

	this->createMovementComponent(300.f, 15.f, 5.f);


}

Player::~Player()
{
}

void Player::update(const float& dt)
{
	this->movementComponent->update(dt);

}
