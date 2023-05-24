/*
Copyright 2023
Dashstrom, Marin Bouanchaud, ericluo-lab, Soudarsane TILLAI, Baptiste Buvron
*/
#pragma once

#include <QList>
#include <QObject>

#include "clan_card_model.hpp"
#include "deck_model.hpp"

class PlayerModel : public QObject {
  Q_OBJECT

 public:
  QList<CardModel *> getCards() { return cards; }

 private:
  QList<CardModel *> cards;
};
