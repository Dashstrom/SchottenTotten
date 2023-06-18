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
  DeckModel() {}
  CardModel* draw() {
    // Return the top card and remove it from the deck
    return m_cards.takeFirst();
  }
  bool isEmpty() const { return m_cards.isEmpty(); }
  int countCards() const { return m_cards.count(); }
  void addCard(CardModel* card) { m_cards.append(card); }
  void shuffle();

 private:
  QList<CardModel*> m_cards;
};

#endif  // INCLUDE_DECK_MODEL_HPP_
