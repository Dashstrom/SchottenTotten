/*
   Copyright 2023
   Dashstrom, Marin Bouanchaud, ericluo-lab, Soudarsane TILLAI, Baptiste Buvron
 */
#pragma once

#include <QList>

#include "card_model.hpp"
#include "rule.hpp"

class RuleColor : public Rule {
 public:
  bool match(QList<CardModel*> cards) const override {
    /* Check if cards have the same color */
    CardModel* previous = nullptr;
    for (auto card : cards) {
      if (previous != nullptr && card->color() != previous->color())
        return false;
      previous = card;
    }
    return true;
  }
};
