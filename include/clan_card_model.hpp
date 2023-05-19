#pragma once

#include <QColor>

#include "card_model.hpp"

class ClanCardModel : public CardModel {
  Q_OBJECT

public:
  enum ClanCardColor {
    Green,
    Blue,
    Red,
    Yellow,
    Purple,
    Brown
  };
  Q_ENUM(ClanCardColor)
  ClanCardModel(int strength, ClanCardColor color) {
    if (this->strength > 1 && this->strength)
    this->strength = strength;
    this->color = color;
  }

  int getStrength() const { return strength; };
  ClanCardColor getColor() const { return color; };

private:
  int strength;
  ClanCardColor color;
};
