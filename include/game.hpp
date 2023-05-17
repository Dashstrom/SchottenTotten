#pragma once

class Board;
#include "board.hpp"
#include "player.hpp"
#include "startModal.hpp"

class Game {
public:
  Game();
  void launch();
  Player *getPlayer1() { return player1; };
  Player *getPlayer2() { return player2; };
  Deck *getDeck() { return deck; };
  void startTurn();
  void endTurn();
  bool hasWinner() {
    return false;
  }; // TODO: compute winner at the end of each turn

private:
  Board *board;
  Deck *deck;
  Player *player1;
  Player *player2;
  int turn;
};