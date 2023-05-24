/*
Copyright 2023
Dashstrom, Marin Bouanchaud, ericluo-lab, Soudarsane TILLAI, Baptiste Buvron
*/
#pragma once

#include <QGuiApplication>
#include <QLabel>
#include <QList>
#include <QPixmap>
#include <QScreen>
#include <QVBoxLayout>

#include "card_model.hpp"

class StoneModel : public QObject {
  Q_OBJECT

 public:
  void addPlayer1Card(CardModel *card) {
    player1Combo.append(card);
    emit player1ComboChanged(player1Combo);
  }
  void addPlayer2Card(CardModel *card) {
    player2Combo.append(card);
    emit player2ComboChanged(player2Combo);
  }

 private:
  QList<CardModel *> player1Combo;
  QList<CardModel *> player2Combo;

 signals:
  void player1ComboChanged(const QList<CardModel *>);
  void player2ComboChanged(const QList<CardModel *>);
};
