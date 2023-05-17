#include "border.hpp"

Border::Border(QWidget *parent) : QLabel(parent) {
  QPixmap image("assets/images/stone.jpg");

  QHBoxLayout *L = new QHBoxLayout(parent);

  // generate 9 stones
  for (int i = 0; i < 9; i++) {
    Stone *stone = new Stone();

    // Connect the custom clicked signal of each stone to a slot in the Border
    // class
    connect(stone, &Stone::clicked, this, &Border::onStoneClicked);

    L->addWidget(stone);
  }
}

void Border::onStoneClicked(Stone *stone) {
  // Access the instance of the clicked stone here
  // ...
  qDebug() << "border stone clicked";

  if (currentClickedStone) {
    currentClickedStone->getStoneMain()->setStyleSheet("border: 0px;");
  }
  currentClickedStone = stone;
  currentClickedStone->getStoneMain()->setStyleSheet("border: 2px solid red;");
}