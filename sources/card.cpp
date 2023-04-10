//
// Created by asaf7 on 3/21/2023.
//

#include "card.hpp"
#include <string>


//implement the card class

Card::Card() {
}

Card::Card(Value value, Suit suit) {
    _suit = suit;
    _value = value;
}

void Card::set_suit(Suit suit) {
    _suit = suit;
}

void Card::set_value(Value value) {
    _value = value;
}

Suit Card::get_suit() {
    return _suit;
}

Value Card::get_value() {
    return _value;
}

int Card::compare(Card card) {
    if (_value == ACE && card.get_value() == TWO) {
        return -1;
    }
    if (_value == TWO && card.get_value() == ACE) {
        return 1;
    }
    if (_value > card.get_value()) {
        return 1;
    } else if (_value < card.get_value()) {
        return -1;
    } else {
        return 0;
    }

}


std::string Card::toString() {
    std::string value;
    std::string suit;

    switch (_value) {
        case ACE:
            value = "ACE";
            break;
        case TWO:
            value = "TWO";
            break;
        case THREE:
            value = "THREE";
            break;
        case FOUR:
            value = "FOUR";
            break;
        case FIVE:
            value = "FIVE";
            break;
        case SIX:
            value = "SIX";
            break;
        case SEVEN:
            value = "SEVEN";
            break;
        case EIGHT:
            value = "EIGHT";
            break;
        case NINE:
            value = "NINE";
            break;
        case TEN:
            value = "TEN";
            break;
        case JACK:
            value = "JACK";
            break;
        case QUEEN:
            value = "QUEEN";
            break;
        case KING:
            value = "KING";
            break;
    }
    switch (_suit) {
        case CLUBS:
            suit = "CLUBS";
            break;
        case DIAMONDS:
            suit = "DIAMONDS";
            break;
        case HEARTS:
            suit = "HEARTS";
            break;
        case SPADES:
            suit = "SPADES";
            break;
    }
    return value + " of " + suit;
}



// ariel