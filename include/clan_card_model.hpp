/*
   Copyright 2023
   Dashstrom, Marin Bouanchaud, ericluo-lab, Soudarsane TILLAI, Baptiste Buvron
 */
#ifndef INCLUDE_CLAN_CARD_MODEL_HPP_
#define INCLUDE_CLAN_CARD_MODEL_HPP_

#include <QColor>
#include <QMetaEnum>
#include <QObject>

#include "card_model.hpp"

class ClanCardModel : public CardModel {
  Q_OBJECT

 public:
  ClanCardModel(int strength, CardModel::CardColor color);

  int strength() const override { return m_strength; }

  CardModel::CardColor color() const override { return m_color; }

  QString name() const override;

 private:
  int m_strength;
  CardModel::CardColor m_color;
};

#endif  // INCLUDE_CLAN_CARD_MODEL_HPP_
