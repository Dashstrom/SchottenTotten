#include "board.hpp"

Board::Board(QWidget *parent) : QMainWindow(parent) {
  this->setWindowTitle("Schotten Totten");

  centralWidget = new QWidget(this);
  mainVerticalContainer = new QVBoxLayout(centralWidget);

  // MENU
  QMenuBar *menu = new QMenuBar(centralWidget);
  QMenu *game = new QMenu("&Game");
  QAction *restart = game->addAction("Restart game");
  QAction *quit = game->addAction("Close Schotten Totten");
  menu->addMenu(game);

  // BORDER
  // TODO: move to Game ?
  QWidget *borderContainer = new QWidget();
  mainVerticalContainer->addWidget(borderContainer);
  Border border = new Border(borderContainer);

  this->setCentralWidget(centralWidget);

  connect(restart, SIGNAL(triggered()), this, SLOT(onRestartActionTriggered()));
  connect(quit, SIGNAL(triggered()), this, SLOT(onQuitActionTriggered()));
}

void Board::onRestartActionTriggered() {
  qDebug() << "Restart action triggered!";
}
void Board::onQuitActionTriggered() {
  qDebug() << "Quit action triggered!";
  close();
}

void Board::printHand(Player *player) {
  const ClanCard *hand = player->getHand();

  QLabel *handLabel = new QLabel("Your hand :");
  handLabel->setAlignment(Qt::AlignCenter);
  mainVerticalContainer->addWidget(handLabel);

  QWidget *handContainer = new QWidget();
  mainVerticalContainer->addWidget(handContainer);

  QHBoxLayout *L = new QHBoxLayout(handContainer);

  for (int i = 0; i < 6; i++) {
    QLabel *cardLabel = new QLabel(QString::number(hand[i].getStrength()));

    QColor qcolor;
    switch (hand[i].getColor()) {
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
    cardLabel->setStyleSheet(style);
    cardLabel->setFixedSize(100, 100);
    cardLabel->setAlignment(Qt::AlignCenter);

    L->addWidget(cardLabel);
  }
}