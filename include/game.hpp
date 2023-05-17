#pragma once

class Board;
#include "board.hpp"
#include "player.hpp"
#include "startModal.hpp"

class Game {
public:
  Game();
  void launch();
  void startTurn(Player *player);
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