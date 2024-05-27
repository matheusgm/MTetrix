#ifndef GUI_LISTITEM_H
#define GUI_LISTITEM_H
#include "BaseGui.h"
namespace gui
{
    class ListItem : public BaseGui
    {
    public:
        sf::RectangleShape shape;
        sf::Text text;

        ListItem(sf::Color color = sf::Color::Red);
        virtual ~ListItem();

        void setPosition(float x, float y) override;
        void setSize(float x, float y) override;

        bool globalBoundsContains(const sf::Vector2f& points) override;
        void updateEvents(sf::Event& sfEvent, const sf::Vector2f& mousePos) override;
        void update(const sf::Vector2f& mousePos) override;
        void render(sf::RenderTarget& target) override;
    };
}
#endif

