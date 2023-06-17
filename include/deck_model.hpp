/*
   Copyright 2023
   Dashstrom, Marin Bouanchaud, ericluo-lab, Soudarsane TILLAI, Baptiste Buvron
 */
#ifndef INCLUDE_DECK_MODEL_HPP_
#define INCLUDE_DECK_MODEL_HPP_

#include <QList>
#include <QMetaEnum>
#include <QObject>
#include <algorithm>
#include <random>

#include "clan_card_model.hpp"

class DeckModel : public QObject {
  Q_OBJECT

 public:
  DeckModel() {
    // Initialize the deck with random cards
    QMetaEnum metaEnum = QMetaEnum::fromType<ClanCardModel::CardColor>();

    for (int i = 0; i < metaEnum.keyCount(); ++i) {
      for (int strength = 1; strength <= 9; strength++) {
        auto color = static_cast<ClanCardModel::CardColor>(metaEnum.value(i));
        cards.append(new ClanCardModel(strength, color));
      }
    }

    // Shuffle cards
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(cards.begin(), cards.end(), gen);
  }

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
