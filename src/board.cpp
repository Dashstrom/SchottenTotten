#include "board.hpp"

Board::Board(QWidget *parent) : QMainWindow(parent) {
  this->setWindowTitle("Schotten Totten");

  centralWidget = new QWidget(this);
  mainVerticalContainer = new QVBoxLayout(centralWidget);

  // MENU
  QMenuBar *menu = new QMenuBar(centralWidget);
  QMenu *game = new QMenu("&Game");
  QAction *restart = game->addAction("Restart game");
  QAction *quit = game->addAction("Close Schotten Totten");
  menu->addMenu(game);

  // BORDER
  // TODO: move to Game ?
  QWidget *borderContainer = new QWidget();
  mainVerticalContainer->addWidget(borderContainer);
  Border border = new Border(borderContainer);

  this->setCentralWidget(centralWidget);

  connect(restart, SIGNAL(triggered()), this, SLOT(onRestartActionTriggered()));
  connect(quit, SIGNAL(triggered()), this, SLOT(onQuitActionTriggered()));
}

void Board::onRestartActionTriggered() {
  qDebug() << "Restart action triggered!";
}
void Board::onQuitActionTriggered() {
  qDebug() << "Quit action triggered!";
  close();
}

void Board::printHand(Player *player) {
  ClanCard **hand = player->getHand();

  QLabel *handLabel = new QLabel("Click on a stone, then on a clan card, to "
                                 "add it to a formation. Your hand is :");
  handLabel->setAlignment(Qt::AlignCenter);
  mainVerticalContainer->addWidget(handLabel);

  QWidget *handContainer = new QWidget();
  mainVerticalContainer->addWidget(handContainer);

  QHBoxLayout *L = new QHBoxLayout(handContainer);

  for (int i = 0; i < 6; i++) {
    L->addWidget(hand[i]);
  }
}