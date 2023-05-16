#include "game.hpp"
#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  Game game;

  app.exec();
  return 0;
}