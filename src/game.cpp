#include "game.hpp"

Game::Game() {
  deck = new Deck();
  player1 = new Player(deck);
  player2 = new Player(deck);
  turn = 0;

  // start
  new StartModal(this);
}

void Game::launch() {
  board = new Board(nullptr, this);
  board->show();

  startTurn(player1);
}

void Game::startTurn(Player *player) {
  if (turn % 2 == 0)
    QMessageBox::information(board, "Game started", "Player 1 : your turn !");
  else
    QMessageBox::information(board, "Game started", "Player 2 : your turn !");

  // display player 1 hand
  board->printHand(player);
}

void Game::endTurn() {
  // place selected clan card in a formation
  board->placeACard(turn);

  // get the board ready for next turn
  board->resetCurrentTurn();

  if (hasWinner())
    return; // TODO end game / display winner
  if (turn++ % 2 == 0)
    startTurn(player1);
  else
    startTurn(player2);
}