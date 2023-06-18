/*
   Copyright 2023
   Dashstrom, Marin Bouanchaud, ericluo-lab, Soudarsane TILLAI, Baptiste Buvron
 */
#include "clan_card_model.hpp"

#include <QMetaEnum>
#include <QString>

#include "card_model.hpp"

ClanCardModel::ClanCardModel(int strength, CardModel::CardColor color) {
  // if ((strength > 1) && strength <= 9)
  m_strength = strength;
  m_color = color;
}

QString ClanCardModel::name() const {
  QMetaEnum metaEnum = QMetaEnum::fromType<ClanCardModel::CardColor>();

  return QString(metaEnum.valueToKey(m_color)).toLower() + "-" +
         QString::number(m_strength) + ".jpg";
}
