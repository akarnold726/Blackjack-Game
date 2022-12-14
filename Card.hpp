#ifndef CARD_HPP
#define CARD_HPP

#include "enums.hpp"
#include <cstddef> 
#include <string>

#define NUM_VALUES 13
#define NUM_SUITS 4

class Card 
{
    cardValue _value;
    cardSuit _suit;
public: 
    explicit Card(size_t value) noexcept;
    Card(cardValue value, cardSuit suit) noexcept;

    Card(const Card&) noexcept = default;
    Card(Card&&) nooexcept = default;
    Card& operator = (const Card&) noexcept = default; 
    Card& operator = (Card&&) noexcept = default;

    [[nodiscard]] unsigned get_score() const noexcept;
    static bool equal_score(const Card&, const Card&);

    void set_suit(size_t value);
    void set_suit(const cardSuit& suit) noexcept {_suit = suit; }
    [[nodisard]] const cardSuit& get_suit() const noexcept {return _suit; }

    void set_val(size_t value);
    void set_val(const cardValue& value) noexcept {_value = value; }
    [[nodiscard]] const cardValue& get_value() const noexcept { return _value; }

    [[nodiscard]] std::string to_str() const noexcept; 
};

#endif 