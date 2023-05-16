#include "window.hpp"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  this->setWindowTitle("Schotten Totten");

  QWidget *widget = new QWidget(this);

  QMenuBar *menu = new QMenuBar(widget);

  // QHBoxLayout *L = new QHBoxLayout(widget);
  // L->addWidget(s1);

  QMenu *game = new QMenu("&Jeu");
  game->addMenu("Relancer partie");
  game->addMenu("Fermer Schotten Totten");

  menu->addMenu(game);

  this->setCentralWidget(widget);
}