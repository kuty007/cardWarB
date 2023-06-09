//
// Created by asaf7 on 3/21/2023.
//
#include <string>
using namespace std;
#pragma once
#ifndef CARDWAR_A_CARD_H
#define CARDWAR_A_CARD_H
namespace ariel{
void print();
}
enum Suit {
    CLUBS,
    DIAMONDS,
    HEARTS,
    SPADES
};
enum Value {
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    JACK,
    QUEEN,
    KING,
    ACE
};


    class Card {
    public:
        Card();
        Card(Value, Suit);
        Value get_value();
        Suit get_suit();
        void set_value(Value value);
        void set_suit(Suit suit);
        int compare(Card card);
        //tostring
        string toString();

    private:
        Value _value;
        Suit _suit;
    };


 // ariel

#endif //CARDWAR_A_CARD_H
