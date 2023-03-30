#include "window.hpp"
#include <QApplication>
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  Tester test;
  test.show();

  app.exec();
  return 0;
}
