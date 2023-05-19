#pragma once

#include <QMetaEnum>
#include <QObject>
#include <QList>
#include <algorithm>
#include <random>
#include "clan_card_model.hpp"

class DeckModel : public QObject {
  Q_OBJECT
public:
  DeckModel() {
    // Initialize the deck with random cards
    QMetaEnum metaEnum = QMetaEnum::fromType<ClanCardModel::ClanCardColor>();
    for (int i = 0; i < metaEnum.keyCount(); ++i) {
      for (int strength = 1; strength <= 9; strength ++) {
        auto color = static_cast<ClanCardModel::ClanCardColor>(metaEnum.value(i));
        cards.append(new ClanCardModel(strength, color));
      }
    }

    // Shuffle cards
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(cards.begin(), cards.end(), gen);

  }

  CardModel *draw() {
    // Return the top card and remove it from the deck
    return cards.takeFirst();
  }

  bool isEmpty() const { return cards.isEmpty(); }

private:
  QList<CardModel *> cards;
};


