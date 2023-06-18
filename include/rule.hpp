/*
   Copyright 2023
   Dashstrom, Marin Bouanchaud, ericluo-lab, Soudarsane TILLAI, Baptiste Buvron
 */
#ifndef INCLUDE_RULE_HPP_
#define INCLUDE_RULE_HPP_

#include <QList>
#include <QString>

#include "card_model.hpp"

class Rule {
 public:
  explicit Rule(QString name) : m_name(name) {}
  virtual ~Rule() {}
  virtual bool match(QList<CardModel *> cards) const = 0;
  const QString name() const { return m_name; }

 private:
  QString m_name;
};

#endif  // INCLUDE_RULE_HPP_
