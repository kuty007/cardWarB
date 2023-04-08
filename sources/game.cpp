//
// Created by asaf7 on 3/23/2023.
//

#include "game.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>


//    Game::Game(): _player1(defaultPlayer), _player2(defaultPlayer) {}

Game::Game(Player &player1, Player &player2) : _player1(player1), _player2(player2) {
//    if (&player1 == &player2) {
//        throw std::invalid_argument("Players can't be the same");
    try {
        if (player1.getIsPlaying() || player2.getIsPlaying()) {
            throw std::invalid_argument("One of the players is already playing");
        }
    } catch (std::invalid_argument &e) {
        cout << e.what() << endl;
        return;
    }
    createCards();
    _player1.setCardsLeft(26);
    _player2.setCardsLeft(26);
    _player1.setIsPlaying(true);
    _player2.setIsPlaying(true);

}

void Game::printLastTurn() {
    if (_log.size() == 0) {
        cout << "No turns played yet" << endl;
        return;
    }
    cout << _log.back() << endl;
}

void Game::printWiner() {
    string winner;
    if (_player1.getCardsWon() > _player2.getCardsWon()) {
        winner = _player1.getName();
    } else if (_player1.getCardsWon() < _player2.getCardsWon()) {
        winner = _player2.getName();
    } else {
        winner = "Draw!";
    }
    if (winner == "Draw!") {
        cout << "The game ended in a draw!" << endl;
    } else {
        cout << winner << " won the game!" << endl;
    }
}


void Game::printLog() {
    if (_log.size() == 0) {
        cout << "No turns played yet" << endl;
        return;
    }
    for (int i = 0; i < _log.size(); i++) {
        cout << _log[static_cast<std::vector<int>::size_type>(i)] << endl;
    }
}

void Game::playTurn() {
    if (_player1.stacksize() == 0 || _player2.stacksize() == 0) {
        throw std::invalid_argument("One of the players has no cards left");
    }

//check if the players are the same player
    if (&_player1 == &_player2) {
        throw std::invalid_argument("Players can't be the same");
    }
    Card card1;
    Card card2;
    card1 = _player1.getTopCard();
    card2 = _player2.getTopCard();
    _turns++;
    if (card1.compare(card2) == 1) {
        _player1Wins++;
        _player1CardsWon += 2;
        _player1.setCardsWon(_player1.getCardsWon() + 2);
        _player1.setCardsLeft(_player1.getCardsLeft() - 1);
        _player2.setCardsLeft(_player2.getCardsLeft() - 1);
        _log.push_back(
                _player1.getName() + " won the turn with " + card1.toString() + " and " + _player2.getName() +
                " lost with " + card2.toString());
    } else if (card1.compare(card2) == -1) {
        _player2Wins++;
        _player2CardsWon += 2;
        _player2.setCardsWon(_player2.getCardsWon() + 2);
        _player2.setCardsLeft(_player2.getCardsLeft() - 1);
        _player1.setCardsLeft(_player1.getCardsLeft() - 1);
        _log.push_back(
                _player2.getName() + " won the turn with " + card2.toString() + " and " + _player1.getName() +
                " lost with " + card1.toString());
    } else {
        drews++;
        string log =
                _player1.getName() + " played " + card1.toString() + " and " + _player2.getName() + " played " +
                card2.toString() + " Drew! ";
        log = drewTurn(2, log);
        _log.push_back(log);
    }
}

std::string Game::drewTurn(int totalCards, std::string log) {
    //check if one of the players has less than 2 cards left and if so you can't do a drew turn
    if (_player1.stacksize() == 0 || _player2.stacksize() == 0) {
        _player1.setCardsLeft(0);
        _player2.setCardsLeft(0);
        _player1.setCardsWon(_player1.getCardsWon() + (totalCards / 2));
        _player2.setCardsWon(_player2.getCardsWon() + (totalCards / 2));
        return "";
    }
    if (_player1.stacksize() < 2 || _player2.stacksize() < 2) {

        _player1.setCardsLeft(0);
        _player2.setCardsLeft(0);
        _player1.removeCard();
        _player2.removeCard();
        totalCards += 2;
        _player1.setCardsWon(_player1.getCardsWon() + (totalCards / 2));
        _player2.setCardsWon(_player2.getCardsWon() + (totalCards / 2));
        return "";
    }
    //dump card from each plyer and then play turn
    //if drew again then dump again and play turn
    if (_player1.stacksize() >= 2) {
        _player1.removeCard();
        _player2.removeCard();
        totalCards += 2;
        Card card1 = _player1.getTopCard();
        Card card2 = _player2.getTopCard();
        totalCards += 2;
        if (card1.compare(card2) == 1) {
            _player1Wins++;
            _player1CardsWon += totalCards;
            _player1.setCardsWon(_player1.getCardsWon() + totalCards);
            _player1.setCardsLeft(_player1.getCardsLeft() - (totalCards / 2));
            _player2.setCardsLeft(_player2.getCardsLeft() - (totalCards / 2));
            log += _player1.getName() + " won the drew with " + card1.toString() + " and " + _player2.getName() +
                   " lost with " + card2.toString();
            return log;

        } else if (card1.compare(card2) == -1) {
            _player2Wins++;
            _player2CardsWon += totalCards;
            _player2.setCardsWon(_player2.getCardsWon() + totalCards);
            _player2.setCardsLeft(_player2.getCardsLeft() - (totalCards / 2));
            _player1.setCardsLeft(_player1.getCardsLeft() - (totalCards / 2));
            log += _player2.getName() + " won the drew with " + card2.toString() + " and " + _player1.getName() +
                   " lost with " + card1.toString();
            return log;
        } else {
            drews++;
            log += _player1.getName() + " played " + card1.toString() + " and " + _player2.getName() + " played " +
                   card2.toString() + " Drew!\n";
            return drewTurn(totalCards, log);
        }
    }
    return log;
}


void Game::playAll() {
    while (_player1.stacksize() > 0 && _player2.stacksize() > 0) {
        playTurn();
    }
}

void Game::printStats() {
    string statsString = "Total turns: " + to_string(_turns) + "\n"
                                                               "Drews: " + to_string(drews) + " turns from " +
                         to_string(getTurns()) + " turns\n"
                         + _player1.getName() + " wins: " + to_string(_player1Wins) + " turns from " +
                         to_string(getTurns()) + " turns\n"
                         + _player1.getName() + " win rate =:" + to_string((float) _player1Wins / getTurns() * 100) +
                         "\n"
                         + _player2.getName() + " wins: " + to_string(_player2Wins) + " turns from " +
                         to_string(getTurns()) + " turns\n"
                         + _player2.getName() + " win rate =:" + to_string((float) _player2Wins / getTurns() * 100)+"\n"
                         + _player1.getName() + " total cards Won: " + to_string(_player1CardsWon) + "\n"
                         + _player2.getName() + " total cards Won: " + to_string(_player2CardsWon) + "\n";
    cout << statsString;

}

void Game::createCards() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 13; j++) {
            //crate card with enum value of i and j
            Card card = Card(static_cast<Value>(j), static_cast<Suit>(i));
            _cards.push_back(card);
        }
    }
    unsigned seed = std::chrono::system_clock::now()
            .time_since_epoch()
            .count();
    shuffle(_cards.begin(), _cards.end(), std::default_random_engine(seed));
    for (int i = 0; i < 26; i++) {
        Card card = _cards.back();
        _player1.addCard(card);
        _cards.pop_back();
        card = _cards.back();
        _player2.addCard(card);
        _cards.pop_back();
    }

}

int Game::getTurns() {
    return _turns;
}

int Game::getDrews() {
    return drews;
}

int Game::getPlayer1Wins() {
    return _player1Wins;
}

int Game::getPlayer2Wins() {
    return _player2Wins;
}

int Game::getPlayer1CardsWon() {
    return _player1CardsWon;
}

int Game::getPlayer2CardsWon() {
    return _player2CardsWon;
}





// ariel