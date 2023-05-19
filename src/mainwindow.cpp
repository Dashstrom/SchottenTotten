#include "mainwindow.hpp"
#include "game_view.hpp"
#include "game_model.hpp"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  // Since this is a QMainWindow we cannot set a layout,
  // we can only set a central widget.
  GameModel* gameModel = new GameModel();
  GameView* gameView = new GameView(gameModel, this);
  QIcon icon("resources/favicon.ico");
  this->setWindowTitle("BLABLA");
  this->setCentralWidget(gameView);
  this->setMinimumHeight(256);
  this->setMinimumWidth(256);
  this->setWindowIcon(icon);
}
