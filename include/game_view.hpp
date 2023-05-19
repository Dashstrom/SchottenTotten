#pragma once

#include <QHBoxLayout>
#include <QLineEdit>
#include <QString>
#include <QLabel>

#include "game_model.hpp"
#include "stone_view.hpp"
#include "stone_model.hpp"

class GameView
  : public QWidget {
  QHBoxLayout* layout;
  GameModel* game;

 public:
  GameView(GameModel* model, QWidget* parent = nullptr) : QWidget(parent) {
    game = model;
    layout = new QHBoxLayout(this);
    setLayout(layout);
    QString backgroundColor = QString("background-color: %1;").arg(QColor(Qt::blue).name());
    this->setStyleSheet(backgroundColor);

    for (StoneModel *stoneModel : game->getStones()) {
      layout->addWidget(new StoneView(stoneModel, this));
    };
  }
};
