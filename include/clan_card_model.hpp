/*
Copyright 2023
Dashstrom, Marin Bouanchaud, ericluo-lab, Soudarsane TILLAI, Baptiste Buvron
*/
#pragma once

#include <QColor>
#include <QMetaEnum>
#include <QObject>

#include "card_model.hpp"

class ClanCardModel : public CardModel {
  Q_OBJECT

 public:
  enum CardColor { Green, Blue, Red, Yellow, Purple, Brown };
  Q_ENUM(CardColor)
  ClanCardModel(int strength, CardColor color) {
    if (strength > 1 && strength) m_strength = strength;
    m_color = color;
  }

  int getStrength() const { return m_strength; }
  CardColor getColor() const { return m_color; }
  QString name() const {
    QMetaEnum metaEnum = QMetaEnum::fromType<ClanCardModel::CardColor>();
    return QString(metaEnum.valueToKey(m_color)) + "-" +
           QString::number(m_strength) + ".png";
  }

 private:
  int m_strength;
  CardColor m_color;
};
