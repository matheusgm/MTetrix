#ifndef MOVEMENT_COMPONENT_H
#define MOVEMENT_COMPONENT_H

enum movement_states {IDLE = 0, MOVING = 1, MOVING_LEFT, MOVING_RIGHT, MOVING_UP, MOVING_DOWN};

class MovementComponent
{
private:
	sf::Sprite& sprite;	

	float maxVelocity;

	sf::Vector2f velocity;
	float acceleration;
	float deceleration;

	// Initializer Function


public:
	MovementComponent(sf::Sprite& sprite, float maxVelocity, float acceleration, float deceleration);
	virtual ~MovementComponent();

	// Accessors
	const float& getMaxVelocity() const;
	const sf::Vector2f& getVelocity() const;

	// Functions
	const bool getState(const short unsigned state) const;

	void move(const float x, const float y, const float& dt);
	void update(const float& dt);

};
#endif
