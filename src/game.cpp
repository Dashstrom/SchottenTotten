#include "game.hpp"

Game::Game() {
  deck = new Deck();
  player1 = new Player(deck);
  player2 = new Player(deck);

  // start
  new StartModal(this);
}

void Game::launch() {
  board = new Board();
  board->show();

  QMessageBox::information(board, "Game started", "Player 1 : your turn !");

  // display player 1 hand
  board->printHand(player1);
}