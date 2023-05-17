#pragma once

#include "board.hpp"
#include "player.hpp"
#include "startModal.hpp"

class Game {
public:
  Game();
  void launch();

private:
  Board *board;
  Deck *deck;
  Player *player1;
  Player *player2;
};