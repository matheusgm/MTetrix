#ifndef GUI_LISTITEM_H
#define GUI_LISTITEM_H

namespace gui
{
    class ListItem
    {
    public:
        sf::RectangleShape shape;
        sf::Text text;
        sf::Vector2f size;
        sf::Vector2f position;

        ListItem(sf::Color color = sf::Color::Red);
        virtual ~ListItem();

        bool isInsideVerticalArea(float yUp, float yDown);

        void setPosition(float x, float y);
        void setSize(float x, float y);
        const sf::Vector2f& getSize() const;

        void render(sf::RenderTarget& target);
    };
}
#endif

