#pragma once

#include "board.hpp"
#include "startModal.hpp"

class Game {
public:
  Game();
  void launch();

private:
  Board *board;
};