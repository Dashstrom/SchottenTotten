/*
Copyright 2023
Dashstrom, Marin Bouanchaud, ericluo-lab, Soudarsane TILLAI, Baptiste Buvron
*/
#pragma once

#include <QVBoxLayout>
#include <QLineEdit>
#include <QString>
#include <QLabel>
#include <QWidget>
#include <QPixmap>
#include <QPixmap>
#include <QLayoutItem>
#include <QRect>

#include "card_model.hpp"

class CardView
  : public QWidget {
  QHBoxLayout *layout;
  QLabel* cardImage;
  CardModel* card;

 public:
  CardView(CardModel* model, QWidget* parent = nullptr) : QWidget(parent) {
    card = model;
    layout = new QHBoxLayout();
    
    QPixmap image("resources/cards/" + card->name());

    // TODO(Dashstrom): make it responsive with window resize
    QRect screenGeometry = QGuiApplication::primaryScreen()->geometry();
    int screenWidth = screenGeometry.width();
    int screenHeight = screenGeometry.height();

    cardImage = new QLabel(this);
    cardImage->setPixmap(
      image.scaled(
        screenWidth * 0.12,
        screenHeight * 0.08,
        Qt::KeepAspectRatio
      )
    );
    layout->addWidget(cardImage);
  }
};
