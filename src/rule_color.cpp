/*
   Copyright 2023
   Dashstrom, Marin Bouanchaud, ericluo-lab, Soudarsane TILLAI, Baptiste Buvron
 */
#include "rule_color.hpp"

#include <QList>

#include "card_model.hpp"

bool RuleColor::match(QList<CardModel*> cards) const {
  /* Check if cards have the same color */
  CardModel* previous = nullptr;
  for (auto card : cards) {
    if (previous != nullptr && card->color() != previous->color()) return false;
    previous = card;
  }
  return true;
}
