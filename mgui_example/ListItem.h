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

        ListItem();
        virtual ~ListItem();

        void setPosition(float x, float y);
        void setSize(float x, float y);
        const sf::Vector2f& getSize() const;

        void render(sf::RenderTarget& target);
    };
}
#endif

