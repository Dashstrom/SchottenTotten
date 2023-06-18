/*
   Copyright 2023
   Dashstrom, Marin Bouanchaud, ericluo-lab, Soudarsane TILLAI, Baptiste Buvron
 */
#ifndef INCLUDE_RULE_RUN_HPP_
#define INCLUDE_RULE_RUN_HPP_

#include <QList>
#include <algorithm>

#include "card_model.hpp"
#include "rule.hpp"

class RuleRun : public Rule {
 public:
  RuleRun() : Rule("run") {}
  bool match(QList<CardModel*> cards) const override;
};

#endif  // INCLUDE_RULE_RUN_HPP_
