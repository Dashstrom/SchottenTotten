/*
   Copyright 2023
   Dashstrom, Marin Bouanchaud, ericluo-lab, Soudarsane TILLAI, Baptiste Buvron
 */
#include <QApplication>
#include <QDebug>

#include "mainwindow.hpp"

int main(int argc, char* argv[]) {
  /* Run main app*/

  QApplication app(argc, argv);

  MainWindow window;

  window.show();

  qDebug() << "Start application";
  app.exec();
  qDebug() << "Stop application";
  return 0;
}
