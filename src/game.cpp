#include "game.hpp"

Game::Game() { new StartModal(this); }

void Game::launch() {
  board = new Board();
  board->show();

  QMessageBox::information(board, "Game started", "Player 1 : your turn !");

  // display player 1 hand
}