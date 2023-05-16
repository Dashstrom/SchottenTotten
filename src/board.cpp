#include "board.hpp"
#include "border.hpp"

Board::Board(QWidget *parent) : QMainWindow(parent) {
  this->setWindowTitle("Schotten Totten");

  QWidget *CentralWidget = new QWidget(this);

  // MENU
  QMenuBar *menu = new QMenuBar(CentralWidget);
  QMenu *game = new QMenu("&Game");
  QAction *restart = game->addAction("Restart game");
  QAction *quit = game->addAction("Close Schotten Totten");
  menu->addMenu(game);

  // BORDER
  Border border = new Border(CentralWidget);

  this->setCentralWidget(CentralWidget);

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
