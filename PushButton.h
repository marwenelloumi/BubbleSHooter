#pragma once
#include <SFML\Graphics\Sprite.hpp>
#include <SFML\Window\Event.hpp>
#include <SFML\Graphics\Text.hpp>

class PushButton : public sf::Sprite {
public:
    sf::Vector2f pos;
    sf::Vector2f size;


    sf::Text text;



    PushButton(const sf::Vector2f& pos, const sf::Vector2f& size);


    PushButton(const sf::Vector2f& pos, const sf::Vector2f& size, sf::Text);
    PushButton();

    bool isClicked(const sf::Event& event, int button);


};