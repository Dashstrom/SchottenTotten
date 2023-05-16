#include "border.hpp"

Border::Border(QWidget *parent) : QLabel(parent) {
  QPixmap image("assets/images/stone.jpg");

  QHBoxLayout *L = new QHBoxLayout(parent);

  // compute responsive dimensions
  // TODO: make it responsive with window resize
  QRect screenGeometry = QGuiApplication::primaryScreen()->geometry();
  int screenWidth = screenGeometry.width();
  int screenHeight = screenGeometry.height();

  // generate 9 stones
  for (int i = 0; i < 9; i++) {
    QLabel *stoneLabel = new QLabel();
    stoneLabel->setPixmap(image.scaled(screenWidth * 0.12, screenHeight * 0.08,
                                       Qt::KeepAspectRatio));
    L->addWidget(stoneLabel);
  }
}
