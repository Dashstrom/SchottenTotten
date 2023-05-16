#include "window.hpp"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  this->setWindowTitle("Schotten Totten");

  QWidget *widget = new QWidget(this);

  QMenuBar *menu = new QMenuBar(widget);

  QMenu *game = new QMenu("&Jeu");
  QAction *restart = game->addAction("Relancer la partie");
  QAction *quit = game->addAction("Fermer Schotten Totten");

  menu->addMenu(game);

  this->setCentralWidget(widget);

  connect(restart, SIGNAL(triggered()), this, SLOT(onRestartActionTriggered()));
  connect(quit, SIGNAL(triggered()), this, SLOT(onQuitActionTriggered()));
}

void MainWindow::onRestartActionTriggered() {
  qDebug() << "Restart action triggered!";
}
void MainWindow::onQuitActionTriggered() {
  qDebug() << "Quit action triggered!";
  close();
}
