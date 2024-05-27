#ifndef GUI_BUTTON_H
#define GUI_BUTTON_H

#include "BaseGui.h"

enum button_states { NORMAL = 0, HOVER, PRESSED, DISABLED };

namespace gui {
	class Button : public BaseGui
	{
	private:
		short unsigned buttonState;
		short unsigned id;
		bool buttonPressed;

		sf::RectangleShape shape;
		sf::Font* font;
		sf::Text text;

		std::function<void()> onPressedCallback;

		sf::Color textNormalColor;
		sf::Color textHoverColor;
		sf::Color textPressedColor;
		sf::Color textDisabledColor;

		sf::Color normalColor;
		sf::Color hoverColor;
		sf::Color pressedColor;
		sf::Color disabledColor;

		sf::Color outlineNormalColor;
		sf::Color outlineHoverColor;
		sf::Color outlinePressedColor;
		sf::Color outlineDisabledColor;

		bool mouseReleased = false;

	public:
		Button(float x, float y, float width, float height,
			sf::Font* font = nullptr, std::string text = "Text", unsigned character_size = 24,
			sf::Color text_normal_color = sf::Color::Color(0, 0, 0, 255), sf::Color text_hover_color = sf::Color::Color(255, 255, 255, 255), sf::Color text_pressed_color = sf::Color::Color(200, 200, 200, 255),
			sf::Color normal_color = sf::Color::Color(255, 255, 255, 255), sf::Color hover_color = sf::Color::Color(0, 0, 0, 255), sf::Color pressed_color = sf::Color::Color(60, 60, 60, 255),
			sf::Color outline_normal_color = sf::Color::Color(0, 0, 0, 255), sf::Color outline_hover_color = sf::Color::Color(0, 0, 0, 255), sf::Color outline_pressed_color = sf::Color::Color(0, 0, 0, 255),
			short unsigned id = 0);

		Button(float x, float y, float width, float height, std::string text = "Text", unsigned character_size = 24)
			: Button(x, y, width, height, nullptr, text, character_size) {};

		Button() : Button(0.f, 0.f, 50.f, 50.f, nullptr) {};

		virtual ~Button();

		// Acessors
		const bool isPressed() const;
		const std::string getText() const;
		const short unsigned& getId() const;

		// Modifier
		void setPosition(const float x, const float y) override;
		void setSize(const float width, const float height) override;
		void setText(const std::string text);
		void setId(const short unsigned id);
		void setDisabled(const bool disable);
		void onPressed(std::function<void()> callback);

		// Functions
		// Herdado por meio de BaseGui
		bool globalBoundsContains(const sf::Vector2f& points) override;
		void updateEvents(sf::Event& sfEvent, const sf::Vector2f& mousePos) override;
		void update(const sf::Vector2f& mousePos) override;
		void render(sf::RenderTarget& target) override;
	};
}
#endif