/*
   Copyright 2023
   Dashstrom, Marin Bouanchaud, ericluo-lab, Soudarsane TILLAI, Baptiste Buvron
 */
#include "deck_model.hpp"

#include <QMetaEnum>
#include <algorithm>
#include <random>

#include "clan_card_model.hpp"

DeckModel::DeckModel() {
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
