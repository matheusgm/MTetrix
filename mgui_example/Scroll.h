#ifndef GUI_SCROLL_H
#define GUI_SCROLL_H
#include "BaseGui.h"
#include "Button.h"

namespace gui {
    class Scroll :
        public BaseGui
    {
    private:
        sf::RectangleShape shape;

        Button* buttonUp;
        Button* buttonDown;
        sf::RectangleShape indicatorShape;
        bool indicatorPressed;

        std::function<void()> onValueChangeCallback;

        int minValue = 0;
        int maxValue = 100;
        int step = 1;

        int value = 0;

    public:
        Scroll(float x, float y, float width, float height, sf::Font* font);
        virtual ~Scroll();

        void updateIndicator();
        void scrollWheel(int delta);
        int getValue();

        void setPosition(const float x, const float y) override;
        void setSize(const float width, const float height) override;
        void onValueChange(std::function<void()> callback);
        
        // Herdado por meio de BaseGui
        bool globalBoundsContains(const sf::Vector2f& points) override;
        void updateEvents(sf::Event& sfEvent, const sf::Vector2f& mousePos) override;
        void update(const sf::Vector2f& mousePos) override;
        void render(sf::RenderTarget& target) override;
    };
}
#endif

