/*
   Copyright 2023
   Dashstrom, Marin Bouanchaud, ericluo-lab, Soudarsane TILLAI, Baptiste Buvron
 */
#pragma once

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
