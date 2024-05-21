#ifndef GUI_SELECT_H
#define GUI_SELECT_H
#include "BaseGui.h"
namespace gui
{
    class Select :
        public BaseGui
    {
    private:
        sf::RectangleShape shape;

    public:
        Select(float x, float y, float width, float height);
        virtual ~Select();

        // Modifier
        void setPosition(const float x, const float y) override;
        void setSize(const float width, const float height) override;

        // Herdado por meio de BaseGui
        bool globalBoundsContains(const sf::Vector2f& points) override;
        void updateEvents(sf::Event& sfEvent, const sf::Vector2f& mousePos) override;
        void update(const sf::Vector2f& mousePos) override;
        void render(sf::RenderTarget& target) override;
    };
}
#endif

