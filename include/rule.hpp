/*
   Copyright 2023
   Dashstrom, Marin Bouanchaud, ericluo-lab, Soudarsane TILLAI, Baptiste Buvron
 */
#pragma once

#include <QList>

#include "card_model.hpp"

class Rule {
 public:
  virtual bool match(QList<CardModel *> cards) const = 0;
};
