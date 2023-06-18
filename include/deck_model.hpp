/*
   Copyright 2023
   Dashstrom, Marin Bouanchaud, ericluo-lab, Soudarsane TILLAI, Baptiste Buvron
 */
#ifndef INCLUDE_DECK_MODEL_HPP_
#define INCLUDE_DECK_MODEL_HPP_

#include <QList>
#include <QObject>

#include "clan_card_model.hpp"

class DeckModel : public QObject {
  Q_OBJECT

 public:
  DeckModel();
  CardModel* draw() {
    // Return the top card and remove it from the deck
    return cards.takeFirst();
  }
  bool isEmpty() const { return cards.isEmpty(); }
  int countCards() const { return cards.count(); }

 private:
  QList<CardModel*> cards;
};

#endif  // INCLUDE_DECK_MODEL_HPP_
