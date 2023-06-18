/*
   Copyright 2023
   Dashstrom, Marin Bouanchaud, ericluo-lab, Soudarsane TILLAI, Baptiste Buvron
 */
#ifndef INCLUDE_RULE_COLOR_RUN_HPP_
#define INCLUDE_RULE_COLOR_RUN_HPP_

#include <QList>

#include "card_model.hpp"
#include "rule.hpp"
#include "rule_color.hpp"
#include "rule_run.hpp"

class RuleColorRun : public Rule {
 public:
  RuleColorRun() : Rule("color_run") {}
  bool match(QList<CardModel *> cards) const override {
    return m_ruleColor.match(cards) && m_ruleRun.match(cards);
  }

 private:
  RuleColor m_ruleColor;
  RuleRun m_ruleRun;
};

#endif  // INCLUDE_RULE_COLOR_RUN_HPP_
