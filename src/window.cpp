#include "window.hpp"
#include "border.hpp"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  this->setWindowTitle("Schotten Totten");

  QWidget *CentralWidget = new QWidget(this);

  // MENU
  QMenuBar *menu = new QMenuBar(CentralWidget);
  QMenu *game = new QMenu("&Jeu");
  QAction *restart = game->addAction("Relancer la partie");
  QAction *quit = game->addAction("Fermer Schotten Totten");
  menu->addMenu(game);

  // BORDER
  Border border = new Border(CentralWidget);

  this->setCentralWidget(CentralWidget);

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
