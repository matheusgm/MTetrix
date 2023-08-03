#include "stdafx.h"
#include "Player.h"

// Initializer functions
void Player::initVariables()
{
	this->scaleX = 2;
	this->scaleY = 2;
	this->attacking = false;
}

void Player::initComponents()
{
	
}

// Constructors / Destructors
Player::Player(float x, float y, sf::Texture& texture_sheet)
{
	this->initVariables();
	this->sprite.setScale(this->scaleX, this->scaleY);
	this->setPosition(x, y);

	this->createHitboxComponent(this->sprite, 15.f, 15.f, 32.f* this->scaleX -30.f, 32.f* this->scaleY-15.f);
	this->createMovementComponent(300.f, 15.f, 5.f);
	this->createAnimationComponent(texture_sheet);

	this->animationComponent->addAnimation("IDLE", 11.f, 0, 0, 3, 0, 32, 32);
	this->animationComponent->addAnimation("WALK", 7.f, 0, 1, 5, 1, 32, 32);
	this->animationComponent->addAnimation("ATTACK", 9.f, 0, 5, 5, 5, 32, 32);
}

Player::~Player()
{
}

// Functions
void Player::updateAttack()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		this->attacking = true;
	}
}

void Player::updateAnimation(const float& dt)
{
	if (this->attacking)
	{
		if (this->animationComponent->play("ATTACK", dt, true))
			this->attacking = false;
	}
	if (this->movementComponent->getState(IDLE))
	{
		this->animationComponent->play("IDLE", dt);
	}
	else if (this->movementComponent->getState(MOVING_RIGHT))
	{
		if (this->sprite.getScale().x < 0.f) {
			this->sprite.setOrigin(0.f, 0.f);
			this->sprite.setScale(this->scaleX, this->scaleY);
		}
		this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_LEFT))
	{
		if (this->sprite.getScale().x > 0.f) {
			this->sprite.setOrigin(16.f * this->scaleX, 0.f);
			this->sprite.setScale(-this->scaleX, this->scaleY);
		}
		this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_UP))
	{

		this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_DOWN))
	{
		this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
	}
}

void Player::update(const float& dt)
{
	this->movementComponent->update(dt);

	this->updateAttack();
	
	this->updateAnimation(dt);

	this->hitboxComponent->update();
	
}
