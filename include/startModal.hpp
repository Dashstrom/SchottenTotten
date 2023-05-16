#pragma once

class Game;

#include "board.hpp"
#include "game.hpp"
#include <QAction>
#include <QDialog>
#include <QHBoxLayout>
#include <QLabel>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QObject>
#include <QPixmap>
#include <QPushButton>
#include <iostream>

class StartModal : public QDialog {
  Q_OBJECT

public:
  explicit StartModal(Game *game, QWidget *parent = nullptr);

private slots:
  void onStartGameButtonClicked();

private:
  QPushButton *startButton;
  Board *board;
  Game *currentGame;
};
