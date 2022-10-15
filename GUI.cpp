#include <sstream>
#include "gui.hpp"

GUI::GUI(const sf::Texture& texture, const sf::Font& font)
    :window{sf::VideoMode{1136, 640}, "BlackJack Application"}
    , backGround{texture}
    , font{font}
    , buttons {
        std::make_pair("Hit",sf::Button{sf:Vector2f{50, 480}, GLOBALS::BUTTON_SIZE, "Hit", font}),
        std::make_pair("Stand", sf::Button{sf::Vector2f{50, 560}, GLOBALS::BUTTON_SIZE, "Stand", font}),
        std::make_pair("Double", sf::Button{sf::Vector2f{986, 480}, GLOBALS::BUTTON_SIZE, "Double", font}),
        std::make_pair("Split", sf::Button{sf::Vector2f{986, 560}, GLOBALS::BUTTON_SIZE, "Split", font}),
        std::make_pair("Insure", sf::Button{sf::Vector2f{350, 560}, GLOBALS::BUTTON_SIZE, "Insure", font}),
        std::make_pair("OK", sf::Button{sf::Vector2f{686, 560}, GLOBAL::BUTTON_SIZE, "OK",font })
    }
{}

GUI::~GUI()
{
    if(window.isOpen()) window.close();
    exit(0);
}

playerAnswer GUI::collect_answer (
    AnswerSet& answerSet)
{
    while (window.isOpen())
    {
        window.clear();
        draw_elements();
        window.display();
        sf::Event ev{};
        while (window.pollEvent(ev))
        {
            if (ev.type == sf::Event::MouseButtonPressed)
            {
                for(auto& answer : answerSet)
                {
                    if (buttons[answer].contains(sf::Mouse::getPosition(window))
                        && sf::Mouse::isButtonPressed(sf::Mouse::Left))
                        return GLOBALS::_strAnswMap[answer];
                }
            }
            if (ev.type == sf::Event::Closed)
            {
                window.close();
                exit(0);
            }
        }
    }
}

unsigned GUI::make_bet()
{
    std::string str;
    unsigned num{0};
    while (window.isOpen())
    {
        window.clear();
        draw_elements();
        draw_bet(str);
        window.display();
        sf::Event ev{};
        while (window.pollEvent(ev))
        {
            if (ev.type == sf::Event::TextEntered)
            {
                if (ev.text.unicode >= 48 && ev.text.unicode <= 57
                    && 10 * num + ev.text.unicode - 48 <= account->get_balance())
                {
                    num = 10 * num + ev.text.unicode - 48;
                    str += ev.text.unicode;
                }
            }
            if (ev.type == sf::Event::KeyPressed)
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace)
                    && str.length())
                {
                    str.pop_back();
                    num /= 10;
                }
            }
            if (ev.type == sf::Event::MouseButtonPressed)
            {
                if (buttons["OK"].contains(sf::Mouse::getPosition(window))
                    && sf::Mouse::isButtonPressed(sf::Mouse::Left) && num)
                {
                    return num;

                }
            }
            if (ev.type == sf::Event::Closed)
            {
                window.close();
                exit(0);
            }
        }
    }
}

void GUI::add_message(const std::string& message)
{
    messages.emplace_back(message);
}

void GUI::show_results()
{
    while (window.isOpen())
    {
        window.clear();
        draw_elements();
        draw_messages();
        window.display();
        sf::Event ev{};
        while (window.pollEvent(ev))
        {
            if (ev.type == sf::Event::MouseButtonPressed)
            {
                if (buttons["OK"].contains(sf::Mouse::getPosition(window))
                    && sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    messages.clear();
                    return;
                }
            }
            if (ev.type == sf::Event::Closed)
        }
    }
}