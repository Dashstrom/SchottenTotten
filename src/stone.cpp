#include "stone.hpp"

Stone::Stone(QWidget *parent) : QWidget(parent) {
  QPixmap image("assets/images/stone.jpg");

  QVBoxLayout *L = new QVBoxLayout(this);

  formation1 = new QWidget();
  formation2 = new QWidget();

  // compute responsive dimensions
  // TODO: make it responsive with window resize
  QRect screenGeometry = QGuiApplication::primaryScreen()->geometry();
  int screenWidth = screenGeometry.width();
  int screenHeight = screenGeometry.height();

  stoneMain = new QLabel();
  stoneMain->setPixmap(image.scaled(screenWidth * 0.12, screenHeight * 0.08,
                                    Qt::KeepAspectRatio));

  L->addWidget(formation1);
  L->addWidget(stoneMain);
  L->addWidget(formation2);

  // note: mousePress signal is handled in Border
  //   connect(this, &Stone::clicked, this, &Stone::onClicked);
}