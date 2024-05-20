#ifndef GUI_BASEGUI_H
#define GUI_BASEGUI_H

namespace gui
{
	class BaseGui
	{
	public:
		// Modifier
		virtual void setPosition(const float x, const float y) = 0;
		virtual void setSize(const float width, const float height) = 0;

		// Functions
		virtual void updateEvents(sf::Event& sfEvent, const sf::Vector2f& mousePos) = 0;
		virtual void update(const sf::Vector2f& mousePos) = 0;
		virtual void render(sf::RenderTarget& target) = 0;
	};
}
#endif

