/*
   Copyright 2023
   Dashstrom, Marin Bouanchaud, ericluo-lab, Soudarsane TILLAI, Baptiste Buvron
 */
#include "rule_run.hpp"

#include <QList>

#include "card_model.hpp"

bool RuleRun::match(QList<CardModel*> cards) const {
  /* Check if cards have successive strength */
  QList<CardModel*> cardsCopy = cards;
  std::sort(cardsCopy.begin(), cardsCopy.end(),
            [](CardModel* card, CardModel* other) {
              return card->strength() < other->strength();
            });
  CardModel* previous = nullptr;
  for (auto card : cards) {
    if (previous != nullptr && previous->strength() != card->strength() - 1)
      return false;
    previous = card;
  }
  return true;
}
