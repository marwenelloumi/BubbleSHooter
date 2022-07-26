#include "PushButton.h"

PushButton::PushButton(const sf::Vector2f& p, const sf::Vector2f& s)
{
    this->size = s;
    this->pos = p;
    this->setPosition(this->pos);



}
PushButton::PushButton(const sf::Vector2f& p, const sf::Vector2f& s, sf::Text tex)
{
    this->size = s;
    this->pos = p;
    this->setPosition(this->pos);
    this->text = tex;


}

PushButton::PushButton()
{
}

bool PushButton::isClicked(const sf::Event& event, int button = sf::Mouse::Left)
{
    return (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == button &&
        event.mouseButton.x >= pos.x && event.mouseButton.y >= pos.y &&
        event.mouseButton.x <= pos.x + size.x && event.mouseButton.y <= pos.y + size.y);

}