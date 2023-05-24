/*
Copyright 2023
Dashstrom, Marin Bouanchaud, ericluo-lab, Soudarsane TILLAI, Baptiste Buvron
*/
#pragma once

#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QString>

#include "game_model.hpp"
#include "stone_model.hpp"
#include "stone_view.hpp"

class GameView : public QWidget {
  QHBoxLayout* layout;
  GameModel* game;

 public:
  explicit GameView(GameModel* model, QWidget* parent = nullptr)
      : QWidget(parent) {
    game = model;
    layout = new QHBoxLayout(this);
    setLayout(layout);
    /* QString backgroundColor =
        QString("background-color: %1;").arg(QColor(Qt::blue).name());
    this->setStyleSheet(backgroundColor); */

    for (StoneModel* stoneModel : game->getStones()) {
      layout->addWidget(new StoneView(stoneModel, this));
    }

    game->getStones()[0]->addPlayer1Card(game->getDeck()->draw());
  }
};
