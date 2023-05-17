#pragma once

class Game;
#include "border.hpp"
#include "clanCard.hpp"
#include "game.hpp"
#include "player.hpp"
#include <QAction>
#include <QColor>
#include <QCoreApplication>
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
  Board(QWidget *parent = nullptr, Game *game = nullptr);
  void printHand(Player *player);
  ClanCard *getCurrentClanCardClicked() { return currentClanCardClicked; };
  void placeACard(int turn);
  void resetCurrentTurn();

private slots:
  void onRestartActionTriggered();
  void onQuitActionTriggered();

private:
  Game *game;
  QWidget *centralWidget;
  QMenuBar *menuBar;
  QMenu *gameMenu;
  Border *border;
  QVBoxLayout *mainVerticalContainer;
  QWidget *handContainer;
  ClanCard *currentClanCardClicked = nullptr;

  void onClanCardClicked(ClanCard *clanCard);
};