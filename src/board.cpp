#include "board.hpp"

Board::Board(QWidget *parent, Game *game) : QMainWindow(parent), game(game) {
  this->setWindowTitle("Schotten Totten");

  centralWidget = new QWidget(this);
  mainVerticalContainer = new QVBoxLayout(centralWidget);

  // MENU
  QMenuBar *menuBar = new QMenuBar(centralWidget);
  QMenu *menu = new QMenu("&Game");
  QAction *restart = menu->addAction("Restart game");
  QAction *quit = menu->addAction("Close Schotten Totten");
  menuBar->addMenu(menu);

  // BORDER
  // TODO: move to Game ?
  QWidget *borderContainer = new QWidget();
  mainVerticalContainer->addWidget(borderContainer);
  border = new Border(borderContainer);

  // hand label
  QLabel *handLabel = new QLabel("Click on a stone, then on a clan card, to "
                                 "add it to a formation. Your hand is :");
  handLabel->setAlignment(Qt::AlignCenter);
  mainVerticalContainer->addWidget(handLabel);

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
  qDebug() << "print hand" << player;

  ClanCard **hand = player->getHand();

  QWidget *handContainer = new QWidget();
  // this->handContainer = handContainer; // TODO: fix !

  mainVerticalContainer->addWidget(handContainer);
  qDebug() << "mainVerticalContainer is" << mainVerticalContainer;

  QHBoxLayout *L = new QHBoxLayout(handContainer);

  for (int i = 0; i < 6; i++) {
    L->addWidget(hand[i]);

    connect(hand[i], &ClanCard::clicked, this, &Board::onClanCardClicked);
  }
}

void Board::onClanCardClicked(ClanCard *clanCard) {
  qDebug() << "clan card clicked" << clanCard;

  if (currentClanCardClicked) {
    currentClanCardClicked->setStyleSheet(
        currentClanCardClicked->getBackgroundColor() + "border: 0px;");
  }
  currentClanCardClicked = clanCard;
  currentClanCardClicked->setStyleSheet(
      currentClanCardClicked->getBackgroundColor() + "border: 2px solid red;");

  if (border->getCurrentClickedStone() != nullptr) {
    // TODO game->endTurn()
    game->endTurn();
  }
}

void Board::placeACard(int turn) {
  if (currentClanCardClicked == nullptr ||
      border->getCurrentClickedStone() == nullptr)
    return; // TODO handle error

  if (turn % 2 == 0) {
    // player 1
    border->getCurrentClickedStone()->getLayoutFormation1()->addWidget(
        currentClanCardClicked);
  } else {
    // player 2
    border->getCurrentClickedStone()->getLayoutFormation2()->addWidget(
        currentClanCardClicked);
  }

  // TODO
  // remove current card from hand
  // draw a new card from deck
}

void Board::resetCurrentTurn() {
  currentClanCardClicked = nullptr;
  border->resetCurrentClickedStone();
  mainVerticalContainer->removeWidget(handContainer);
  delete handContainer;
  handContainer = nullptr;
}