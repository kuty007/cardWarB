
//
// Created by asaf7 on 3/21/2023.
//
#include <string>
#include "player.hpp"
#pragma once
#ifndef CARDWAR_A_GAME_H
#define CARDWAR_A_GAME_H


class Game {
public:

    Game(Player &player1, Player &player2);


    void printLastTurn();

    void printWiner();

    void printLog();

    void playTurn();

    void playAll();

    void printStats();

    //crate all the cards and give them to the players
    void createCards();

    int getTurns();

    int getDraws();

    int getPlayer1Wins();

    int getPlayer2Wins();

    int getPlayer1CardsWon();

    int getPlayer2CardsWon();

    std::string drawTurn(int totalCards, string log);


private:
    Player &_player1;
    Player &_player2;
    std::vector <Card> _cards;
    int _turns = 0;
    int draws = 0;
    int _player1Wins = 0;
    int _player2Wins = 0;
    int _player1CardsWon = 0;
    int _player2CardsWon = 0;
    // log of game plays
    std::vector <string> _log;


};


#endif //CARDWAR_A_GAME_H
