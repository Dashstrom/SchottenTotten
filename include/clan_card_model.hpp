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
  ClanCardModel(int strength, CardModel::CardColor color) {
    // if ((strength > 1) && strength <= 9)
    m_strength = strength;
    m_color = color;
  }

  int strength() const override { return m_strength; }

  CardModel::CardColor color() const override { return m_color; }

  QString name() const override {
    QMetaEnum metaEnum = QMetaEnum::fromType<ClanCardModel::CardColor>();

    return QString(metaEnum.valueToKey(m_color)) + "-" +
           QString::number(m_strength) + ".png";
  }

 private:
  int m_strength;
  CardModel::CardColor m_color;
};
