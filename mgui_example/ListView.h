#ifndef GUI_LISTVIEW_H
#define GUI_LISTVIEW_H

#include "BaseGui.h"
#include "Scroll.h"

namespace gui
{
	class ListView : BaseGui
	{
	private:
		sf::RectangleShape shape;

		Scroll* scroll;

	public:
		ListView(float x, float y, float width, float height, sf::Font* font);
		virtual ~ListView();

		// Modifier
		void setPosition(const float x, const float y) override;
		void setSize(const float width, const float height) override;

		// Herdado por meio de BaseGui
		void updateEvents(sf::Event& sfEvent, const sf::Vector2f& mousePos) override;
		void update(const sf::Vector2f& mousePos) override;
		void render(sf::RenderTarget& target) override;
	};
}
#endif

