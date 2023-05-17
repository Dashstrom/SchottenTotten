#include "clanCard.hpp"

ClanCard::ClanCard(int s, ClanCardColor c)
    : QLabel(QString::number(s)), strength(s), color(c) {

  QColor qcolor;
  switch (color) {
  case ClanCardColor::Green:
    qcolor = QColor(Qt::green);
    break;
  case ClanCardColor::Blue:
    qcolor = QColor(Qt::blue);
    break;
  case ClanCardColor::Red:
    qcolor = QColor(Qt::red);
    break;
  case ClanCardColor::Yellow:
    qcolor = QColor(Qt::yellow);
    break;
  case ClanCardColor::Purple:
    qcolor = QColor(128, 0, 128); // purple color
    break;
  case ClanCardColor::Brown:
    qcolor = QColor(165, 42, 42); // brown color
    break;
  }

  QString style = QString("background-color: %1;").arg(qcolor.name());
  this->setStyleSheet(style);
  this->setFixedSize(100, 100);
  this->setAlignment(Qt::AlignCenter);
};