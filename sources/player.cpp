//
// Created by asaf7 on 3/21/2023.
//

#include "player.hpp"
#include "game.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>





Player::Player() {
}

Player::Player(string name) {
    _name = name;
    this->isPlaying = false;
    this->cardsLeft = 0;
    this->cardsWon = 0;
    this->numOfWins = 0;
    this->_cards = std::vector<Card>();

}

int Player::stacksize() {
    return _cards.size();
}

int Player::cardesTaken() {
    return cardsWon;
}

int Player::getNumOfWins() {
    return numOfWins;
}

int Player::getCardsWon() {
    return cardsWon;
}

int Player::getCardsLeft() {
    return cardsLeft;
}

bool Player::getIsPlaying() {
    return isPlaying;
}

string Player::getName() {
    return _name;
}

void Player::setNumOfWins(int num) {
    numOfWins = num;
}

void Player::setCardsWon(int num) {
    cardsWon = num;
}

void Player::setCardsLeft(int num) {
    cardsLeft = num;
}

void Player::setIsPlaying(bool isPlaying) {
    this->isPlaying = isPlaying;
}

void Player::setCards(std::vector <Card> cards) {
    _cards = cards;
}

void Player::setName(string name) {
    _name = name;
}

std::vector <Card> Player::getCards() {
    return _cards;
}

void Player::addCard(Card card) {
    _cards.push_back(card);
}

void Player::removeCard() {
    if (_cards.size() > 0) {
        _cards.pop_back();
    } else {
        return;
    }
}
class NoCardsLeftException : public std::exception {
public:
    virtual const char* what() const noexcept {
        return "Player has no cards left.";
    }
};

Card Player::getTopCard() {
    if (_cards.empty()) {
        throw NoCardsLeftException();
    }

    Card card = _cards.back();
    _cards.pop_back();
    return card;
}
void Player::restPlayer() {
    this->isPlaying = false;
    this->cardsLeft = 0;
    this->cardsWon = 0;
}


//