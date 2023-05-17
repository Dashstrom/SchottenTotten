#pragma once

#include "border.hpp"
#include "clanCard.hpp"
#include "player.hpp"
#include <QAction>
#include <QColor>
#include <QHBoxLayout>
#include <QLabel>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QPixmap>
#include <iostream>

class Board : public QMainWindow {
  Q_OBJECT

public:
  Board(QWidget *parent = nullptr);
  void printHand(Player *player);
  ClanCard *getCurrentClanCardClicked() { return currentClanCardClicked; };

private slots:
  void onRestartActionTriggered();
  void onQuitActionTriggered();

private:
  QWidget *centralWidget;
  QMenuBar *menuBar;
  QMenu *gameMenu;
  QVBoxLayout *mainVerticalContainer;
  ClanCard *currentClanCardClicked;

  void onClanCardClicked(ClanCard *clanCard);
};