#ifndef GUI_H
#define GUI_H

enum button_states{ NORMAL = 0, HOVER, PRESSED, DISABLED};

namespace gui
{
	class Button
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

	public:
		Button(float x, float y, float width, float height,
			sf::Font* font, std::string text = "Text", unsigned character_size = 24,
			sf::Color text_normal_color = sf::Color::Color(0, 0, 0, 255), sf::Color text_hover_color = sf::Color::Color(255, 255, 255, 255), sf::Color text_pressed_color = sf::Color::Color(200, 200, 200, 255),
			sf::Color normal_color = sf::Color::Color(255, 255, 255, 255), sf::Color hover_color = sf::Color::Color(0, 0, 0, 255), sf::Color pressed_color = sf::Color::Color(60, 60, 60, 255),
			sf::Color outline_normal_color = sf::Color::Color(0, 0, 0, 255), sf::Color outline_hover_color = sf::Color::Color(0, 0, 0, 255), sf::Color outline_pressed_color = sf::Color::Color(0, 0, 0, 255),
			short unsigned id = 0);

		virtual ~Button();

		// Acessors
		const bool isPressed() const;
		const std::string getText() const;
		const short unsigned& getId() const;
		const sf::Vector2f& getPosition() const;
		const sf::Vector2f& getSize() const;
		const float getTop() const;
		const float getBottom() const;
		const float getLeft() const;
		const float getRight() const;

		// Modifier
		void setPosition(const float x, const float y);
		void setSize(const float width, const float height);
		void setText(const std::string text);
		void setId(const short unsigned id);
		void setDisabled(const bool disable);
		void onPressed(std::function<void()> callback);

		// Functions
		void updateEvents(sf::Event& sfEvent, const sf::Vector2f& mousePos);
		void update(const sf::Vector2f& mousePos);
		void render(sf::RenderTarget& target);
	};

	class Slider
	{
	private:
		sf::RectangleShape backgroundShape;
		sf::RectangleShape foregroundShape;

		sf::CircleShape indicatorShape;
		bool indicatorPressed;

		std::function<void()> onValueChangeCallback;


		int minValue;
		int maxValue;
		int step;

		int value;

	public:
		Slider(float x, float y, float width, float height,
			int min_value, int max_value, int default_value = 0, int step = 1,
			sf::Color background_color = sf::Color::Color(192, 192, 192, 220), sf::Color foreground_color = sf::Color::Color(0, 100, 0, 220), sf::Color indicator_color = sf::Color::Color(240, 240, 240, 255)
			);
		virtual ~Slider();

		// Acessors
		const int getValue() const;
		const sf::Vector2f& getSize() const;

		// Modifier
		void setPosition(const float x, const float y);
		void setSize(const float width, const float height);
		void onValueChange(std::function<void()> callback);

		// Functions
		void updateIndicator();
		void updateEvents(sf::Event& sfEvent, const sf::Vector2f& mousePos);
		void update(const sf::Vector2f& mousePos);
		void render(sf::RenderTarget& target);
	};
}
#endif
