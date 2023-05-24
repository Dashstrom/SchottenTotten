/*
Copyright 2023
Dashstrom, Marin Bouanchaud, ericluo-lab, Soudarsane TILLAI, Baptiste Buvron
*/
#pragma once

#include <QLabel>
#include <QLineEdit>
#include <QPixmap>
#include <QString>
#include <QVBoxLayout>
#include <QWidget>

#include "card_model.hpp"
#include "card_view.hpp"
#include "stone_model.hpp"

class StoneView : public QWidget {
  QWidget* formation1;
  QWidget* formation2;
  QVBoxLayout* layoutFormation1;
  QVBoxLayout* layoutFormation2;
  QVBoxLayout* layout;
  QLabel* stoneImage;
  StoneModel* stone;

 public:
  explicit StoneView(StoneModel* model, QWidget* parent = nullptr)
      : QWidget(parent) {
    stone = model;
    QPixmap image("resources/stone.jpg");

    QVBoxLayout* layout = new QVBoxLayout(this);

    formation1 = new QWidget(this);
    layoutFormation1 = new QVBoxLayout(formation1);

    formation2 = new QWidget(this);
    layoutFormation2 = new QVBoxLayout(formation2);

    // compute responsive dimensions
    // TODO(Marin Bouanchaud): make it responsive with window resize
    QRect screenGeometry = QGuiApplication::primaryScreen()->geometry();
    int screenWidth = screenGeometry.width();
    int screenHeight = screenGeometry.height();

    stoneImage = new QLabel();
    stoneImage->setPixmap(image.scaled(screenWidth * 0.12, screenHeight * 0.08,
                                       Qt::KeepAspectRatio));

    layout->addWidget(formation1);
    layout->addWidget(stoneImage);
    layout->addWidget(formation2);

    connect(model, &StoneModel::player1ComboChanged, this,
            [&](QList<CardModel*> cards) {
              for (auto card : cards) {
                layoutFormation1->addWidget(new CardView(card, formation1));
              }
            });

    connect(model, &StoneModel::player2ComboChanged, this,
            [&](QList<CardModel*> cards) {
              for (auto card : cards) {
                layoutFormation1->addWidget(new CardView(card, formation2));
              }
            });
  }
};
