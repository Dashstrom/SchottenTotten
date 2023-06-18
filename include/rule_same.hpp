/*
   Copyright 2023
   Dashstrom, Marin Bouanchaud, ericluo-lab, Soudarsane TILLAI, Baptiste Buvron
 */
#ifndef INCLUDE_RULE_SAME_HPP_
#define INCLUDE_RULE_SAME_HPP_

#include <QList>

#include "card_model.hpp"
#include "rule.hpp"

class RuleSame : public Rule {
 public:
  RuleSame() : Rule("same") {}
  bool match(QList<CardModel*> cards) const override;
};

#endif  // INCLUDE_RULE_SAME_HPP_
