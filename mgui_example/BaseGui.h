#ifndef GUI_BASEGUI_H
#define GUI_BASEGUI_H

namespace gui
{
	class BaseGui
	{

	private:
		sf::Vector2f position;
		sf::Vector2f size;
	public:
		BaseGui(sf::Vector2f position, sf::Vector2f size) {
			this->position = position;
			this->size = size;
		}

		// Acessors
		const sf::Vector2f& getPosition() const;
		const sf::Vector2f& getSize() const;
		const float getTop() const;
		const float getBottom() const;
		const float getLeft() const;
		const float getRight() const;
		const float getWidth() const;
		const float getHeight() const;

		// Modifier
		void setPosition(sf::Vector2f position);
		void setSize(sf::Vector2f size);
		virtual void setPosition(const float x, const float y) = 0;
		virtual void setSize(const float width, const float height) = 0;

		// Functions
		virtual bool globalBoundsContains(const sf::Vector2f& points) = 0;
		virtual void updateEvents(sf::Event& sfEvent, const sf::Vector2f& mousePos) = 0;
		virtual void update(const sf::Vector2f& mousePos) = 0;
		virtual void render(sf::RenderTarget& target) = 0;
	};
}
#endif

