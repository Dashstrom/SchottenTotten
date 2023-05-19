/*
Copyright 2023
Dashstrom, Marin Bouanchaud, ericluo-lab, Soudarsane TILLAI, Baptiste Buvron
*/
#include <QApplication>
#include <QDebug>

#include "mainwindow.hpp"

int main(int argc, char *argv[]) {
  /* Run main app*/

  QApplication app(argc, argv);

  MainWindow window;
  window.show();

  qDebug() << "Start execution";
  app.exec();
  qDebug() << "End execution";
  return 0;
}
