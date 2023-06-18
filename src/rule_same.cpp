/*
   Copyright 2023
   Dashstrom, Marin Bouanchaud, ericluo-lab, Soudarsane TILLAI, Baptiste Buvron
 */
#include "rule_same.hpp"

#include <QList>

#include "card_model.hpp"

bool RuleSame::match(QList<CardModel*> cards) const {
  /* Check if cards have the same strength */
  CardModel* previous = nullptr;
  for (auto card : cards) {
    if (previous != nullptr && card->strength() != previous->strength())
      return false;
    previous = card;
  }
  return true;
}
