/*
   Copyright 2023
   Dashstrom, Marin Bouanchaud, ericluo-lab, Soudarsane TILLAI, Baptiste Buvron
 */
#pragma once

#include <QList>

#include "card_model.hpp"
#include "rule.hpp"
#include "rule_color.hpp"
#include "rule_run.hpp"

class RuleColorRun : public Rule {
 public:
  bool match(QList<CardModel *> cards) const override {
    return ruleColor.match(cards) && ruleRun.match(cards);
  }

 private:
  RuleColor ruleColor;
  RuleRun ruleRun;
};
