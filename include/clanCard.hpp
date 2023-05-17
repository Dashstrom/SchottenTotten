#pragma once

#include <QColor>
#include <QLabel>

enum class ClanCardColor { Green, Blue, Red, Yellow, Purple, Brown };

class ClanCard : public QLabel {
public:
  ClanCard(int s = 0, ClanCardColor c = ClanCardColor::Green);

  int getStrength() const { return strength; };
  ClanCardColor getColor() const { return color; };

  // TODO : add setters with validation (>= 1 && <= 6 ...)

private:
  int strength;
  ClanCardColor color;
};
