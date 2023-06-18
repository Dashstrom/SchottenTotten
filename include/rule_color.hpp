/*
   Copyright 2023
   Dashstrom, Marin Bouanchaud, ericluo-lab, Soudarsane TILLAI, Baptiste Buvron
 */
#ifndef INCLUDE_RULE_COLOR_HPP_
#define INCLUDE_RULE_COLOR_HPP_

#include <QList>

#include "card_model.hpp"
#include "rule.hpp"

class RuleColor : public Rule {
 public:
  RuleColor() : Rule("color") {}
  bool match(QList<CardModel*> cards) const override;
};

#endif  // INCLUDE_RULE_COLOR_HPP_
