#ifndef HITBOXCOMPONENT_H
#define HITBOXCOMPONENT_H

class HitBoxComponent
{ 
private:
	sf::Sprite& sprite;
	sf::RectangleShape hitbox;
	float offsetX;
	float offsetY;

public:
	HitBoxComponent(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height);
	virtual ~HitBoxComponent();

	// Functions
	bool checkIntersect(const sf::FloatRect& frect);

	void update();
	void render(sf::RenderTarget& target);
};

#endif
